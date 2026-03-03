#include <bits/stdc++.h>
using namespace std;

/*
============================================================
PROBLEM:
A frog is at index 0 and wants to reach index n-1.
From index i, it can jump:
    - to i+1
    - to i+2

Cost of jump = abs(height[i] - height[j])

Goal: Minimize total cost to reach last index.
============================================================
*/


// ============================================================
// 1️⃣ PURE RECURSION (TLE)
// Time Complexity: O(2^n)
// Reason: We recompute same subproblems again and again.
// ============================================================

int solveRecursive(vector<int> &height, int idx) {
    // Base case: starting point
    if (idx == 0) return 0;

    // Jump from idx-1
    int first = solveRecursive(height, idx - 1)
                + abs(height[idx] - height[idx - 1]);

    // Jump from idx-2
    int second = INT_MAX;
    if (idx > 1) {
        second = solveRecursive(height, idx - 2)
                 + abs(height[idx] - height[idx - 2]);
    }

    return min(first, second);
}



// ============================================================
// 2️⃣ MEMOIZATION (Top Down DP)
// Time Complexity: O(n)
// Space Complexity: O(n) + recursion stack
//
// Intuition:
// Store already computed results in dp[] to avoid recomputation.
// ============================================================

int solveMemo(vector<int> &height, int idx, vector<int> &dp) {
    if (idx == 0) return 0;

    // If already computed, return stored result
    if (dp[idx] != -1) return dp[idx];

    int first = solveMemo(height, idx - 1, dp)
                + abs(height[idx] - height[idx - 1]);

    int second = INT_MAX;
    if (idx > 1) {
        second = solveMemo(height, idx - 2, dp)
                 + abs(height[idx] - height[idx - 2]);
    }

    // Store result before returning
    return dp[idx] = min(first, second);
}



// ============================================================
// 3️⃣ TABULATION (Bottom Up DP)
// Time Complexity: O(n)
// Space Complexity: O(n)
//
// Intuition:
// Instead of recursion, build answer from 0 → n-1.
// dp[i] = minimum cost to reach index i.
// ============================================================

int solveTabulation(vector<int> &height) {
    int n = height.size();
    vector<int> dp(n);

    dp[0] = 0;  // base case

    for (int i = 1; i < n; i++) {

        int first = dp[i - 1] + abs(height[i] - height[i - 1]);

        int second = INT_MAX;
        if (i > 1) {
            second = dp[i - 2] + abs(height[i] - height[i - 2]);
        }

        dp[i] = min(first, second);
    }

    return dp[n - 1];
}



// ============================================================
// 4️⃣ SPACE OPTIMIZED (Most Efficient)
// Time Complexity: O(n)
// Space Complexity: O(1)
//
// Intuition:
// We only need last two states:
// prev  = dp[i-1]
// prev2 = dp[i-2]
// ============================================================

int solveSpaceOptimized(vector<int> &height) {
    int n = height.size();

    int prev = 0;   // dp[0]
    int prev2 = 0;  // dp[-1] logically unused

    for (int i = 1; i < n; i++) {

        int first = prev + abs(height[i] - height[i - 1]);

        int second = INT_MAX;
        if (i > 1) {
            second = prev2 + abs(height[i] - height[i - 2]);
        }

        int curr = min(first, second);

        prev2 = prev;
        prev = curr;
    }

    return prev;
}



// ============================================================
// MAIN FUNCTION (Taking Input from User)
// ============================================================

int main() {

    int n;
    cout << "Enter number of stones: ";
    cin >> n;

    vector<int> height(n);

    cout << "Enter heights: ";
    for (int i = 0; i < n; i++) {
        cin >> height[i];
    }

    cout << "\nMinimum Cost (Recursive - TLE): "
         << solveRecursive(height, n - 1) << endl;

    vector<int> dp(n, -1);
    cout << "Minimum Cost (Memoization): "
         << solveMemo(height, n - 1, dp) << endl;

    cout << "Minimum Cost (Tabulation): "
         << solveTabulation(height) << endl;

    cout << "Minimum Cost (Space Optimized): "
         << solveSpaceOptimized(height) << endl;

    return 0;
}