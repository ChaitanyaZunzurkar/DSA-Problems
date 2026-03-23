#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int MOD = 1e9 + 7;
    typedef long long ll;

    // dp[i][j] = {maxProduct from (i,j) → end, minProduct from (i,j) → end}
    vector<vector<pair<ll, ll>>> dp;

    /*
    ------------------------------------------------------------
    🔥 INTUITION:
    ------------------------------------------------------------
    - We need maximum product path from (0,0) to (n-1,m-1)
    - Grid may contain NEGATIVE numbers → important twist

    WHY TRACK BOTH max AND min?
    - (-ve) * (-ve) = +ve → minimum can become maximum
    - So we store:
        dp[i][j] = {maxProduct, minProduct}

    From each cell:
        we can go:
            → down (i+1, j)
            → right (i, j+1)

    Transition:
        current_val * (child max OR child min)

    ------------------------------------------------------------
    */

    pair<ll, ll> solve(int i, int j, vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // Base case
        if(i == n-1 && j == m-1)
            return {grid[i][j], grid[i][j]};

        // Memoization check
        if(dp[i][j] != make_pair(LLONG_MIN, LLONG_MAX)) {
            return dp[i][j];
        }

        ll maxVal = LLONG_MIN;
        ll minVal = LLONG_MAX;

        // Move DOWN
        if(i + 1 < n) {
            auto [downMax, downMin] = solve(i+1, j, grid);

            ll a = grid[i][j] * downMax;
            ll b = grid[i][j] * downMin;

            maxVal = max({maxVal, a, b});
            minVal = min({minVal, a, b});
        }

        // Move RIGHT
        if(j + 1 < m) {
            auto [rightMax, rightMin] = solve(i, j+1, grid);

            ll a = grid[i][j] * rightMax;
            ll b = grid[i][j] * rightMin;

            maxVal = max({maxVal, a, b});
            minVal = min({minVal, a, b});
        }

        return dp[i][j] = {maxVal, minVal};
    }

    int maxProductPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        dp = vector<vector<pair<ll, ll>>>(n,
              vector<pair<ll, ll>>(m, {LLONG_MIN, LLONG_MAX}));

        auto [maxProd, minProd] = solve(0, 0, grid);

        return maxProd < 0 ? -1 : maxProd % MOD;
    }

    /*
    ------------------------------------------------------------
    🔥 TABULATION (BOTTOM-UP DP)
    ------------------------------------------------------------
    Time: O(n*m)
    Space: O(n*m)

    dpMax[i][j] = max product till (i,j)
    dpMin[i][j] = min product till (i,j)
    ------------------------------------------------------------
    */
    int maxProductPathTab(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector<vector<ll>> dpMax(n, vector<ll>(m));
        vector<vector<ll>> dpMin(n, vector<ll>(m));

        dpMax[0][0] = dpMin[0][0] = grid[0][0];

        // First row
        for(int j = 1; j < m; j++) {
            dpMax[0][j] = dpMin[0][j] = dpMax[0][j-1] * grid[0][j];
        }

        // First column
        for(int i = 1; i < n; i++) {
            dpMax[i][0] = dpMin[i][0] = dpMax[i-1][0] * grid[i][0];
        }

        for(int i = 1; i < n; i++) {
            for(int j = 1; j < m; j++) {

                ll a = dpMax[i-1][j] * grid[i][j];
                ll b = dpMin[i-1][j] * grid[i][j];
                ll c = dpMax[i][j-1] * grid[i][j];
                ll d = dpMin[i][j-1] * grid[i][j];

                dpMax[i][j] = max({a, b, c, d});
                dpMin[i][j] = min({a, b, c, d});
            }
        }

        return dpMax[n-1][m-1] < 0 ? -1 : dpMax[n-1][m-1] % MOD;
    }

    /*
    ------------------------------------------------------------
    🔥 SPACE OPTIMIZATION
    ------------------------------------------------------------
    Instead of full dp[][], we only keep previous row
    Space: O(m)
    ------------------------------------------------------------
    */
    int maxProductPathSpace(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector<ll> prevMax(m), prevMin(m);

        prevMax[0] = prevMin[0] = grid[0][0];

        for(int j = 1; j < m; j++) {
            prevMax[j] = prevMin[j] = prevMax[j-1] * grid[0][j];
        }

        for(int i = 1; i < n; i++) {
            vector<ll> currMax(m), currMin(m);

            currMax[0] = currMin[0] = prevMax[0] * grid[i][0];

            for(int j = 1; j < m; j++) {

                ll a = prevMax[j] * grid[i][j];
                ll b = prevMin[j] * grid[i][j];
                ll c = currMax[j-1] * grid[i][j];
                ll d = currMin[j-1] * grid[i][j];

                currMax[j] = max({a, b, c, d});
                currMin[j] = min({a, b, c, d});
            }

            prevMax = currMax;
            prevMin = currMin;
        }

        return prevMax[m-1] < 0 ? -1 : prevMax[m-1] % MOD;
    }
};

/*
------------------------------------------------------------
🔹 DRIVER CODE (USER INPUT)
------------------------------------------------------------
Input format:
n m
grid elements

Example:
3 3
1 -2 1
1 -2 1
3 -4 1
------------------------------------------------------------
*/

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    Solution obj;

    cout << "Recursion + Memoization: "
         << obj.maxProductPath(grid) << endl;

    cout << "Tabulation: "
         << obj.maxProductPathTab(grid) << endl;

    cout << "Space Optimized: "
         << obj.maxProductPathSpace(grid) << endl;

    return 0;
}