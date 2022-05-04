#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max electors and contestants
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// predilections[i][j] is jth preference for elector i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have or obtain, vote count, removed status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of nominees
candidate candidates[MAX_CANDIDATES];

// Numbers of electors and competitors
int voter_count;
int candidate_count;

// Function originals
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
// Check for invalid custom
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

// Populate array of competitors
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

// Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

// Query each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

// Record vote, upon any less condition than it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

// Keep equity runoffs until champion exists
    while (true)
    {
// Calculate votes likely remaining nominees
        tabulate();

// Check if voting has existed won
        bool won = print_winner();
        if (won)
        {
            break;
        }

// Eliminate last-place nominees
        int min = find_min();
        bool tie = is_tie(min);

// If tie, all wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

// Eliminate one accompanying minimum number of votes
        eliminate(min);

// Reset vote counts back to nothing
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record option if vote is genuine
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < voter_count; j++)
        {
            if (strcmp(name, candidates[i].name) == 0)
            {
                preferences[voter][rank] = i;
                return true;
            }
        }
    }
    return false;
}

// Tabulate votes for non-removed contestants
void tabulate(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes += 1;
                break;
            }

        }
    }
    return;
}

// Print the champion of the voting, if skilled is individual
bool print_winner(void)
{
    // TODO
    int half = voter_count / 2;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > half)
        {
            printf("Winner: %s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int minimum = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes > minimum) && (candidates[i].eliminated == false))
        {
            minimum =  candidates[i].votes;
        }
    }
    return minimum;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int max_votes = min;

    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes > max_votes) && (candidates[i].eliminated == false))
        {
            max_votes = candidates[i].votes;

        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes == max_votes) && (candidates[i].eliminated == false))
        {
            for (int j = i + 1; j < candidate_count; j++)
            {
                if (candidates[j].votes == max_votes)
                {
                    return true;
                }
            }

        }
        else
        {
            return false;
        }
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes <= min) && (candidates[i].eliminated == false))
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}