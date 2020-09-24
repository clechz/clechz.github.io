import os

from re import search
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import alert
from pytz import timezone
from helpers import apology, login_required, lookup, usd
from datetime import datetime


# Configure application
app = Flask(__name__)

# current time
time = datetime.now(timezone("Asia/Riyadh"))


# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")
db2 = SQL("sqlite:///finance_backup.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                  username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology(" invalid username and / or password", 403)


        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    rows = db.execute("SELECT symbol, SUM(shares) AS shares, price, SUM(total) AS total FROM trans WHERE user_id = :session GROUP BY symbol; ", session=session["user_id"])
    users = db.execute("SELECT * FROM users WHERE id = :session;", session = session["user_id"])
    username = users[0]["username"]
    portfolio = []
    grand = 0
    for row in rows:
        stock = lookup(row["symbol"])
        portfolio.append({
            "symbol": stock["symbol"],
            "name": stock["name"],
            "shares": row["shares"],
            "price": usd(stock["price"]),
            "total": usd(row["total"])
        })
        grand += row["total"]
    cash = users[0]["cash"]

    return render_template("index.html", username=username, portfolio=portfolio, cash=usd(cash), grand = usd(grand))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shrares of stock"""

    if request.method == "POST":

        shares = request.form.get("shares")
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)

        if not stock:
            return apology("Invalid Symbol", 403)

        if not symbol:
            return apology("Missing Symbol", 403)

        if not shares:
            return apology("Missing Shares", 403)

        name = stock["name"]
        price = stock['price']
        total = int(shares) * price

        rows = db.execute("SELECT cash FROM users WHERE id = :session;", session = session["user_id"])

        cash = rows[0]["cash"]

        #fcash = total - cash
        fcash = cash - total

        if total > cash:
            return apology("Can't Afford")

        db.execute("INSERT INTO trans (user_id, symbol, shares, price, total) VALUES(:session, :symbol, :shares, :price, :total);",
            session=session["user_id"], symbol=symbol, shares=shares, price=price, total=total)

        db.execute("INSERT INTO history (user_id, symbol, shares, price, transacted) VALUES(:session, :symbol, :shares, :price, :time);",
            session=session["user_id"], symbol=symbol, shares= shares, price=price, time=time)

        db.execute("UPDATE users SET cash = :fcash WHERE id = :session",
            fcash=fcash, session=session["user_id"])

        flash(f"Bought {shares} share/s of {name}")

        return redirect("/")

    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM history WHERE user_id = :session", session=session["user_id"])
    price = rows[0]["price"]
    for row in rows:
        row["price"] = usd(row["price"])
        row["shares"] = str(row["shares"])
        if int(row["shares"]) > 0:
            row["shares"] = f"+{row['shares']}"

    return render_template("history.html", rows=rows,)

@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        symbol = request.form.get("symbol")
        stock = lookup(symbol)

        if not symbol:
            return apology("Missing Symbol")

        elif not stock:
            return apology("Invalid Symbol")

        return render_template("quoted.html", symbol=stock["symbol"], name=stock["name"], cost=stock["price"])

    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        repassword = request.form.get("repassword")
        hash = generate_password_hash(password)

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        rows = db.execute("SELECT username FROM users WHERE username = (:username)",
            username = username)

        if len(rows) == 1:
            return apology("sorry this username is all ready taken!", 403)

        if password != repassword:
            return apology("sorry passwords dosen't match!", 403)

        if len(str(password)) < 8:
            return apology("password must be 8 charcters or longer")

        if search("[#~@$%^&*()-={}[];:"" '|\?><+,/`]", password) != None:
            apology("password must not countain any spechial charcters or emoji")

        prim_key = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
            username=username, hash=hash)

        session["user_id"] = prim_key
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    rows = db.execute("SELECT symbol, SUM(shares) AS shares FROM trans where user_id = :session GROUP BY symbol;", session=session["user_id"])
    users = db.execute("SELECT * FROM users WHERE id = :session;", session = session["user_id"])


    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        stock = lookup(symbol)
        name = stock["name"]
        price = stock["price"]
        cash = users[0]["cash"]
        fcash = cash + price * int(shares)

        if not symbol or not shares:
            return apology("you must provide a symbol and shares ", 403)

        for row in rows:
            if row["symbol"] == symbol:
                mshares = row["shares"]


        if int(mshares) < int(shares):
            return apology("can't afford", 403)

        else:
            # TODO

            hshares = "-"+shares

            db.execute("UPDATE users SET cash = :fcash WHERE id = :session; ",
            fcash=fcash, session=session["user_id"])

            db.execute("DELETE FROM trans WHERE user_id = :session AND symbol IN (SELECT symbol FROM trans WHERE symbol = :symbol ORDER BY trans_id LIMIT :shares); ",
                session=session["user_id"], symbol=symbol, shares=int(shares))

            db.execute("INSERT INTO history (user_id, symbol, shares, price, transacted) VALUES(:session, :symbol, :shares, :price, :time);",
                session=session["user_id"], symbol=symbol, shares= hshares, price=price, time=time)

            flash(f"Sold {shares} share/s of {name} !!")
            return redirect("/")

    else:
        rows = db.execute("SELECT symbol, SUM(shares) AS shares FROM trans where user_id = :session GROUP BY symbol;", session=session["user_id"])
        # the view info
        options = []
        for row in rows:
            options.append({
                "symbol": row["symbol"],
                "shares": row["shares"]
            })

        return render_template("sell.html", options=options)


@app.route("/settings", methods=["GET", "POST"])
@login_required
def settings():

    users = db.execute("SELECT * FROM users WHERE id = :session;", session = session["user_id"])


    if request.method == "POST":
        pass

    else:
        return render_template("settings.html",username=users[0]["username"])


@app.route("/settings/change_username", methods=["GET", "POST"])
@login_required
def changeUsername():

    if request.method == "POST":

        reusername = request.form.get("reusername")

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                  username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology(" invalid username and / or password", 403)


        db.execute("UPDATE users SET username = :reusername WHERE id = :session;",
            reusername= reusername, session=session["user_id"])

        flash(f"Username has been changed successfully to {reusername}!")
        return redirect("/")

    else:
        return render_template("change_username.html")


@app.route("/settings/change_password", methods=["GET", "POST"])
@login_required
def changePassowrd():

    if request.method == "POST":

        repassword = request.form.get("repassword")
        hash = generate_password_hash(repassword)

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                  username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology(" invalid username and / or password", 403)


        db.execute("UPDATE users SET hash = :hash WHERE id = :session;",
            hash=hash, session=session["user_id"])

        flash("Password has been changed successfully!")
        return redirect("/")

    else:
        return render_template("change_password.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

