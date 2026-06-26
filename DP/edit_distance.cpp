#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*************************************************
                1. MEMOIZATION (Top-Down DP)
    **************************************************
     * INTUITION:
     * We want to find the minimum operations to convert s1[0..i] to s2[0..j].
     * We compare characters from the end of both strings.
     * * Base Cases:
     * - If j < 0: String s2 is empty. We must delete all remaining characters 
     * in s1. Number of deletions = i + 1.
     * - If i < 0: String s1 is empty. We must insert all remaining characters 
     * of s2 into s1. Number of insertions = j + 1.
     * * Choices:
     * - If s1[i] == s2[j]: Characters match. No operation needed. 
     * Move both pointers left: solve(i-1, j-1).
     * - If s1[i] != s2[j]: We have 3 choices, each costing 1 operation:
     * 1. Insert: Conceptually insert s2[j] into s1. Now they match, so 
     * we move the s2 pointer left, but s1 pointer stays: solve(i, j-1).
     * 2. Delete: Delete s1[i]. Move s1 pointer left: solve(i-1, j).
     * 3. Replace: Replace s1[i] with s2[j]. Now they match, so move 
     * both pointers left: solve(i-1, j-1).
     * We take the minimum of these three choices.
     * * COMPLEXITY:
     * - Time: O(N * M) where N = len(s1), M = len(s2)
     * - Space: O(N * M) for the DP table + O(N + M) for the recursion stack.
     **************************************************/
    int solve(int i, int j, string &s1, string &s2, vector<vector<int>> &dp) {
        if(j < 0) return i + 1;
        if(i < 0) return j + 1;

        if(dp[i][j] != -1) return dp[i][j];

        if(s1[i] == s2[j]) {
            return dp[i][j] = solve(i-1, j-1, s1, s2, dp);
        }

        int insertOp  = 1 + solve(i, j-1, s1, s2, dp);
        int deleteOp  = 1 + solve(i-1, j, s1, s2, dp);
        int replaceOp = 1 + solve(i-1, j-1, s1, s2, dp);

        return dp[i][j] = min({insertOp, deleteOp, replaceOp});
    }

    int minDistanceMemo(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(n-1, m-1, word1, word2, dp);
    }

    /*************************************************
                2. TABULATION (Bottom-Up DP)
    **************************************************
     * INTUITION:
     * To avoid the recursion stack space, we build the solution iteratively.
     * We use a 1-based index to handle negative indices easily. 
     * dp[i][j] represents the minimum operations to convert the first 'i' 
     * characters of word1 to the first 'j' characters of word2.
     * * Base Cases Translation:
     * - dp[i][0] = i (Converting a string of length i to an empty string requires i deletions)
     * - dp[0][j] = j (Converting an empty string to a string of length j requires j insertions)
     * * COMPLEXITY:
     * - Time: O(N * M)
     * - Space: O(N * M) for the 2D DP matrix. Recursion stack eliminated.
     **************************************************/
    int minDistanceTab(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        // Base cases
        for(int i = 0; i <= n; i++) dp[i][0] = i;
        for(int j = 0; j <= m; j++) dp[0][j] = j;

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = min({
                        1 + dp[i][j-1],    // Insert
                        1 + dp[i-1][j],    // Delete
                        1 + dp[i-1][j-1]   // Replace
                    });
                }
            }
        }
        return dp[n][m];
    }

    /*************************************************
            3. SPACE OPTIMIZATION (1D DP Array)
    **************************************************
     * INTUITION:
     * If we look at the Tabulation transition, computing dp[i][j] only 
     * requires values from the current row (dp[i][j-1]) and the previous 
     * row (dp[i-1][j], dp[i-1][j-1]). 
     * * We don't need the entire N x M matrix. We just need two 1D arrays:
     * - `prev`: Represents the previous row (i-1)
     * - `curr`: Represents the current row being calculated (i)
     * * Notice that for every new row 'i', the first element curr[0] must be 
     * set to 'i' (equivalent to dp[i][0] = i).
     * * COMPLEXITY:
     * - Time: O(N * M)
     * - Space: O(M) where M is the length of word2. This is highly optimal!
     **************************************************/
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        
        vector<int> prev(m+1, 0), curr(m+1, 0);

        // Base case: 0th row (word1 is empty)
        for(int j = 0; j <= m; j++) {
            prev[j] = j;
        }

        for(int i = 1; i <= n; i++) {
            // Base case for the 0th column of the current row (word2 is empty)
            curr[0] = i; 
            
            for(int j = 1; j <= m; j++) {
                if(word1[i-1] == word2[j-1]) {
                    curr[j] = prev[j-1];
                } else {
                    curr[j] = min({
                        1 + curr[j-1],  // Insert
                        1 + prev[j],    // Delete
                        1 + prev[j-1]   // Replace
                    });
                }
            }
            // Move current row data to previous row for the next iteration
            prev = curr;
        }

        return prev[m];
    }
};

// Main function to test the implementations
int main() {
    Solution obj;

    string word1 = "horse";
    string word2 = "ros";

    cout << "--- Edit Distance Problem ---" << endl;
    cout << "Word 1: " << word1 << endl;
    cout << "Word 2: " << word2 << endl << endl;

    cout << "Memoization Result    : " << obj.minDistanceMemo(word1, word2) << endl;
    cout << "Tabulation Result     : " << obj.minDistanceTab(word1, word2) << endl;
    cout << "Space Optimized Result: " << obj.minDistance(word1, word2) << endl;

    return 0;
}