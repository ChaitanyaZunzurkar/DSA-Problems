#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:

    /*****************************************************************
        MEMOIZATION (Top-Down DP)

        Intuition:
        -----------
        We need the minimum insertions required to make a string
        palindrome.

        Observation:
        ------------
        If we find the Longest Palindromic Subsequence (LPS),
        then the remaining characters must be inserted.

        Minimum Insertions = n - LPS

        LPS can be found by calculating the LCS between:
            original string
            reversed string

        State:
        -------
        dp[i][j] = LCS length between
                   s1[0...i] and s2[0...j]

        Time Complexity: O(n²)
        Space Complexity: O(n²) + O(n) recursion stack
    *****************************************************************/

    int solveMemo(int i, int j, string &s1, string &s2,
                  vector<vector<int>> &dp) {

        if (i < 0 || j < 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (s1[i] == s2[j]) {
            return dp[i][j] =
                   1 + solveMemo(i - 1, j - 1, s1, s2, dp);
        }

        return dp[i][j] =
               max(solveMemo(i - 1, j, s1, s2, dp),
                   solveMemo(i, j - 1, s1, s2, dp));
    }

    int minInsertionsMemoization(string s) {

        int n = s.size();

        string rev = s;
        reverse(rev.begin(), rev.end());

        vector<vector<int>> dp(n, vector<int>(n, -1));

        int lps = solveMemo(n - 1, n - 1, s, rev, dp);

        return n - lps;
    }

    /*****************************************************************
        TABULATION (Bottom-Up DP)

        Intuition:
        -----------
        Same idea as memoization.

        Instead of recursion, we build the DP table from
        smaller states to larger states.

        State:
        -------
        dp[i][j] = LCS length between

                   s1[0...i-1]
                   s2[0...j-1]

        Transition:
        -----------
        if characters match:
            dp[i][j] = 1 + dp[i-1][j-1]

        else:
            dp[i][j] =
            max(dp[i-1][j], dp[i][j-1])

        Time Complexity: O(n²)
        Space Complexity: O(n²)
    *****************************************************************/

    int minInsertionsTabulation(string s) {

        int n = s.size();

        string rev = s;
        reverse(rev.begin(), rev.end());

        vector<vector<int>> dp(n + 1,
                               vector<int>(n + 1, 0));

        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= n; j++) {

                if (s[i - 1] == rev[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] =
                        max(dp[i - 1][j],
                            dp[i][j - 1]);
                }
            }
        }

        int lps = dp[n][n];

        return n - lps;
    }

    /*****************************************************************
        SPACE OPTIMIZATION

        Intuition:
        -----------
        In tabulation, each row only depends on:

            previous row
            current row

        Therefore we do not need the entire DP table.

        We can keep only:
            prev -> previous row
            curr -> current row

        Time Complexity: O(n²)
        Space Complexity: O(n)
    *****************************************************************/

    int minInsertionsSpaceOptimized(string s) {

        int n = s.size();

        string rev = s;
        reverse(rev.begin(), rev.end());

        vector<int> prev(n + 1, 0);
        vector<int> curr(n + 1, 0);

        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= n; j++) {

                if (s[i - 1] == rev[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                }
                else {
                    curr[j] =
                        max(prev[j], curr[j - 1]);
                }
            }

            prev = curr;
        }

        int lps = prev[n];

        return n - lps;
    }
};

int main() {

    /*
        Input:
        ------
        A single string

        Example:
        abcaa

        Output:
        -------
        Minimum insertions required to make
        the string palindrome.
    */

    string s;

    cout << "Enter string: ";
    cin >> s;

    Solution obj;

    cout << "\nUsing Memoization: "
         << obj.minInsertionsMemoization(s);

    cout << "\nUsing Tabulation: "
         << obj.minInsertionsTabulation(s);

    cout << "\nUsing Space Optimization: "
         << obj.minInsertionsSpaceOptimized(s);

    return 0;
}