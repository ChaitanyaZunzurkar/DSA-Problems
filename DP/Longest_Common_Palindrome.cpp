#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:

    /*
    =====================================================
    MEMOIZATION (Top Down DP)
    -----------------------------------------------------
    INTUITION:
    We start from the last index of both strings.

    For every position:
    - If characters match:
        include that character
        move diagonally (i-1, j-1)

    - If characters don't match:
        either:
            skip character from string1
            OR
            skip character from string2

        take maximum of both.

    DP stores already calculated states
    to avoid repeated recursion.

    Time Complexity: O(N*M)
    Space Complexity: O(N*M) + recursion stack
    =====================================================
    */

    int memo(int i, int j, string &s1, string &s2,
             vector<vector<int>>& dp) {

        if (i < 0 || j < 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (s1[i] == s2[j]) {
            return dp[i][j] =
                1 + memo(i - 1, j - 1, s1, s2, dp);
        }

        return dp[i][j] =
            max(
                memo(i - 1, j, s1, s2, dp),
                memo(i, j - 1, s1, s2, dp)
            );
    }

    int lcsMemo(string s1, string s2) {

        int n = s1.size();
        int m = s2.size();

        vector<vector<int>> dp(
            n,
            vector<int>(m, -1)
        );

        return memo(n - 1, m - 1, s1, s2, dp);
    }


    /*
    =====================================================
    TABULATION (Bottom Up DP)
    -----------------------------------------------------
    INTUITION:
    Build answer from smaller subproblems.

    dp[i][j] =
    LCS length for:
    first i chars of s1
    first j chars of s2

    Transition:

    if match:
        dp[i][j]=1+dp[i-1][j-1]

    else:
        take max of:
        upper cell
        left cell

    Time Complexity: O(N*M)
    Space Complexity: O(N*M)
    =====================================================
    */

    int lcsTabulation(string s1, string s2) {

        int n = s1.size();
        int m = s2.size();

        vector<vector<int>> dp(
            n + 1,
            vector<int>(m + 1, 0)
        );

        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= m; j++) {

                if (s1[i - 1] == s2[j - 1]) {

                    dp[i][j] =
                        1 + dp[i - 1][j - 1];

                } else {

                    dp[i][j] =
                        max(
                            dp[i - 1][j],
                            dp[i][j - 1]
                        );
                }
            }
        }

        return dp[n][m];
    }


    /*
    =====================================================
    SPACE OPTIMIZATION
    -----------------------------------------------------
    INTUITION:

    Observe:
    current row only depends on:
    previous row
    current row's previous value

    So instead of entire matrix,
    store only:

    prev → previous row
    curr → current row

    Space reduces:
    O(N*M)
    → O(M)

    Time Complexity: O(N*M)
    Space Complexity: O(M)
    =====================================================
    */

    int lcsSpaceOptimization(string s1, string s2) {

        int n = s1.size();
        int m = s2.size();

        vector<int> prev(m + 1, 0);
        vector<int> curr(m + 1, 0);

        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= m; j++) {

                if (s1[i - 1] == s2[j - 1]) {

                    curr[j] =
                        1 + prev[j - 1];

                } else {

                    curr[j] =
                        max(
                            prev[j],
                            curr[j - 1]
                        );
                }
            }

            prev = curr;
        }

        return prev[m];
    }
};


/*
=====================================================
MAIN FUNCTION
-----------------------------------------------------
Take both strings from user
Call all three approaches
Print results
=====================================================
*/

int main() {

    string s1, s2;

    cout << "Enter first string: ";
    cin >> s1;

    cout << "Enter second string: ";
    cin >> s2;

    Solution obj;

    cout << "\nMemoization Answer: "
         << obj.lcsMemo(s1, s2);

    cout << "\nTabulation Answer: "
         << obj.lcsTabulation(s1, s2);

    cout << "\nSpace Optimization Answer: "
         << obj.lcsSpaceOptimization(s1, s2);

    return 0;
}