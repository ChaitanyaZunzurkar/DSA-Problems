#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    =========================================================
                    1. MEMOIZATION (Top Down)
    =========================================================

    Intuition:
    ----------
    For every coin index, we have 2 choices:

    1. Take the coin
       -> stay on same index because coin can be reused
       -> amount decreases

    2. Not take the coin
       -> move to previous index

    We store already computed states in dp[][] to avoid
    repeated recursion calls.

    State:
    ------
    dp[idx][amount]
    = minimum coins required using coins[0...idx]
    */

    int solveMemo(int idx,
                  int amount,
                  vector<int>& coins,
                  vector<vector<int>>& dp) {

        // Base Case
        // Only first coin available
        if(idx == 0) {

            // If amount divisible by first coin
            if(amount % coins[0] == 0) {
                return amount / coins[0];
            }

            // Impossible case
            return 1e9;
        }

        // Already computed
        if(dp[idx][amount] != -1) {
            return dp[idx][amount];
        }

        // Option 1: Do not take current coin
        int notTake = solveMemo(idx - 1,
                                amount,
                                coins,
                                dp);

        // Option 2: Take current coin
        int take = 1e9;

        if(coins[idx] <= amount) {

            // Stay on same index
            // because we can reuse coin
            take = 1 + solveMemo(idx,
                                 amount - coins[idx],
                                 coins,
                                 dp);
        }

        return dp[idx][amount] = min(take, notTake);
    }


    /*
    =========================================================
                    2. TABULATION (Bottom Up)
    =========================================================

    Intuition:
    ----------
    Convert recursion into iterative table.

    Recursive Relation:

    dp[idx][amt] =
        min(
            dp[idx-1][amt],                 // not take
            1 + dp[idx][amt-coins[idx]]    // take
        )

    Same row used in TAKE because
    this is UNBOUNDED KNAPSACK.
    */

    int coinChangeTabulation(vector<int>& coins, int amount) {

        int n = coins.size();

        vector<vector<int>> dp(n,
                               vector<int>(amount + 1, 0));

        // Base Case Initialization
        for(int amt = 0; amt <= amount; amt++) {

            if(amt % coins[0] == 0) {
                dp[0][amt] = amt / coins[0];
            }
            else {
                dp[0][amt] = 1e9;
            }
        }

        // Build DP Table
        for(int idx = 1; idx < n; idx++) {

            for(int amt = 0; amt <= amount; amt++) {

                // Not Take
                int notTake = dp[idx - 1][amt];

                // Take
                int take = 1e9;

                if(coins[idx] <= amt) {

                    // SAME ROW
                    take = 1 + dp[idx][amt - coins[idx]];
                }

                dp[idx][amt] = min(take, notTake);
            }
        }

        int ans = dp[n - 1][amount];

        return (ans >= 1e9) ? -1 : ans;
    }


    /*
    =========================================================
                3. SPACE OPTIMIZATION
    =========================================================

    Intuition:
    ----------
    Current row only depends on:
    1. Previous row
    2. Current row left side

    So instead of storing entire table,
    store only:
    - prev row
    - curr row

    Space Complexity:
    -----------------
    O(amount)
    */

    int coinChangeSpaceOptimized(vector<int>& coins,
                                 int amount) {

        int n = coins.size();

        vector<int> prev(amount + 1, 0);

        // Base Case Initialization
        for(int amt = 0; amt <= amount; amt++) {

            if(amt % coins[0] == 0) {
                prev[amt] = amt / coins[0];
            }
            else {
                prev[amt] = 1e9;
            }
        }

        // Build DP
        for(int idx = 1; idx < n; idx++) {

            vector<int> curr(amount + 1, 0);

            for(int amt = 0; amt <= amount; amt++) {

                int notTake = prev[amt];

                int take = 1e9;

                if(coins[idx] <= amt) {

                    // SAME ROW because coin reusable
                    take = 1 + curr[amt - coins[idx]];
                }

                curr[amt] = min(take, notTake);
            }

            prev = curr;
        }

        int ans = prev[amount];

        return (ans >= 1e9) ? -1 : ans;
    }
};


int main() {

    int n;

    cout << "Enter number of coins: ";
    cin >> n;

    vector<int> coins(n);

    cout << "Enter coin values:\n";

    for(int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    int amount;

    cout << "Enter target amount: ";
    cin >> amount;

    Solution obj;

    /*
    =========================================================
                        MEMOIZATION
    =========================================================
    */

    vector<vector<int>> dp(n,
                           vector<int>(amount + 1, -1));

    int memoAns =
        obj.solveMemo(n - 1,
                      amount,
                      coins,
                      dp);

    if(memoAns >= 1e9) {
        memoAns = -1;
    }

    cout << "\nMemoization Answer: "
         << memoAns << endl;


    /*
    =========================================================
                        TABULATION
    =========================================================
    */

    int tabAns =
        obj.coinChangeTabulation(coins,
                                 amount);

    cout << "Tabulation Answer: "
         << tabAns << endl;


    /*
    =========================================================
                    SPACE OPTIMIZATION
    =========================================================
    */

    int spaceAns =
        obj.coinChangeSpaceOptimized(coins,
                                     amount);

    cout << "Space Optimized Answer: "
         << spaceAns << endl;

    return 0;
}