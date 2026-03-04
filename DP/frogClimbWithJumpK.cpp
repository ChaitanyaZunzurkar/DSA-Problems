#include <bits/stdc++.h>
using namespace std;

// Intuition:
// To reach stone `idx`, the frog could have jumped from any of the previous
// `k` stones: idx-1, idx-2, ..., idx-k.
// We recursively compute the minimum cost required to reach those stones
// and add the cost of the jump: |height[idx] - height[idx-i]|.
// We take the minimum of all possible jumps.

int solveRecursive(vector<int> &height, int idx, int k) {
    if(idx == 0) return 0;

    int mini = INT_MAX;

    for(int i = 1; i <= k; i++) {
        if(idx - i >= 0) {
            int jumpCost = solveRecursive(height, idx - i, k)
                         + abs(height[idx] - height[idx - i]);

            mini = min(mini, jumpCost);
        }
    }

    return mini;
}


// Intuition:
// This is the optimized version of recursion using memoization.
// We store the minimum cost to reach each index in dp[] so that
// we do not recompute the same states again.

int solveMemo(vector<int> &height, int idx, int k, vector<int> &dp) {
    if(idx == 0) return 0;

    if(dp[idx] != -1) return dp[idx];

    int mini = INT_MAX;

    for(int i = 1; i <= k; i++) {
        if(idx - i >= 0) {
            int jumpCost = solveMemo(height, idx - i, k, dp)
                         + abs(height[idx] - height[idx - i]);

            mini = min(mini, jumpCost);
        }
    }

    return dp[idx] = mini;
}


// Intuition:
// Instead of solving recursively, we build the solution from bottom to top.
// dp[i] stores the minimum cost to reach stone i.
// For each stone we check the previous k stones and take the minimum cost.

int solveTabulation(vector<int> &height, int k) {
    int n = height.size();

    vector<int> dp(n, INT_MAX);
    dp[0] = 0;

    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= k; j++) {
            if(i - j >= 0) {
                int jumpCost = dp[i - j] + abs(height[i] - height[i - j]);
                dp[i] = min(dp[i], jumpCost);
            }
        }
    }

    return dp[n - 1];
}


int main() {
    int n, k;

    cout << "Enter number of stones: ";
    cin >> n;

    vector<int> height(n);

    cout << "Enter heights of stones: ";
    for(int i = 0; i < n; i++) {
        cin >> height[i];
    }

    cout << "Enter maximum jump k: ";
    cin >> k;

    cout << "Minimum cost using Recursion: "
         << solveRecursive(height, n - 1, k) << endl;

    vector<int> dp(n, -1);
    cout << "Minimum cost using Memoization: "
         << solveMemo(height, n - 1, k, dp) << endl;

    cout << "Minimum cost using Tabulation: "
         << solveTabulation(height, k) << endl;

    return 0;
}