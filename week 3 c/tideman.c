#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];
bool blocked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int counter;
int dif[99];
int x;
int y;
int test;

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
            blocked[i][j] = false;
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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks

int preference(int intfirst, int intsecond, int ranks[])   // calculates if someone is preffered
{

    int pos1;
    int pos2;
    for (int i = 0; i < candidate_count; i++)
    {
        if (ranks[i] == intfirst)
        {
            pos1 = i;
        }
        if (ranks[i] == intsecond)
        {
            pos2 = i;
        }
    }
    if (pos1 < pos2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void circle(int first, int second)   //tests if values ends where it started
{
    int i = 0;
    int z = first;
    int o = second;
    int testx = 0;

    while (testx == 0)
    {
        if (blocked[second][i] == true)
        {

            for (int j = 0; j < pair_count; j++)
            {
                if (pairs[j].winner == second && pairs[j].loser == first && blocked[pairs[j].winner][pairs[j].loser] == true)
                {
                    blocked[z][o] = false;
                    testx = 1;
                }
            }
            second = i;
            i = 0;
        }
        else
        {
            i++;
        }
        if (i > candidate_count)
        {
            testx = 1;
        }
    }

    return;

}


void record_preferences(int ranks[])
{
    // TODO
    int pos;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preference(i, j, ranks) == 1)
            {
                preferences[i][j]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO

    counter = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[counter].winner = i;
                pairs[counter].loser = j;  //dodat winner i lossera u struck
                dif[counter] = preferences[pairs[counter].winner][pairs[counter].loser] - preferences[pairs[counter].loser][pairs[counter].winner];
                counter++;
                pair_count = counter;

            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    int diff = 0;
    int diff1 = 0;
    int counterx = -1;
    pair temp;

    while (counterx != 0)
    {
        for (int j = 0; j < pair_count; j++)
        {
            counterx = 0;
            diff = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            diff1 = preferences[pairs[j + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j + 1].winner];

            if (diff < diff1)
            {
                temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
                counterx++;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO

    for (int i = 0; i < candidate_count; i++) 
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                blocked[i][j] = true;
            }
        }
    }

    int count1 = 0;
    int count3 = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (blocked[i][j] == 1)
            {
                count1++;
            }
        }
        if (count1 == 1)
        {
            count3++;
        }
        count1 = 0;
    }
    if (count3 == 3)
    {
        blocked[pairs[pair_count - 1].winner][pairs[pair_count - 1].loser] = false;
    }


    for (int i = pair_count; i > 0; i--)
    {
        circle(pairs[i].winner, pairs[i].loser);
    }

    for (int i = 0; i < pair_count; i++)
    {

        if (blocked[pairs[i].winner][pairs[i].loser] == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }


    }

    return;

}

// Print the winner of the election
void print_winner(void)
{
    // TODO

    int winner = 0;
    int c = 0;
    int max = 0;
    int position;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)              //searches calumn a row with all 0/false values
            {
                c++;
            }
        }
        if (c == candidate_count)
        {
            position = i;
        }

        c = 0;
    }

    printf("%s\n", candidates[position]);

    return;
}