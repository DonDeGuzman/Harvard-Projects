#include <cs50.h>

#include <stdio.h>

#include <string.h>

// Max number of applicants
#define MAX 9

// Up-and-comers have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Cluster of applicants
candidate candidates[MAX];

// Number of competitors
int candidate_count;

// Work models
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid utilization
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate exhibit of competitors
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Circle over all citizens
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Show victor of political decision
    print_winner();
}

// Update vote aggregates given another vote
bool vote(string name)
{
    //Circle through the Candidate count
    for (int i = 0; i < candidate_count; i++)
    {
        //check assuming applicant like is client's vote
        if (strcmp(candidates[i].name, name) == 0)
        {
            //on the off chance that like what client vote in favor of, increment the particular competitor vote and bring valid back
            candidates[i].votes++;
            return true;
        }
    }
    //different, if the vote is not alike to that of the contender, return wrong.....and print the invalid vote /different, if the vote is not equal to that of the aspirant, return dishonest.....and print the invalid vote
    return false;
}

// Print the champion (or numbers one) of the voting
void print_winner(void)
{
    //Create and changing and set it to 0
    int maximum_vote = 0;

    //emphasize over list of nominee
    for (int i = 0; i < candidate_count; i++)
    {
        //check for applicant votes that are higher in amount maximum_vote and set ruling class to maximum_vote
        if (candidates[i].votes > maximum_vote)
        {
            maximum_vote = candidates[i].votes;
        }
    }

    //say again over list of contender
    for (int i = 0; i < candidate_count; i++)
    {
        //check for aspirant votes that are effective maximum vote and print bureaucracy as you go
        if (candidates[i].votes == maximum_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}