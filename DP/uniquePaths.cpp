#include <iostream>
#include <vector>
using namespace std;

/*
=====================================================
PROBLEM 1 : UNIQUE PATHS (NO OBSTACLES)
=====================================================

Grid size = n x m

Start  -> (0,0)
Finish -> (n-1,m-1)

Moves allowed:
1. Right
2. Down

Core Idea:

To reach cell (i,j) we can come from:

UP   -> (i-1,j)
LEFT -> (i,j-1)

So,

ways(i,j) = ways(i-1,j) + ways(i,j-1)

Base case:

ways(0,0) = 1
=====================================================
*/


/*
-----------------------------------------------------
MEMOIZATION (TOP DOWN DP)
-----------------------------------------------------
*/

int solveMemoUP(int i, int j, vector<vector<int>> &dp)
{
    if(i == 0 && j == 0)
        return 1;

    if(dp[i][j] != -1)
        return dp[i][j];

    int up = 0;
    int left = 0;

    if(i > 0)
        up = solveMemoUP(i-1, j, dp);

    if(j > 0)
        left = solveMemoUP(i, j-1, dp);

    return dp[i][j] = up + left;
}

int uniquePathsMemo(int n, int m)
{
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveMemoUP(n-1, m-1, dp);
}



/*
-----------------------------------------------------
TABULATION (BOTTOM UP)
-----------------------------------------------------
*/

int uniquePathsTab(int n, int m)
{
    vector<vector<int>> dp(n, vector<int>(m, 0));

    dp[0][0] = 1;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
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
-----------------------------------------------------
SPACE OPTIMIZATION
-----------------------------------------------------

Observation:

Each cell depends only on:

UP   -> previous row
LEFT -> previous column

So we only store one row.

dp[j] = ways to reach column j
*/

int uniquePathsSpace(int n, int m)
{
    vector<int> dp(m, 0);

    dp[0] = 1;

    for(int i = 0; i < n; i++)
    {
        for(int j = 1; j < m; j++)
        {
            dp[j] += dp[j-1];
        }
    }

    return dp[m-1];
}




/*
=====================================================
PROBLEM 2 : UNIQUE PATHS WITH OBSTACLES
=====================================================

Same as previous problem but:

1 -> obstacle
0 -> free cell

If obstacle present:

ways(i,j) = 0
=====================================================
*/


/*
-----------------------------------------------------
MEMOIZATION
-----------------------------------------------------
*/

int solveMemoObs(vector<vector<int>> &grid, int i, int j, vector<vector<int>> &dp)
{
    if(grid[i][j] == 1)
        return 0;

    if(i == 0 && j == 0)
        return 1;

    if(dp[i][j] != -1)
        return dp[i][j];

    int up = 0;
    int left = 0;

    if(i > 0)
        up = solveMemoObs(grid, i-1, j, dp);

    if(j > 0)
        left = solveMemoObs(grid, i, j-1, dp);

    return dp[i][j] = up + left;
}

int uniquePathsObsMemo(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    if(grid[0][0] == 1)
        return 0;

    vector<vector<int>> dp(n, vector<int>(m, -1));

    return solveMemoObs(grid, n-1, m-1, dp);
}



/*
-----------------------------------------------------
TABULATION
-----------------------------------------------------
*/

int uniquePathsObsTab(vector<vector<int>> &grid)
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
-----------------------------------------------------
SPACE OPTIMIZED
-----------------------------------------------------
*/

int uniquePathsObsSpace(vector<vector<int>> &grid)
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
                dp[j] = 0;

            else if(j > 0)
                dp[j] += dp[j-1];
        }
    }

    return dp[m-1];
}



/*
=====================================================
MAIN FUNCTION
=====================================================
*/

int main()
{
    int n, m;

    cout << "Enter rows and columns: ";
    cin >> n >> m;

    cout << "\nUNIQUE PATHS (NO OBSTACLES)\n";

    cout << "Memoization : " << uniquePathsMemo(n,m) << endl;
    cout << "Tabulation  : " << uniquePathsTab(n,m) << endl;
    cout << "Space Opt   : " << uniquePathsSpace(n,m) << endl;


    cout << "\nEnter grid for obstacle problem:\n";

    vector<vector<int>> grid(n, vector<int>(m));

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin >> grid[i][j];


    cout << "\nUNIQUE PATHS WITH OBSTACLES\n";

    cout << "Memoization : " << uniquePathsObsMemo(grid) << endl;
    cout << "Tabulation  : " << uniquePathsObsTab(grid) << endl;
    cout << "Space Opt   : " << uniquePathsObsSpace(grid) << endl;

}