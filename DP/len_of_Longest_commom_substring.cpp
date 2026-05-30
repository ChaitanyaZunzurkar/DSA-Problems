#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:

    /*
    ===================================================================
    INTUITION:
    ===================================================================

    We need to find the length of the Longest Common Substring between
    two strings.

    Difference between Subsequence and Substring:
    ---------------------------------------------
    Subsequence:
        Characters can be non-contiguous.
        Example:
        "abcde" -> "ace" is a subsequence.

    Substring:
        Characters must be contiguous.
        Example:
        "abcde" -> "bcd" is a substring.

    -------------------------------------------------------------------
    DP STATE:
    -------------------------------------------------------------------

    dp[i][j] = Length of the longest common substring ending at:
               s1[i-1] and s2[j-1]

    Meaning:
    If characters match, we extend the previous substring.

    -------------------------------------------------------------------
    TRANSITION:
    -------------------------------------------------------------------

    If s1[i-1] == s2[j-1]

        dp[i][j] = 1 + dp[i-1][j-1]

    because the current matching character extends the substring that
    ended at the previous indices.

    Else

        dp[i][j] = 0

    because a substring must be contiguous, so a mismatch breaks the
    current substring completely.

    -------------------------------------------------------------------
    ANSWER:
    -------------------------------------------------------------------

    Keep track of the maximum value found in the DP table because the
    longest common substring can end at any position.

    -------------------------------------------------------------------
    TIME COMPLEXITY:
    -------------------------------------------------------------------
    O(N * M)

    -------------------------------------------------------------------
    SPACE COMPLEXITY:
    -------------------------------------------------------------------
    O(N * M)

    ===================================================================
    */

    int longCommSubstr(string& s1, string& s2) {
        int n = s1.size();
        int m = s2.size();

        // DP table initialized with 0
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        int ans = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {

                // Characters match
                if (s1[i - 1] == s2[j - 1]) {

                    // Extend previous common substring
                    dp[i][j] = 1 + dp[i - 1][j - 1];

                    // Update maximum length found so far
                    ans = max(ans, dp[i][j]);
                }
                else {

                    // Mismatch breaks the substring
                    dp[i][j] = 0;
                }
            }
        }

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

    int result = obj.longCommSubstr(s1, s2);

    cout << "\nLength of Longest Common Substring = "
         << result << endl;

    return 0;
}