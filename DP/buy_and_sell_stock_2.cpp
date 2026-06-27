#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /* =====================================================================
       APPROACH 1: Plain Recursion (Time Limit Exceeded)
       ---------------------------------------------------------------------
       Intuition: 
       On every day, we have two choices based on our current state:
       1. If we can buy (buy == 1): We either BUY the stock today (subtract 
          price from profit) or DO NOT BUY (skip to the next day).
       2. If we can sell (buy == 0): We either SELL the stock today (add 
          price to profit) or DO NOT SELL (skip to the next day).
       We explore all combinations and return the maximum profit.
       
       Time Complexity: O(2^N) - Two branches at every step.
       Space Complexity: O(N) - Recursive stack space.
       ===================================================================== */
    int solveRec(int idx, int buy, vector<int> &prices) {
        if (idx == prices.size()) return 0; // Base case: no more days left
    
        int profit = 0;
        if (buy) {
            int take = -prices[idx] + solveRec(idx + 1, 0, prices);
            int notTake = 0 + solveRec(idx + 1, 1, prices);
            profit = max(take, notTake);
        } else {
            int take = prices[idx] + solveRec(idx + 1, 1, prices);
            int notTake = 0 + solveRec(idx + 1, 0, prices);
            profit = max(take, notTake);
        }
        return profit;
    }

    /* =====================================================================
       APPROACH 2: Memoization (Top-Down DP)
       ---------------------------------------------------------------------
       Intuition: 
       The recursive approach solves overlapping subproblems (e.g., reaching 
       day 3 with 'buy = 1' multiple ways). We can cache these results in a 
       2D array `dp[idx][buy]` to avoid redundant calculations.
       
       Time Complexity: O(N * 2) = O(N)
       Space Complexity: O(N * 2) + O(N) = O(N) for DP array and recursion stack.
       ===================================================================== */
    int solveMemo(int idx, int buy, vector<int> &prices, vector<vector<int>> &dp) {
        if (idx == prices.size()) return 0;
        
        if (dp[idx][buy] != -1) return dp[idx][buy];

        long profit = 0;
        if (buy) {
            int take = -prices[idx] + solveMemo(idx + 1, 0, prices, dp);
            int notTake = 0 + solveMemo(idx + 1, 1, prices, dp);
            profit = max(take, notTake);
        } else {
            int take = prices[idx] + solveMemo(idx + 1, 1, prices, dp);
            int notTake = 0 + solveMemo(idx + 1, 0, prices, dp);
            profit = max(take, notTake);
        }
        return dp[idx][buy] = profit;
    }

    /* =====================================================================
       APPROACH 3: Tabulation (Bottom-Up DP)
       ---------------------------------------------------------------------
       Intuition: 
       Instead of using recursion, we build the solution from the base case 
       (last day) up to the first day. We create a DP table of size [N+1][2].
       The state transitions remain exactly the same as memoization.
       
       Time Complexity: O(N)
       Space Complexity: O(N * 2) = O(N) for the DP table. (No recursion stack)
       ===================================================================== */
    int maxProfitTabulation(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    
        // Base case is inherently handled since vectors are initialized to 0.
    
        for (int i = n - 1; i >= 0; i--) {
            for (int buy = 0; buy < 2; buy++) {
                if (buy) {
                    int take = -prices[i] + dp[i + 1][0];
                    int notTake = 0 + dp[i + 1][1];
                    dp[i][buy] = max(take, notTake);
                } else {
                    int take = prices[i] + dp[i + 1][1];
                    int notTake = 0 + dp[i + 1][0];
                    dp[i][buy] = max(take, notTake);
                }
            }
        }
        return dp[0][1];
    }

    /* =====================================================================
       APPROACH 4: Space Optimization (Using 2 Arrays)
       ---------------------------------------------------------------------
       Intuition: 
       Notice in Tabulation that to calculate the values for day `i` (dp[i]), 
       we ONLY need the values from day `i+1` (dp[i+1]). 
       We don't need the entire N-sized array in memory. We can just use two 
       arrays of size 2: `next` (representing day i+1) and `curr` (day i).
       
       Time Complexity: O(N)
       Space Complexity: O(1) - specifically O(2 + 2), which is constant.
       ===================================================================== */
    int maxProfitSpaceOpt1(vector<int>& prices) {
        int n = prices.size();
        vector<int> next(2, 0), curr(2, 0); // Size 2 because 'buy' is only 0 or 1
    
        for (int i = n - 1; i >= 0; i--) {
            for (int buy = 0; buy < 2; buy++) {
                if (buy) {
                    curr[buy] = max(-prices[i] + next[0], 0 + next[1]);
                } else {
                    curr[buy] = max(prices[i] + next[1], 0 + next[0]);
                }
            }
            next = curr; // Move current computations to 'next' for the preceding day
        }
        return next[1];
    }

    /* =====================================================================
       APPROACH 5: Ultimate Space Optimization (Single Array / Variables)
       ---------------------------------------------------------------------
       Intuition:
       We can take Approach 4 even further. Because the inner loop variables 
       only depend on previous states that don't overwrite each other in a 
       conflicting way (if assigned carefully), we can actually manage this 
       with a single array of size 2, or just 4 plain integer variables.
       Here we use a single array of size 2 called `next`.
       
       Time Complexity: O(N)
       Space Complexity: O(1)
       ===================================================================== */
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        
        // next[1] represents max profit when we CAN buy.
        // next[0] represents max profit when we CANNOT buy (must sell).
        vector<int> next(2, 0); 
        
        for (int i = n - 1; i >= 0; i--) {
            // We need temporary variables to prevent overwriting values 
            // before we use them for the other state.
            int next_buy_1 = max(-prices[i] + next[0], 0 + next[1]);
            int next_buy_0 = max(prices[i] + next[1], 0 + next[0]);
            
            // Update the single array
            next[1] = next_buy_1;
            next[0] = next_buy_0;
        }

        return next[1]; // We start at day 0 with the ability to buy
    }
};

int main() {
    int n;
    cout << "Enter the number of days: ";
    if (!(cin >> n)) return 0;

    vector<int> prices(n);
    cout << "Enter the stock prices for each day separated by spaces:\n";
    for(int i = 0; i < n; i++) {
        cin >> prices[i];
    }

    Solution sol;
    
    // Using the fully optimized approach
    int result = sol.maxProfit(prices);
    
    cout << "\n==============================\n";
    cout << "Maximum Profit: " << result << endl;
    cout << "==============================\n";

    /* // To test the memoization approach, you would uncomment this block:
    // vector<vector<int>> dp(n, vector<int>(2, -1));
    // int memoResult = sol.solveMemo(0, 1, prices, dp);
    // cout << "Maximum Profit (Memoization): " << memoResult << endl;
    */

    return 0;
}