#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
PROBLEM: MINIMUM PATH SUM
-----------------------------------------------------------
You are given an n x m grid filled with non-negative numbers.
Find a path from top-left (0,0) to bottom-right (n-1,m-1)
such that the sum of all numbers along the path is minimum.

You can only move:
1. RIGHT  (i, j+1)
2. DOWN   (i+1, j)

Example:
Grid:
1 3 1
1 5 1
4 2 1

Possible path:
1 → 3 → 1 → 1 → 1 = 7 (minimum)

Goal:
Find the minimum possible path sum.
===========================================================
*/


/*
===========================================================
1️⃣ MEMOIZATION (Top Down DP)
-----------------------------------------------------------
INTUITION:
We start from the destination (n-1, m-1) and recursively
ask:

What is the minimum path to reach here?

To reach (i,j), we must come from:
1. top  -> (i-1, j)
2. left -> (i, j-1)

So recurrence relation becomes:

dp[i][j] = grid[i][j] + min(
                solve(i-1,j),
                solve(i,j-1)
            )

Base Case:
If we reach (0,0), return grid[0][0].

Memoization:
Store results in dp array to avoid recomputation.
===========================================================
*/

int solveMemo(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp)
{
    // Base case: starting cell
    if(i == 0 && j == 0)
        return grid[0][0];

    // If out of bounds return very large value
    if(i < 0 || j < 0)
        return INT_MAX;

    // If already computed return stored value
    if(dp[i][j] != -1)
        return dp[i][j];

    int up = solveMemo(i-1, j, grid, dp);
    int left = solveMemo(i, j-1, grid, dp);

    return dp[i][j] = grid[i][j] + min(up, left);
}

int minPathMemo(vector<vector<int>>& grid)
{
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> dp(n, vector<int>(m, -1));

    return solveMemo(n-1, m-1, grid, dp);
}



/*
===========================================================
2️⃣ TABULATION (Bottom-Up DP)
-----------------------------------------------------------
INTUITION:
Instead of recursion, we build the answer from the start.

We create a DP table where:
dp[i][j] = minimum path sum to reach cell (i,j)

Transition:
dp[i][j] = grid[i][j] + min(
                dp[i-1][j],  // from top
                dp[i][j-1]   // from left
            )

Base Case:
dp[0][0] = grid[0][0]

We fill the table row by row.
===========================================================
*/

int minPathTab(vector<vector<int>>& grid)
{
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> dp(n, vector<int>(m, 0));

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(i==0 && j==0)
            {
                dp[i][j] = grid[i][j];
            }
            else
            {
                int up = INT_MAX;
                int left = INT_MAX;

                if(i>0) up = dp[i-1][j];
                if(j>0) left = dp[i][j-1];

                dp[i][j] = grid[i][j] + min(up,left);
            }
        }
    }

    return dp[n-1][m-1];
}



/*
===========================================================
3️⃣ SPACE OPTIMIZATION
-----------------------------------------------------------
OBSERVATION:
In tabulation we only use:
- current row
- previous row

So we don't need the entire matrix.

We keep:
prev[] -> previous row
cur[]  -> current row

This reduces space complexity from O(n*m) to O(m).
===========================================================
*/

int minPathSpace(vector<vector<int>>& grid)
{
    int n = grid.size();
    int m = grid[0].size();

    vector<int> prev(m,0);

    for(int i=0;i<n;i++)
    {
        vector<int> cur(m,0);

        for(int j=0;j<m;j++)
        {
            if(i==0 && j==0)
            {
                cur[j] = grid[i][j];
            }
            else
            {
                int up = INT_MAX;
                int left = INT_MAX;

                if(i>0) up = prev[j];
                if(j>0) left = cur[j-1];

                cur[j] = grid[i][j] + min(up,left);
            }
        }

        prev = cur;
    }

    return prev[m-1];
}



/*
===========================================================
MAIN FUNCTION
-----------------------------------------------------------
Takes input from user
Runs all three methods
===========================================================
*/

int main()
{
    int n,m;

    cout<<"Enter rows and columns: ";
    cin>>n>>m;

    vector<vector<int>> grid(n, vector<int>(m));

    cout<<"Enter grid values:\n";

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>grid[i][j];
        }
    }

    cout<<"\nMinimum Path Sum (Memoization): "
        <<minPathMemo(grid)<<endl;

    cout<<"Minimum Path Sum (Tabulation): "
        <<minPathTab(grid)<<endl;

    cout<<"Minimum Path Sum (Space Optimized): "
        <<minPathSpace(grid)<<endl;

    return 0;
}