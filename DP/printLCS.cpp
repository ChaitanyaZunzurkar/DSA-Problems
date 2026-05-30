/*
    Longest Common Subsequence (LCS) - Printing One LCS

    ---------------------------------------------------------
    INTUITION
    ---------------------------------------------------------

    We are given two strings s1 and s2.

    A subsequence is formed by deleting zero or more characters
    without changing the relative order of the remaining characters.

    Example:
        s1 = "abcde"

        Subsequences:
        "ace"
        "abd"
        "bce"
        etc.

    The Longest Common Subsequence (LCS) is the longest subsequence
    present in BOTH strings.

    Example:
        s1 = "abcde"
        s2 = "ace"

        LCS = "ace"
        Length = 3


    ---------------------------------------------------------
    DP STATE
    ---------------------------------------------------------

    dp[i][j] = Length of LCS between

                s1[0...i-1]
                s2[0...j-1]

    In other words, we consider the first i characters of s1
    and the first j characters of s2.


    ---------------------------------------------------------
    TRANSITION
    ---------------------------------------------------------

    Case 1:
    If characters match

        s1[i-1] == s2[j-1]

    then this character definitely contributes to the LCS.

        dp[i][j] = 1 + dp[i-1][j-1]


    Case 2:
    If characters do not match

        s1[i-1] != s2[j-1]

    then we have two choices:

        Ignore current character of s1
        Ignore current character of s2

        dp[i][j] =
        max(dp[i-1][j], dp[i][j-1])


    ---------------------------------------------------------
    RECONSTRUCTION OF ONE LCS
    ---------------------------------------------------------

    After filling the DP table:

        dp[n][m]

    contains the length of the LCS.

    We start from cell (n,m) and move backwards.

    If characters match:
        Put the character in answer.
        Move diagonally.

    Else:
        Move towards the direction having larger DP value.

    This traces one valid LCS.


    ---------------------------------------------------------
    TIME COMPLEXITY
    ---------------------------------------------------------

    DP Construction : O(n * m)

    Reconstruction  : O(n + m)

    Total           : O(n * m)


    ---------------------------------------------------------
    SPACE COMPLEXITY
    ---------------------------------------------------------

    O(n * m)
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:

    string printLCS(string s1, string s2) {

        int n = s1.size();
        int m = s2.size();

        /*
            Step 1:
            Create DP table.

            dp[i][j] stores LCS length for
            first i characters of s1
            first j characters of s2
        */
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        /*
            Step 2:
            Fill DP table
        */
        for(int i = 1; i <= n; i++) {

            for(int j = 1; j <= m; j++) {

                if(s1[i - 1] == s2[j - 1]) {

                    // Character contributes to LCS
                    dp[i][j] = 1 + dp[i - 1][j - 1];

                } else {

                    // Choose best among two possibilities
                    dp[i][j] = max(dp[i - 1][j],
                                   dp[i][j - 1]);
                }
            }
        }

        /*
            Length of LCS
        */
        int len = dp[n][m];

        /*
            Create answer string of required length.

            Example:
            len = 4

            ans = "    "
        */
        string ans(len, ' ');

        int i = n;
        int j = m;
        int index = len - 1;

        /*
            Step 3:
            Reconstruct one LCS by moving
            backwards in DP table.
        */
        while(i > 0 && j > 0) {

            /*
                Character is part of LCS
            */
            if(s1[i - 1] == s2[j - 1]) {

                ans[index] = s1[i - 1];

                index--;
                i--;
                j--;
            }

            /*
                Move towards larger DP value
            */
            else if(dp[i - 1][j] > dp[i][j - 1]) {

                i--;

            } else {

                j--;
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

    string lcs = obj.printLCS(s1, s2);

    cout << "\nLength of LCS = " << lcs.length() << endl;
    cout << "LCS = " << lcs << endl;

    return 0;
}