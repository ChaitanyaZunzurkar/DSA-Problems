#include <bits/stdc++.h>
using namespace std;

/*
========================================================
PROBLEM: Climbing Stairs
--------------------------------------------------------
You are at step 0. To reach step n, you can:
- Take 1 step
- Take 2 steps

Question:
In how many distinct ways can you reach step n?

This is a classic Dynamic Programming problem.
========================================================
*/


/*
========================================================
1) MEMOIZATION (TOP-DOWN DP)
--------------------------------------------------------
INTUITION:
- Start from the final answer: ways(n)
- Break it into smaller subproblems:
      ways(n) = ways(n-1) + ways(n-2)
- Many subproblems repeat, so we store results in dp[]
- Each state is computed only once

THINKING:
"If I already know the number of ways to reach step k,
why calculate it again?"

STATE:
dp[n] = number of ways to reach step n

TIME  : O(n)
SPACE : O(n) (dp array + recursion stack)
========================================================
*/

int helper(int n, vector<int> &dp) {
    // Base cases
    // If there are 1 or 2 steps, ways = n itself
    if (n <= 2) return n;

    // If already computed, return stored result
    if (dp[n] != -1) return dp[n];

    // Recursive relation
    dp[n] = helper(n - 1, dp) + helper(n - 2, dp);
    return dp[n];
}

int climbStairs_memo(int n) {
    vector<int> dp(n + 1, -1); // -1 means "not computed"
    return helper(n, dp);
}


/*
========================================================
2) TABULATION (BOTTOM-UP DP)
--------------------------------------------------------
INTUITION:
- Solve the problem from the smallest subproblems first
- No recursion, build the answer iteratively
- Store all results in dp[] array

THINKING:
"I already know the ways to reach step 1 and 2.
From that, I can build answers up to step n."

STATE:
dp[i] = number of ways to reach step i

TIME  : O(n)
SPACE : O(n)
========================================================
*/

int climbStairs_tab(int n) {
    if (n <= 2) return n;

    vector<int> dp(n + 1);
    dp[1] = 1;  // One way to reach step 1
    dp[2] = 2;  // Two ways to reach step 2

    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}


/*
========================================================
3) SPACE OPTIMIZED DP
--------------------------------------------------------
INTUITION:
- dp[i] depends only on dp[i-1] and dp[i-2]
- So we do NOT need the full dp[] array
- Keep only the last two values

THINKING:
"Why waste memory storing everything
when I only need the previous two?"

TIME  : O(n)
SPACE : O(1)
========================================================
*/

int climbStairs_optimized(int n) {
    if (n <= 2) return n;

    int prev1 = 1; // ways to reach step 1
    int prev2 = 2; // ways to reach step 2

    for (int i = 3; i <= n; i++) {
        int curr = prev1 + prev2;
        prev1 = prev2;
        prev2 = curr;
    }

    return prev2;
}


/*
========================================================
MAIN FUNCTION
--------------------------------------------------------
- Takes input from user
- Calls all three approaches
- Prints results
========================================================
*/

int main() {
    int n;
    cin >> n;

    cout << "Memoization Answer     : " << climbStairs_memo(n) << endl;
    cout << "Tabulation Answer      : " << climbStairs_tab(n) << endl;
    cout << "Space Optimized Answer : " << climbStairs_optimized(n) << endl;

    return 0;
}