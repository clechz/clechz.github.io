SELECT title 
FROM people 
JOIN ratings ON ratings.movie_id = movies.id
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE name = "Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5