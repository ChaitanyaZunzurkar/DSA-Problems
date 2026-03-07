#include <iostream>
#include <vector>
using namespace std;

/*
===========================================================
PROBLEM: UNIQUE PATHS WITH OBSTACLES
===========================================================

Grid contains:
0 -> free cell
1 -> obstacle

Start: (0,0)
End:   (n-1,m-1)

Allowed moves:
1. Right
2. Down

Goal:
Find total number of unique paths avoiding obstacles.

Core idea for all solutions:

Ways(i,j) = Ways(i-1,j) + Ways(i,j-1)

Meaning:
Paths to reach current cell =
paths from UP + paths from LEFT

If obstacle present:
Ways(i,j) = 0
===========================================================
*/


/*
===========================================================
SOLUTION 1 : RECURSION + MEMOIZATION (TOP DOWN DP)
===========================================================

Idea:

We start from destination (n-1,m-1) and recursively
move UP or LEFT until we reach (0,0).

Memoization avoids recomputation.

Time Complexity  : O(n*m)
Space Complexity : O(n*m) + recursion stack
===========================================================
*/

int solveMemo(vector<vector<int>> &grid, int i, int j, vector<vector<int>> &dp)
{
    // if obstacle encountered
    if(grid[i][j] == 1)
        return 0;

    // base case -> starting cell
    if(i == 0 && j == 0)
        return 1;

    if(dp[i][j] != -1)
        return dp[i][j];

    int up = 0;
    int left = 0;

    if(i > 0)
        up = solveMemo(grid, i-1, j, dp);

    if(j > 0)
        left = solveMemo(grid, i, j-1, dp);

    return dp[i][j] = up + left;
}

int uniquePathsMemo(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    if(grid[0][0] == 1)
        return 0;

    vector<vector<int>> dp(n, vector<int>(m, -1));

    return solveMemo(grid, n-1, m-1, dp);
}



/*
===========================================================
SOLUTION 2 : TABULATION (BOTTOM UP DP)
===========================================================

We build the DP table iteratively.

dp[i][j] stores number of ways to reach cell (i,j).

Transition:

dp[i][j] = dp[i-1][j] + dp[i][j-1]

If obstacle -> dp[i][j] = 0

Time Complexity  : O(n*m)
Space Complexity : O(n*m)
===========================================================
*/

int uniquePathsTab(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    if(grid[0][0] == 1)
        return 0;

    vector<vector<int>> dp(n, vector<int>(m, 0));

    dp[0][0] = 1;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(grid[i][j] == 1)
            {
                dp[i][j] = 0;
                continue;
            }

            if(i == 0 && j == 0)
                continue;

            int up = 0;
            int left = 0;

            if(i > 0)
                up = dp[i-1][j];

            if(j > 0)
                left = dp[i][j-1];

            dp[i][j] = up + left;
        }
    }

    return dp[n-1][m-1];
}



/*
===========================================================
SOLUTION 3 : SPACE OPTIMIZED DP
===========================================================

Observation:
Each cell depends only on:

UP   -> previous row
LEFT -> same row previous column

So we do not need full 2D DP.

We store only one row.

dp[j] represents number of ways to reach column j
in the current row.

Transition:

dp[j] = dp[j] (UP) + dp[j-1] (LEFT)

If obstacle:
dp[j] = 0

Time Complexity  : O(n*m)
Space Complexity : O(m)
===========================================================
*/

int uniquePathsSpace(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    if(grid[0][0] == 1)
        return 0;

    vector<int> dp(m, 0);

    dp[0] = 1;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(grid[i][j] == 1)
            {
                dp[j] = 0;
            }
            else if(j > 0)
            {
                dp[j] += dp[j-1];
            }
        }
    }

    return dp[m-1];
}



/*
===========================================================
MAIN FUNCTION
===========================================================
*/

int main()
{
    int n, m;

    cout << "Enter rows: ";
    cin >> n;

    cout << "Enter columns: ";
    cin >> m;

    vector<vector<int>> grid(n, vector<int>(m));

    cout << "Enter grid values (0 = free, 1 = obstacle):\n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }

    cout << "\nResults:\n";

    cout << "Memoization Solution : "
         << uniquePathsMemo(grid) << endl;

    cout << "Tabulation Solution : "
         << uniquePathsTab(grid) << endl;

    cout << "Space Optimized Solution : "
         << uniquePathsSpace(grid) << endl;

    return 0;
}