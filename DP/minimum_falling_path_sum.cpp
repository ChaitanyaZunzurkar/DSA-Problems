#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*-----------------------------------------------------------
    INTUITION (Memoization - Top Down DP)

    We want the minimum falling path sum in the matrix.
    From each cell we can move to:
        1. Down       -> (row+1, col)
        2. Down-Left  -> (row+1, col-1)
        3. Down-Right -> (row+1, col+1)

    Instead of recomputing paths repeatedly, we store results
    in a DP table.

    Steps:
    - Recursively compute the minimum cost from current cell
      to the bottom.
    - Store result in dp[row][col] to avoid recomputation.

    Time Complexity  : O(n^2)
    Space Complexity : O(n^2) + recursion stack
    -----------------------------------------------------------*/

    int solveMemo(vector<vector<int>>& matrix, int row, int col, vector<vector<int>>& dp) {
        int n = matrix.size();

        if(col < 0 || col >= n) return INT_MAX;

        if(row == n - 1)
            return matrix[row][col];

        if(dp[row][col] != -1)
            return dp[row][col];

        int down = solveMemo(matrix, row+1, col, dp);
        int left = solveMemo(matrix, row+1, col-1, dp);
        int right = solveMemo(matrix, row+1, col+1, dp);

        return dp[row][col] = matrix[row][col] + min({down, left, right});
    }

    int memoization(vector<vector<int>>& matrix) {
        int n = matrix.size();

        vector<vector<int>> dp(n, vector<int>(n, -1));

        int ans = INT_MAX;

        for(int j = 0; j < n; j++) {
            ans = min(ans, solveMemo(matrix, 0, j, dp));
        }

        return ans;
    }


    /*-----------------------------------------------------------
    INTUITION (Tabulation - Bottom Up DP)

    Instead of recursion, we build the solution row by row.

    Idea:
    dp[i][j] = minimum cost to reach cell (i,j)

    Transition:
    We come from previous row:
        dp[i][j] = matrix[i][j] +
                   min(
                        dp[i-1][j],      // up
                        dp[i-1][j-1],    // up-left
                        dp[i-1][j+1]     // up-right
                   )

    Steps:
    1. First row is same as matrix because path starts there.
    2. Fill rows from top to bottom.
    3. Answer = minimum value in last row.

    Time Complexity  : O(n^2)
    Space Complexity : O(n^2)
    -----------------------------------------------------------*/

    int tabulation(vector<vector<int>>& matrix) {
        int n = matrix.size();

        vector<vector<int>> dp(n, vector<int>(n, 0));

        for(int j = 0; j < n; j++)
            dp[0][j] = matrix[0][j];

        for(int i = 1; i < n; i++) {
            for(int j = 0; j < n; j++) {

                int up = dp[i-1][j];

                int left = INT_MAX;
                if(j-1 >= 0)
                    left = dp[i-1][j-1];

                int right = INT_MAX;
                if(j+1 < n)
                    right = dp[i-1][j+1];

                dp[i][j] = matrix[i][j] + min({up, left, right});
            }
        }

        int ans = INT_MAX;

        for(int j = 0; j < n; j++)
            ans = min(ans, dp[n-1][j]);

        return ans;
    }


    /*-----------------------------------------------------------
    INTUITION (Space Optimized DP)

    Observe that to compute row i we only need row i-1.

    So instead of storing the entire dp table,
    we store only:
        prev -> previous row
        curr -> current row

    After computing curr row we update prev = curr.

    This reduces memory from O(n^2) to O(n).

    Time Complexity  : O(n^2)
    Space Complexity : O(n)
    -----------------------------------------------------------*/

    int spaceOptimized(vector<vector<int>>& matrix) {
        int n = matrix.size();

        vector<int> prev(n);

        for(int j = 0; j < n; j++)
            prev[j] = matrix[0][j];

        for(int i = 1; i < n; i++) {

            vector<int> curr(n);

            for(int j = 0; j < n; j++) {

                int up = prev[j];

                int left = INT_MAX;
                if(j-1 >= 0)
                    left = prev[j-1];

                int right = INT_MAX;
                if(j+1 < n)
                    right = prev[j+1];

                curr[j] = matrix[i][j] + min({up, left, right});
            }

            prev = curr;
        }

        int ans = INT_MAX;

        for(int j = 0; j < n; j++)
            ans = min(ans, prev[j]);

        return ans;
    }
};


int main() {

    int n;

    cout << "Enter size of matrix (n x n): ";
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));

    cout << "Enter matrix values:\n";

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> matrix[i][j];

    Solution obj;

    cout << "\nMemoization Answer: "
         << obj.memoization(matrix) << endl;

    cout << "Tabulation Answer: "
         << obj.tabulation(matrix) << endl;

    cout << "Space Optimized Answer: "
         << obj.spaceOptimized(matrix) << endl;

}