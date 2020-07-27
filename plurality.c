#include<stdio.h>
#include<cs50.h>
#include<string.h>
//libaries
#define MAX 9



typedef struct //class
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];

int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[]) //cmd args
{

    if (argc < 2)
    {
        printf("Usage: plurality [candinate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i <= candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("vote: "); //inp

        if (!vote(name))
        {
            printf("Invalid vote.\n"); //op
        }
    }

    print_winner(); //winner
}
int get_index(string name) //var
{
    for (int i = 0; i < candidate_count; i++)
        if (strcmp(name, candidates[i].name) == 0)
        {
            return i;
        }
    return -1;
}

bool vote(string name)
{
    int candidate_index = get_index(name);
    if (candidate_index != -1)
    {
        candidates[candidate_index].votes++;
        return true;
    }
    return false;
}

int get_max(void)
{
    int max_votes = candidates[0].votes;
    for (int i = 1; i < candidate_count; i++) //loop
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    return max_votes;
}

void print_winner(void)
{
    int max_votes = get_max();

    for (int i = 0; i < candidate_count; i++) //loop
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name); //last
        }
       
    }

}