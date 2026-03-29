#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    ============================================================
    1. RECURSION (BRUTE FORCE)
    ============================================================
    Intuition:
    - At each '*', we have 3 choices:
        1. Treat as '('
        2. Treat as ')'
        3. Treat as empty
    - Try all possibilities.
    - Track 'count' = number of open brackets.

    Problems:
    - Exponential time: O(3^n)
    */

    bool solveRec(string &s, int idx, int count) {
        if(count < 0) return false; // too many ')'
        if(idx == s.size()) return count == 0;

        if(s[idx] == '(') {
            return solveRec(s, idx + 1, count + 1);
        }
        else if(s[idx] == ')') {
            return solveRec(s, idx + 1, count - 1);
        }
        else { // '*'
            return solveRec(s, idx + 1, count + 1) || // '('
                   solveRec(s, idx + 1, count - 1) || // ')'
                   solveRec(s, idx + 1, count);       // empty
        }
    }


    /*
    ============================================================
    2. MEMOIZATION (TOP-DOWN DP)
    ============================================================
    Intuition:
    - Same as recursion, but store results.
    - dp[idx][count] = whether valid from this state

    Time: O(n^2)
    Space: O(n^2)
    */

    bool solveMemo(string &s, int idx, int count, vector<vector<int>> &dp) {
        if(count < 0) return false;
        if(idx == s.size()) return count == 0;

        if(dp[idx][count] != -1) return dp[idx][count];

        if(s[idx] == '(') {
            return dp[idx][count] = solveMemo(s, idx + 1, count + 1, dp);
        }
        else if(s[idx] == ')') {
            return dp[idx][count] = solveMemo(s, idx + 1, count - 1, dp);
        }
        else {
            return dp[idx][count] =
                solveMemo(s, idx + 1, count + 1, dp) ||
                solveMemo(s, idx + 1, count - 1, dp) ||
                solveMemo(s, idx + 1, count, dp);
        }
    }


    /*
    ============================================================
    3. TABULATION (BOTTOM-UP DP)
    ============================================================
    Intuition:
    - Build dp from back.
    - dp[i][j] = can we form valid string from i with j open brackets

    Time: O(n^2)
    Space: O(n^2)
    */

    bool solveTab(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(n + 1, false));

        dp[n][0] = true; // base case

        for(int i = n - 1; i >= 0; i--) {
            for(int count = 0; count <= n; count++) {
                if(s[i] == '(') {
                    if(count + 1 <= n)
                        dp[i][count] = dp[i+1][count+1];
                }
                else if(s[i] == ')') {
                    if(count - 1 >= 0)
                        dp[i][count] = dp[i+1][count-1];
                }
                else {
                    bool ans = false;

                    if(count + 1 <= n)
                        ans |= dp[i+1][count+1];

                    if(count - 1 >= 0)
                        ans |= dp[i+1][count-1];

                    ans |= dp[i+1][count];

                    dp[i][count] = ans;
                }
            }
        }

        return dp[0][0];
    }


    /*
    ============================================================
    4. GREEDY (OPTIMAL APPROACH)
    ============================================================
    Intuition:
    - Maintain a RANGE of possible open brackets:
        mini = minimum open brackets
        maxi = maximum open brackets

    Why it works:
    - '*' gives flexibility → we track range instead of exact value

    Rules:
    '(' → mini++, maxi++
    ')' → mini--, maxi--
    '*' → mini--, maxi++

    Important:
    - mini can't go below 0
    - if maxi < 0 → invalid immediately

    Time: O(n)
    Space: O(1)
    */

    bool solveGreedy(string s) {
        int mini = 0, maxi = 0;

        for(char ch : s) {
            if(ch == '(') {
                mini++;
                maxi++;
            }
            else if(ch == ')') {
                mini--;
                maxi--;
            }
            else { // '*'
                mini--;   // assume ')'
                maxi++;   // assume '('
            }

            if(maxi < 0) return false; // too many ')'
            if(mini < 0) mini = 0;     // reset
        }

        return mini == 0;
    }
};


int main() {
    string s;
    cout << "Enter string: ";
    cin >> s;

    Solution obj;

    cout << "\n--- Results ---\n";

    // Recursion (can be slow for large input)
    cout << "Recursion: ";
    cout << (obj.solveRec(s, 0, 0) ? "Valid\n" : "Invalid\n");

    // Memoization
    vector<vector<int>> dp(s.size(), vector<int>(s.size()+1, -1));
    cout << "Memoization: ";
    cout << (obj.solveMemo(s, 0, 0, dp) ? "Valid\n" : "Invalid\n");

    // Tabulation
    cout << "Tabulation: ";
    cout << (obj.solveTab(s) ? "Valid\n" : "Invalid\n");

    // Greedy (Best)
    cout << "Greedy: ";
    cout << (obj.solveGreedy(s) ? "Valid\n" : "Invalid\n");

    return 0;
}