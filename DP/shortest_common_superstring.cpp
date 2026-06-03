#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    --------------------------------------------------------------------
    INTUITION

    We want the shortest string that contains both s1 and s2 as
    subsequences.

    Observation:
    Characters that are common to both strings do not need to be
    repeated. Therefore, if we know the Longest Common Subsequence (LCS),
    we can use it as a backbone while merging both strings.

    Example:
    s1 = "abac"
    s2 = "cab"

    LCS = "ab"

    Instead of writing both strings completely:
    "abac" + "cab" = length 7

    We reuse the common characters ('a' and 'b') and obtain:
    "cabac" = length 5

    Formula:
    SCS Length = n + m - LCS Length

    --------------------------------------------------------------------
    APPROACH

    1. Build the LCS DP table.
       dp[i][j] = length of LCS of first i characters of s1
                  and first j characters of s2.

    2. Backtrack from dp[n][m].

       Case 1:
       If characters match:
           Take that character once.
           Move diagonally.

       Case 2:
       Characters do not match.

           If dp[i-1][j] > dp[i][j-1]
               take s1[i-1]
               move up

           Else
               take s2[j-1]
               move left

    3. Add any remaining characters from either string.

    4. Since we build the answer from the end,
       reverse the constructed string.

    Time Complexity  : O(n * m)
    Space Complexity : O(n * m)

    --------------------------------------------------------------------
    */

    string shortestCommonSupersequence(string s1, string s2) {

        int n = s1.size();
        int m = s2.size();

        // DP table for LCS
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Build LCS table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {

                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j],
                                   dp[i][j - 1]);
                }
            }
        }

        string ans = "";

        int i = n;
        int j = m;

        /*
        Backtracking to construct SCS

        Whenever characters are equal,
        include them only once.

        Otherwise move towards the larger
        LCS value and include that character.
        */
        while (i > 0 && j > 0) {

            if (s1[i - 1] == s2[j - 1]) {

                ans.push_back(s1[i - 1]);

                i--;
                j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) {

                ans.push_back(s1[i - 1]);
                i--;
            }
            else {

                ans.push_back(s2[j - 1]);
                j--;
            }
        }

        // Add remaining characters of s1
        while (i > 0) {
            ans.push_back(s1[i - 1]);
            i--;
        }

        // Add remaining characters of s2
        while (j > 0) {
            ans.push_back(s2[j - 1]);
            j--;
        }

        // Reverse because we built answer backwards
        reverse(ans.begin(), ans.end());

        return ans;
    }
};

int main() {

    string s1, s2;

    cout << "Enter first string: ";
    cin >> s1;

    cout << "Enter second string: ";
    cin >> s2;

    Solution obj;

    string scs = obj.shortestCommonSupersequence(s1, s2);

    cout << "\nShortest Common Supersequence = "
         << scs << endl;

    cout << "Length = " << scs.length() << endl;

    return 0;
}