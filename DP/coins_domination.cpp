#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    ============================================================
    🧠 INTUITION (READ THIS CAREFULLY)

    Problem: Minimum coins to make a target amount.

    This is a classic "UNBOUNDED KNAPSACK" problem:
    → You can take the same coin multiple times.

    At every index (coin), we have 2 choices:

    1. NOT TAKE the coin:
       → move to previous coin
       → solve(i-1, T)

    2. TAKE the coin:
       → stay at same index (because unlimited supply)
       → 1 + solve(i, T - coins[i])

    WHY SAME INDEX?
    Because we can reuse the same coin again.

    ------------------------------------------------------------
    Base Case:
    If we are at index 0 (only one coin left):
        If T is divisible → answer = T / coin
        Else → impossible (return large value)

    ------------------------------------------------------------
    Goal:
    Minimize number of coins
    ============================================================
    */


    // ================= MEMOIZATION =================
    int solve(int ind, int T, vector<int>& coins, vector<vector<int>> &dp) {
        // Base case
        if(ind == 0) {
            if(T % coins[0] == 0) return T / coins[0];
            return 1e9; // impossible
        }

        if(dp[ind][T] != -1) return dp[ind][T];

        // Not take current coin
        int notTake = solve(ind - 1, T, coins, dp);

        // Take current coin (stay at same index → unbounded)
        int take = 1e9;
        if(coins[ind] <= T)
            take = 1 + solve(ind, T - coins[ind], coins, dp);

        return dp[ind][T] = min(take, notTake);
    }

    int coinChangeMemo(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, -1));

        int ans = solve(n - 1, amount, coins, dp);
        return (ans >= 1e9) ? -1 : ans;
    }


    // ================= TABULATION =================
    int coinChangeTab(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, 0));

        /*
        Base case initialization:
        Using only coins[0], can we form T?

        If divisible → T / coins[0]
        Else → impossible
        */
        for(int T = 0; T <= amount; T++) {
            if(T % coins[0] == 0) dp[0][T] = T / coins[0];
            else dp[0][T] = 1e9;
        }

        /*
        Fill DP table:

        notTake → dp[i-1][T]
        take → 1 + dp[i][T - coins[i]]  (IMPORTANT: same row)
        */
        for(int i = 1; i < n; i++) {
            for(int T = 0; T <= amount; T++) {

                int notTake = dp[i - 1][T];

                int take = 1e9;
                if(coins[i] <= T)
                    take = 1 + dp[i][T - coins[i]];

                dp[i][T] = min(take, notTake);
            }
        }

        int ans = dp[n - 1][amount];
        return (ans >= 1e9) ? -1 : ans;
    }


    // ================= SPACE OPTIMIZATION =================
    int coinChangeSpace(vector<int>& coins, int amount) {
        int n = coins.size();

        /*
        Instead of 2D dp[i][T], we use 1D array.

        WHY IT WORKS?

        - notTake depends on previous row → prev[T]
        - take depends on same row → cur[T - coins[i]]

        So we maintain:
            prev → dp[i-1]
            cur  → dp[i]
        */

        vector<int> prev(amount + 1, 0), cur(amount + 1, 0);

        // Base case
        for(int T = 0; T <= amount; T++) {
            if(T % coins[0] == 0) prev[T] = T / coins[0];
            else prev[T] = 1e9;
        }

        for(int i = 1; i < n; i++) {
            for(int T = 0; T <= amount; T++) {

                int notTake = prev[T];

                int take = 1e9;
                if(coins[i] <= T)
                    take = 1 + cur[T - coins[i]]; // same row

                cur[T] = min(take, notTake);
            }

            prev = cur;
        }

        int ans = prev[amount];
        return (ans >= 1e9) ? -1 : ans;
    }
};


// ================= MAIN FUNCTION =================
int main() {
    int n;
    cout << "Enter number of coins: ";
    cin >> n;

    vector<int> coins(n);
    cout << "Enter coin values: ";
    for(int i = 0; i < n; i++) cin >> coins[i];

    int amount;
    cout << "Enter amount: ";
    cin >> amount;

    Solution obj;

    int memoAns = obj.coinChangeMemo(coins, amount);
    int tabAns = obj.coinChangeTab(coins, amount);
    int spaceAns = obj.coinChangeSpace(coins, amount);

    cout << "\n===== RESULTS =====\n";
    cout << "Memoization: " << memoAns << endl;
    cout << "Tabulation: " << tabAns << endl;
    cout << "Space Optimized: " << spaceAns << endl;

    return 0;
}