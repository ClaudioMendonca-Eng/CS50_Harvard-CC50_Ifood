#include <cs50.h>
#include <stdio.h>
#include <string.h>

// https://cdn.cs50.net/2020/fall/psets/3/runoff/runoff.c

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }
    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
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

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        if (strcmp(candidates[candidate].name, name) == 0)
        {

            preferences[voter][rank] = candidate;
            if (preferences[voter][0] == candidate)
            {
                candidates[candidate].votes++;
            }

            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{

    for (int voter = 0; voter < voter_count; voter++)
    {
        for (int rank = 0; rank < candidate_count; rank++)
        {
            if (preferences[voter][0] == rank)
            {
                candidates[rank].votes++;
            }
        }
    }

    for (int voter = 0; voter < voter_count; voter++)
    {
        for (int candidate = 0; candidate < candidate_count; candidate++)
        {
            if (preferences[voter][0] == candidate)
            {
                if (candidates[candidate].eliminated)
                {
                    candidates[candidate].votes--;
                    candidates[preferences[voter][1]].votes++;
                    for (int rank = 0, tab = 1; rank < candidate_count; rank++, tab++)
                    {
                        if (tab < candidate_count)
                        {
                            preferences[voter][rank] = preferences[voter][tab];
                        }
                        else
                        {
                            preferences[voter][rank] = candidate;
                        }
                    }
                }
            }
        }
    }

    return;
}
// Print the winner of the election, if there is one
bool print_winner(void)
{
    //
    int majority = candidates[0].votes;
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        if (candidates[candidate].votes > majority)
        {
            majority = candidates[candidate].votes;
        }
    }

    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        if ((candidates[candidate].votes == majority) && (majority > (voter_count / 2)))
        {
            printf("%s\n", candidates[candidate].name);
            return true;
        }
    }

    return false;
}
// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min = candidates[0].votes; // Assume o primeiro elemento como mínimo inicial
    for (int rank = 0; rank < candidate_count; rank++)
    {
        if (candidates[rank].votes < min && !(candidates[rank].eliminated))
        {
            min = candidates[rank].votes; // Atualiza o mínimo se encontrar um valor menor
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int tie = 0;
    int eliminated = 0;
    for (int rank = 0; rank < candidate_count; rank++)
    {
        if (candidates[rank].votes == min && !(candidates[rank].eliminated))
        {
            tie++;
        }
        if (candidates[rank].eliminated)
        {
            eliminated++;
        }
    }
    if (tie == (candidate_count - eliminated))
    {
        return true;
    }

    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO

    printf("min = %i\n", min);

    for (int rank = 0; rank < candidate_count; rank++)
    {
        if (candidates[rank].votes == min)
        {
            candidates[rank].eliminated = true;
        }
    }

    return;
}
