#include <iostream>
#include <vector>
using namespace std;

/*
    ============================================================
                    COIN CHANGE II
    ============================================================

    Problem:
    --------
    Given an array of coin denominations and a target amount,
    find the number of combinations that can form the amount.

    Example:
    coins = {1,2,5}
    amount = 5

    Output = 4

    Combinations:
    1+1+1+1+1
    1+1+1+2
    1+2+2
    5

    ------------------------------------------------------------
    IMPORTANT OBSERVATION
    ------------------------------------------------------------

    We are counting COMBINATIONS, not PERMUTATIONS.

    Meaning:

    1 + 2 + 2
    2 + 1 + 2
    2 + 2 + 1

    are considered SAME.

    ------------------------------------------------------------
    DP STATE
    ------------------------------------------------------------

    dp[i][target]

    = Number of ways to create "target"
      using coins from index 0 to i.

    ------------------------------------------------------------
    CHOICE DIAGRAM
    ------------------------------------------------------------

    For every coin we have two choices:

    1) Take it
       Stay at same index because coin can be reused.

    2) Don't take it
       Move to previous index.

                        solve(i,target)
                          /      \
                         /        \
                     Take        Not Take
                      |              |
             solve(i,target-coin) solve(i-1,target)

    ------------------------------------------------------------
    BASE CASE
    ------------------------------------------------------------

    If only first coin remains:

    Example:
        coin = 2
        target = 8

    We can form 8 only if:
        8 % 2 == 0

    because:
        2+2+2+2

    Hence:

        target % coins[0] == 0

    return 1
    else return 0
*/


/*
    ============================================================
                    MEMOIZATION
    ============================================================

    Time Complexity:
        O(N * Amount)

    Space Complexity:
        O(N * Amount) + Recursion Stack

    Idea:
    -----
    Store answer of every state.

    State:
        (idx, target)

    Once calculated, reuse it.
*/

int memoHelper(int idx,
               int target,
               vector<int>& coins,
               vector<vector<int>>& dp)
{
    if(idx == 0)
    {
        return (target % coins[0] == 0);
    }

    if(dp[idx][target] != -1)
    {
        return dp[idx][target];
    }

    int notTake = memoHelper(
                    idx - 1,
                    target,
                    coins,
                    dp
                  );

    int take = 0;

    if(coins[idx] <= target)
    {
        take = memoHelper(
                    idx,
                    target - coins[idx],
                    coins,
                    dp
               );
    }

    return dp[idx][target] = take + notTake;
}

int memoization(int amount, vector<int>& coins)
{
    int n = coins.size();

    vector<vector<int>> dp(
        n,
        vector<int>(amount + 1, -1)
    );

    return memoHelper(
            n - 1,
            amount,
            coins,
            dp
           );
}


/*
    ============================================================
                    TABULATION
    ============================================================

    Time Complexity:
        O(N * Amount)

    Space Complexity:
        O(N * Amount)

    Idea:
    -----
    Convert recursion into table.

    dp[i][target]

    Take:
        dp[i][target - coin]

    Not Take:
        dp[i-1][target]

    Answer:
        take + notTake
*/

int tabulation(int amount, vector<int>& coins)
{
    int n = coins.size();

    vector<vector<int>> dp(
        n,
        vector<int>(amount + 1, 0)
    );

    /*
        Base Row

        Only coin[0] available.

        We can form target only when
        target is multiple of coin[0].
    */

    for(int target = 0; target <= amount; target++)
    {
        dp[0][target] =
            (target % coins[0] == 0);
    }

    for(int i = 1; i < n; i++)
    {
        for(int target = 0;
            target <= amount;
            target++)
        {
            int notTake =
                dp[i - 1][target];

            int take = 0;

            if(coins[i] <= target)
            {
                take =
                    dp[i][target - coins[i]];
            }

            dp[i][target] =
                take + notTake;
        }
    }

    return dp[n - 1][amount];
}


/*
    ============================================================
                SPACE OPTIMIZATION
    ============================================================

    Time Complexity:
        O(N * Amount)

    Space Complexity:
        O(Amount)

    Observation:
    ------------

    For dp[i][target]

    We only need:

        Previous Row
        Current Row

    Hence we can remove entire matrix.

    ------------------------------------------------------------

    IMPORTANT:

    For TAKE:

        dp[i][target - coin]

    Notice same row (i).

    Therefore use CURRENT row.

    Wrong:
        prev[target - coin]

    Correct:
        curr[target - coin]
*/

int spaceOptimized(int amount,
                   vector<int>& coins)
{
    int n = coins.size();

    vector<int> prev(amount + 1, 0);

    for(int target = 0;
        target <= amount;
        target++)
    {
        prev[target] =
            (target % coins[0] == 0);
    }

    for(int i = 1; i < n; i++)
    {
        vector<int> curr(amount + 1, 0);

        for(int target = 0;
            target <= amount;
            target++)
        {
            int notTake =
                prev[target];

            int take = 0;

            if(coins[i] <= target)
            {
                take =
                    curr[target - coins[i]];
            }

            curr[target] =
                take + notTake;
        }

        prev = curr;
    }

    return prev[amount];
}


/*
    ============================================================
                            MAIN
    ============================================================

    Input Format:

    Enter number of coins:
    3

    Enter coins:
    1 2 5

    Enter amount:
    5

    Output:
    Memoization     : 4
    Tabulation      : 4
    Space Optimized : 4
*/

int main()
{
    int n;

    cout << "Enter number of coins: ";
    cin >> n;

    vector<int> coins(n);

    cout << "Enter coin values: ";

    for(int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    int amount;

    cout << "Enter target amount: ";
    cin >> amount;

    cout << "\n";

    cout << "Memoization     : "
         << memoization(amount, coins)
         << "\n";

    cout << "Tabulation      : "
         << tabulation(amount, coins)
         << "\n";

    cout << "Space Optimized : "
         << spaceOptimized(amount, coins)
         << "\n";

    return 0;
}
