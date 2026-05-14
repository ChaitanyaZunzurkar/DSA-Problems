#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Solution {
    int mod = 1e9 + 7;

public:
    /*
    1. MATHEMATICAL INTUITION:
    - We need to split the array into two subsets, S1 and S2.
    - Conditions: (1) S1 - S2 = diff  and  (2) S1 + S2 = totalSum
    - Adding both equations: 2 * S1 = totalSum + diff  =>  S1 = (totalSum + diff) / 2
    - Therefore, the problem reduces to: "Find the number of subsets that sum up to a Target (S1)."
    - Edge Cases: 
        a) If (totalSum + diff) is odd, we can't have a valid integer subset sum.
        b) If totalSum < diff, the difference is physically impossible.
    */

    /*
    2. MEMOIZATION INTUITION (Top-Down):
    - Concept: Think of this as a "Decision Tree." At every index, you ask: "Should I include this number?"
    - State: dp[idx][currSum] stores the answer for "How many ways can I reach 'target' starting 
      from 'idx' having already accumulated 'currSum'?"
    - Why use DP? Many branches of the decision tree lead to the same (idx, currSum). Instead of 
      re-calculating, we store the result (Memoize) to turn an exponential O(2^n) into O(n * target).
    - Base Case logic: When we reach idx 0, if the element is 0, it doubles our possibilities (Take/NotTake 
      both result in the same sum). Otherwise, we check if we need the value or if we already hit target.
    */
    int solveMemo(int idx, int currSum, int target, vector<int> &arr, vector<vector<int>> &dp) {
        if (idx == 0) {
            // If the last element is 0 and we are at target, we have 2 options:
            // 1. Pick the 0 (sum stays target) 
            // 2. Don't pick the 0 (sum stays target)
            if (currSum == target && arr[0] == 0) return 2;
            
            // If the element isn't 0, we have 1 way if:
            // 1. Current sum is already target (Don't pick arr[0])
            // 2. Current sum + arr[0] hits target (Pick arr[0])
            if (currSum == target || currSum + arr[0] == target) return 1;
            
            return 0;
        }

        if (dp[idx][currSum] != -1) return dp[idx][currSum];

        // Choice 1: Exclude the current element (Sum remains same)
        int notTake = solveMemo(idx - 1, currSum, target, arr, dp);

        // Choice 2: Include the current element (Only if it doesn't exceed target)
        int take = 0;
        if (currSum + arr[idx] <= target) {
            take = solveMemo(idx - 1, currSum + arr[idx], target, arr, dp);
        }

        return dp[idx][currSum] = (take + notTake) % mod;
    }

    /*
    3. TABULATION INTUITION (Bottom-Up):
    - Concept: "Building from the ground up." Instead of recursion, we fill a table row by row.
    - dp[i][j]: Represents "Number of ways to form sum 'j' using the first 'i' elements."
    - Transition: To get a sum 'j' using 'i' elements:
        - Either we didn't use the i-th element: dp[i-1][j]
        - Or we used the i-th element: dp[i-1][j - arr[i]]
    - Advantage: No recursion stack depth issues (prevents Stack Overflow).
    */
    int solveTab(vector<int>& arr, int target) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));

        // Base case for the first element (index 0)
        if (arr[0] == 0) dp[0][0] = 2; // Two ways: Pick 0 or Don't pick 0
        else {
            dp[0][0] = 1; // One way: Don't pick arr[0]
            if (arr[0] <= target) dp[0][arr[0]] = 1; // One way: Pick arr[0]
        }

        for (int i = 1; i < n; i++) {
            for (int sum = 0; sum <= target; sum++) {
                int notTake = dp[i - 1][sum];
                int take = 0;
                if (arr[i] <= sum) {
                    take = dp[i - 1][sum - arr[i]];
                }
                dp[i][sum] = (take + notTake) % mod;
            }
        }
        return dp[n - 1][target];
    }

    /*
    4. SPACE OPTIMIZATION INTUITION:
    - Observation: In Tabulation, to calculate row 'i', we ONLY look at row 'i-1'.
    - Conclusion: We don't need a 2D matrix. We just need a 1D array 'prev' to store the 
      results of the previous element.
    - We calculate 'curr' using 'prev', then move 'curr' to 'prev' for the next iteration.
    - Space complexity drops from O(N * Target) to O(Target).
    */
    int solveSO(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> prev(target + 1, 0);

        if (arr[0] == 0) prev[0] = 2;
        else {
            prev[0] = 1;
            if (arr[0] <= target) prev[arr[0]] = 1;
        }

        for (int i = 1; i < n; i++) {
            vector<int> curr(target + 1, 0);
            for (int sum = 0; sum <= target; sum++) {
                int notTake = prev[sum];
                int take = 0;
                if (arr[i] <= sum) {
                    take = prev[sum - arr[i]];
                }
                curr[sum] = (take + notTake) % mod;
            }
            prev = curr;
        }
        return prev[target];
    }
};

int main() {
    Solution obj;
    int n, d;

    cout << "--- Partition with Given Difference ---" << endl;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    int totalSum = 0;
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        totalSum += arr[i];
    }

    cout << "Enter required difference: ";
    cin >> d;

    // Mathematical check before starting DP
    if ((totalSum + d) % 2 != 0 || totalSum < d) {
        cout << "Result: 0 (No valid partition possible mathematically)" << endl;
    } else {
        int target = (totalSum + d) / 2;

        // Memoization Call
        vector<vector<int>> dp(n, vector<int>(target + 1, -1));
        cout << "\n[Memoization] Ways: " << obj.solveMemo(n - 1, 0, target, arr, dp);

        // Tabulation Call
        cout << "\n[Tabulation] Ways: " << obj.solveTab(arr, target);

        // Space Optimized Call
        cout << "\n[Space Optimized] Ways: " << obj.solveSO(arr, target) << endl;
    }

    return 0;
}