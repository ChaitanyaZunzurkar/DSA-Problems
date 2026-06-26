#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {

public:

    /*************************************************
                1. RECURSION
    **************************************************
     * INTUITION:
     * We want to find how many times string `t` appears as a subsequence in string `s`.
     * We start comparing both strings from the end (indices i and j).
     * * Base Cases:
     * - If j < 0: We have successfully matched all characters of `t`. Return 1.
     * - If i < 0: We have exhausted `s` but `t` still has characters left. Return 0.
     * * Choices:
     * - If s[i] == t[j]: We have two valid options:
     * 1. MATCH: Use s[i] to match t[j] and move both pointers left (i-1, j-1).
     * 2. SKIP: Don't use s[i] for this match, and keep looking for t[j] 
     * in the remaining parts of `s` (i-1, j).
     * Total ways = MATCH + SKIP.
     * * - If s[i] != t[j]: We cannot match, so our only option is to skip s[i] 
     * and keep looking for t[j] in the rest of `s` (i-1, j).
     * * COMPLEXITY:
     * - Time: O(2^N) where N is the length of s (exponential tree of choices).
     * - Space: O(N + M) for the auxiliary recursion stack space.
     **************************************************/

    int solveRec(int i, int j, string &s, string &t)
    {
        if(j < 0)
            return 1; // Target string exhausted: found a valid subsequence

        if(i < 0)
            return 0; // Source string exhausted before target string

        if(s[i] == t[j])
        {
            // Two choices: Use the matched character OR skip it
            return solveRec(i-1, j-1, s, t) + solveRec(i-1, j, s, t);
        }

        // Characters don't match: Skip the character in 's'
        return solveRec(i-1, j, s, t);
    }

    int numDistinctRec(string s, string t)
    {
        return solveRec(s.size()-1, t.size()-1, s, t);
    }

    /*************************************************
                2. MEMOIZATION (Top-Down DP)
    **************************************************
     * INTUITION:
     * The recursive approach recalculates the same states (i, j) multiple times.
     * To avoid this "Overlapping Subproblems" issue, we cache the results in 
     * a 2D array `dp`, where dp[i][j] stores the result for s[0...i] and t[0...j].
     * * Before computing for a state (i, j), we check if it has already been computed 
     * (i.e., dp[i][j] != -1). If yes, we return the cached value.
     * * COMPLEXITY:
     * - Time: O(N * M) where N = len(s) and M = len(t).
     * - Space: O(N * M) for the DP table + O(N + M) for recursion stack.
     **************************************************/

    unsigned long long solveMemo(
        int i, int j, string &s, string &t, vector<vector<long long>> &dp)
    {
        if(j < 0)
            return 1;

        if(i < 0)
            return 0;

        if(dp[i][j] != -1)
            return dp[i][j]; // Return cached result

        if(s[i] == t[j])
        {
            // Store the result before returning
            return dp[i][j] = solveMemo(i-1, j-1, s, t, dp) + solveMemo(i-1, j, s, t, dp);
        }

        return dp[i][j] = solveMemo(i-1, j, s, t, dp);
    }

    int numDistinctMemo(string s, string t)
    {
        int n = s.size();
        int m = t.size();

        // dp initialized with -1 to indicate uncomputed states
        vector<vector<long long>> dp(n, vector<long long>(m, -1));

        return solveMemo(n-1, m-1, s, t, dp);
    }

    /*************************************************
                3. TABULATION (Bottom-Up DP)
    **************************************************
     * INTUITION:
     * We convert the Memoization approach to an iterative one to save recursion 
     * stack space. Since negative indices are hard to represent in an array, 
     * we shift our indices by 1. 
     * - dp[i][j] now means the answer for s of length 'i' and t of length 'j'.
     * * Base Case Translation:
     * - j = 0 means target string 't' is empty. An empty string is a subsequence 
     * of any string exactly 1 time. So, dp[i][0] = 1 for all i.
     * - i = 0 (and j > 0) means 's' is empty but 't' is not. Ways = 0.
     * * State Transition:
     * - If s[i-1] == t[j-1]: dp[i][j] = dp[i-1][j-1] (Match) + dp[i-1][j] (Skip)
     * - If s[i-1] != t[j-1]: dp[i][j] = dp[i-1][j] (Skip only)
     * * COMPLEXITY:
     * - Time: O(N * M)
     * - Space: O(N * M) for the DP table. Recursion stack space is eliminated.
     **************************************************/

    int numDistinctTab(string s, string t)
    {
        int n = s.size();
        int m = t.size();

        // Using unsigned long long to prevent integer overflow for large answers
        vector<vector<unsigned long long>> dp(n+1, vector<unsigned long long>(m+1,0));

        // Base case: Empty target string 't' can be matched exactly 1 way
        for(int i=0;i<=n;i++)
            dp[i][0]=1;

        // Base case: Empty source string 's' implies 0 ways (already set by initialization)
        
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(s[i-1]==t[j-1])
                {
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                }
                else
                {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        return dp[n][m];
    }

    /*************************************************
            4. SPACE OPTIMIZATION (1D DP Array)
    **************************************************
     * INTUITION:
     * If we look at the Tabulation transition:
     * dp[i][j] relies ONLY on the previous row: dp[i-1][j-1] and dp[i-1][j].
     * We don't need the entire N x M matrix. A single 1D array of size M+1 is enough.
     * * Why loop 'j' backward?
     * Because dp[j] relies on dp[j-1] from the *previous* row.
     * If we iterate 'j' forward (from 1 to m), we will overwrite dp[j-1] with the 
     * current row's data before we can use it to calculate dp[j]. 
     * By iterating backwards, dp[j-1] retains the unmodified value from the previous row.
     * * COMPLEXITY:
     * - Time: O(N * M)
     * - Space: O(M) where M is the length of string `t`. Highly optimal!
     **************************************************/

    int numDistinct(string s, string t)
    {
        int n = s.size();
        int m = t.size();

        // 1D array representing the previous row, size M+1
        vector<unsigned long long> dp(m+1,0);

        // Base case: Empty target string 't' can be matched 1 way
        dp[0]=1;

        for(int i=1;i<=n;i++)
        {
            // Iterate backwards to avoid overwriting needed values from the previous row
            for(int j=m;j>=1;j--)
            {
                if(s[i-1]==t[j-1])
                {
                    // equivalent to: dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
                    dp[j] += dp[j-1];
                }
                // if they don't match, dp[j] remains dp[j] (equivalent to dp[i][j] = dp[i-1][j])
            }
        }

        return dp[m];
    }
};

int main()
{
    Solution obj;

    string s = "babgbag";
    string t = "bag";

    cout << "Recursion          : "
         << obj.numDistinctRec(s,t) << endl;

    cout << "Memoization        : "
         << obj.numDistinctMemo(s,t) << endl;

    cout << "Tabulation         : "
         << obj.numDistinctTab(s,t) << endl;

    cout << "Space Optimisation : "
         << obj.numDistinct(s,t) << endl;
 
    return 0;
}