#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:

    /*******************************************************************
     * MEMOIZATION (Top-Down DP)
     *
     * INTUITION:
     * ----------
     * Let solve(i, j) represent the length of the Longest Common
     * Subsequence (LCS) between:
     *
     * text1[0...i] and text2[0...j]
     *
     * CASE 1:
     * If text1[i] == text2[j]
     * then this character must be part of the LCS.
     *
     * Therefore:
     * 1 + solve(i-1, j-1)
     *
     * CASE 2:
     * If characters are different,
     * we have two choices:
     *
     * 1. Skip current character from text1
     *    solve(i-1, j)
     *
     * 2. Skip current character from text2
     *    solve(i, j-1)
     *
     * Take maximum of both.
     *
     * OVERLAPPING SUBPROBLEMS:
     * ------------------------
     * Same states get computed repeatedly.
     * dp[i][j] stores already computed answers.
     *
     * TIME  : O(N*M)
     * SPACE : O(N*M) + O(N+M) recursion stack
     *******************************************************************/
    int memoHelper(int i,
                   int j,
                   string &text1,
                   string &text2,
                   vector<vector<int>> &dp)
    {
        if(i < 0 || j < 0)
            return 0;

        if(dp[i][j] != -1)
            return dp[i][j];

        if(text1[i] == text2[j])
        {
            return dp[i][j] =
                   1 + memoHelper(i - 1,
                                  j - 1,
                                  text1,
                                  text2,
                                  dp);
        }

        return dp[i][j] =
               max(memoHelper(i - 1, j, text1, text2, dp),
                   memoHelper(i, j - 1, text1, text2, dp));
    }

    int lcsMemoization(string text1, string text2)
    {
        int n = text1.size();
        int m = text2.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));

        return memoHelper(n - 1,
                          m - 1,
                          text1,
                          text2,
                          dp);
    }

    /*******************************************************************
     * TABULATION (Bottom-Up DP)
     *
     * INTUITION:
     * ----------
     * Memoization computes states recursively.
     * Tabulation computes the same states iteratively.
     *
     * dp[i][j] =
     * LCS length between text1[0...i] and text2[0...j]
     *
     * We fill the table from smaller states to larger states.
     *
     * MATCH:
     * -------
     * dp[i][j] = 1 + dp[i-1][j-1]
     *
     * NOT MATCH:
     * ----------
     * dp[i][j] =
     * max(dp[i-1][j], dp[i][j-1])
     *
     * Since our memoization had base case:
     *
     * i < 0 OR j < 0 => 0
     *
     * We handle those situations using boundary checks.
     *
     * TIME  : O(N*M)
     * SPACE : O(N*M)
     *******************************************************************/
    int lcsTabulation(string text1, string text2)
    {
        int n = text1.size();
        int m = text2.size();

        vector<vector<int>> dp(n, vector<int>(m, 0));

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(text1[i] == text2[j])
                {
                    dp[i][j] =
                        1 + ((i > 0 && j > 0)
                             ? dp[i - 1][j - 1]
                             : 0);
                }
                else
                {
                    int up =
                        (i > 0)
                        ? dp[i - 1][j]
                        : 0;

                    int left =
                        (j > 0)
                        ? dp[i][j - 1]
                        : 0;

                    dp[i][j] = max(up, left);
                }
            }
        }

        return dp[n - 1][m - 1];
    }

    /*******************************************************************
     * SPACE OPTIMIZATION
     *
     * INTUITION:
     * ----------
     * Observe the tabulation transition:
     *
     * dp[i][j] depends only on:
     *
     * 1. dp[i-1][j]     -> Previous Row
     * 2. dp[i][j-1]     -> Current Row
     * 3. dp[i-1][j-1]   -> Previous Row
     *
     * Therefore we don't need the entire matrix.
     *
     * We only need:
     *
     * prev[] -> previous row
     * curr[] -> current row
     *
     * Mapping:
     *
     * dp[i-1][j]     -> prev[j]
     * dp[i][j-1]     -> curr[j-1]
     * dp[i-1][j-1]   -> prev[j-1]
     *
     * This reduces space from O(N*M) to O(M).
     *
     * TIME  : O(N*M)
     * SPACE : O(M)
     *******************************************************************/
    int lcsSpaceOptimized(string text1, string text2)
    {
        int n = text1.size();
        int m = text2.size();

        vector<int> prev(m, 0);

        for(int i = 0; i < n; i++)
        {
            vector<int> curr(m, 0);

            for(int j = 0; j < m; j++)
            {
                if(text1[i] == text2[j])
                {
                    curr[j] =
                        1 + ((i > 0 && j > 0)
                             ? prev[j - 1]
                             : 0);
                }
                else
                {
                    int up =
                        (i > 0)
                        ? prev[j]
                        : 0;

                    int left =
                        (j > 0)
                        ? curr[j - 1]
                        : 0;

                    curr[j] = max(up, left);
                }
            }

            prev = curr;
        }

        return prev[m - 1];
    }
};

int main()
{
    string text1;
    string text2;

    cout << "Enter First String: ";
    cin >> text1;

    cout << "Enter Second String: ";
    cin >> text2;

    Solution obj;

    cout << "\nLCS Length using Memoization      : "
         << obj.lcsMemoization(text1, text2);

    cout << "\nLCS Length using Tabulation       : "
         << obj.lcsTabulation(text1, text2);

    cout << "\nLCS Length using Space Optimized  : "
         << obj.lcsSpaceOptimized(text1, text2);

    cout << endl;

    return 0;
}