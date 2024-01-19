#include <cs50.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (name == candidates[i])
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; ++i)
    {
        int winner_candidate = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            int loser_candidate = ranks[j];
            preferences[winner_candidate][loser_candidate]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // i + j to avoid self comparison, even though its correct as j = 0;
        for (int j = i + 1; j < candidate_count; j++)
        {
            int preference = preferences[i][j];
            int reversed_preference = preferences[j][i];

            if (preference > reversed_preference)
            {
                pairs[pair_count++] = (pair){.winner = i, .loser = j};
            }
            else if (preference < reversed_preference)
            {
                pairs[pair_count++] = (pair){.winner = j, .loser = i};
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    bool swapped;
    do
    {
        swapped = false;
        for (int i = pair_count - 1; i >= 1; i--)
        {
            int rightPreference = preferences[pairs[i].winner][pairs[i].loser];
            int leftPreference = preferences[pairs[i - 1].winner][pairs[i - 1].loser];

            if (rightPreference > leftPreference)
            {
                pair rightPair = pairs[i];
                pair leftPair = pairs[i - 1];

                pairs[i - 1] = rightPair;
                pairs[i] = leftPair;
                swapped = true;
            }
        }
    } while (swapped);

    return;
}

bool has_cycle(int loser, int winner)
{
    if (loser == winner)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (has_cycle(i, winner))
            {
                return true;
            }
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; ++i)
    {
        if (!has_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

bool has_arrow_pointing_at_him(int candidate)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[candidate][i])
        {
            return true;
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool has_arrow_pointing_at_him = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                has_arrow_pointing_at_him = true;
                break;
            }
        }

        if (!has_arrow_pointing_at_him)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}
