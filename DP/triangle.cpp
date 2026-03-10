#include <bits/stdc++.h>
using namespace std;

/*
========================================================
PROBLEM: Minimum Path Sum in Triangle
========================================================

Given a triangle array, start from the top element
and move to the bottom row.

Allowed moves:
1. Down      -> (i+1, j)
2. Diagonal  -> (i+1, j+1)

Goal:
Find the minimum sum path from top to bottom.

Example:
Input:
4
2
3 4
6 5 7
4 1 8 3

Output:
11

Path: 2 -> 3 -> 5 -> 1

========================================================
TIME COMPLEXITY
Memoization      : O(N^2)
Tabulation       : O(N^2)
Space Optimized  : O(N^2) time , O(N) space
========================================================
*/


/*
========================================================
1️⃣ MEMOIZATION (Top Down DP)
========================================================

Idea:
We recursively explore both choices:
- down
- diagonal

To avoid recomputation we store results in dp.

dp[i][j] = minimum path sum starting from (i,j)
*/

int solveMemo(vector<vector<int>>& triangle, int row, int col, int n, vector<vector<int>>& dp)
{
    // Base case: last row
    if(row == n-1)
        return triangle[row][col];

    // If already computed
    if(dp[row][col] != -1)
        return dp[row][col];

    // Move Down
    int down = triangle[row][col] + solveMemo(triangle, row+1, col, n, dp);

    // Move Diagonal
    int diagonal = triangle[row][col] + solveMemo(triangle, row+1, col+1, n, dp);

    // Store result
    return dp[row][col] = min(down, diagonal);
}

int minimumTotalMemo(vector<vector<int>>& triangle)
{
    int n = triangle.size();

    vector<vector<int>> dp(n, vector<int>(n, -1));

    return solveMemo(triangle, 0, 0, n, dp);
}


/*
========================================================
2️⃣ TABULATION (Bottom Up DP)
========================================================

Instead of recursion, we start from the bottom row.

Why?
Because the last row values are already the minimum
cost to reach the bottom.

Then we move upwards and compute:

dp[i][j] = triangle[i][j] +
           min(dp[i+1][j], dp[i+1][j+1])
*/

int minimumTotalTabulation(vector<vector<int>>& triangle)
{
    int n = triangle.size();

    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Initialize last row
    for(int j=0;j<n;j++)
        dp[n-1][j] = triangle[n-1][j];

    // Fill from bottom to top
    for(int i=n-2;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {
            int down = triangle[i][j] + dp[i+1][j];
            int diagonal = triangle[i][j] + dp[i+1][j+1];

            dp[i][j] = min(down, diagonal);
        }
    }

    return dp[0][0];
}



/*
========================================================
3️⃣ SPACE OPTIMIZATION
========================================================

Observation:
Each row only depends on the next row.

So instead of storing entire dp table,
we only store ONE row.

front = next row
curr  = current row

Space reduces from O(N^2) -> O(N)
*/

int minimumTotalSpaceOptimized(vector<vector<int>>& triangle)
{
    int n = triangle.size();

    vector<int> front(n), curr(n);

    // Last row initialization
    for(int j=0;j<n;j++)
        front[j] = triangle[n-1][j];

    // Move upwards
    for(int i=n-2;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {
            int down = triangle[i][j] + front[j];
            int diagonal = triangle[i][j] + front[j+1];

            curr[j] = min(down, diagonal);
        }

        front = curr;
    }

    return front[0];
}



/*
========================================================
MAIN FUNCTION
User gives triangle input
========================================================
*/

int main()
{
    int n;

    cout << "Enter number of rows in triangle: ";
    cin >> n;

    vector<vector<int>> triangle(n);

    cout << "Enter triangle values:\n";

    for(int i=0;i<n;i++)
    {
        triangle[i].resize(i+1);

        for(int j=0;j<=i;j++)
        {
            cin >> triangle[i][j];
        }
    }

    cout << "\nMinimum Path Sum (Memoization): "
         << minimumTotalMemo(triangle) << endl;

    cout << "Minimum Path Sum (Tabulation): "
         << minimumTotalTabulation(triangle) << endl;

    cout << "Minimum Path Sum (Space Optimized): "
         << minimumTotalSpaceOptimized(triangle) << endl;

    return 0;
}