#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    /*
    =========================================================
                1. MEMOIZATION (TOP-DOWN DP)
    =========================================================

    Intuition:
    ---------------------------------------------------------
    We try all possible subsets.

    For every element:
    1. Take it
    2. Do not take it

    If we can make target = totalSum/2,
    then equal partition is possible.

    dp[idx][currSum]
    stores whether it is possible to form
    target starting from this state.

    Time Complexity:
    O(n * target)

    Space Complexity:
    O(n * target)
    */

    bool solveMemo(int idx,
                   int target,
                   int currSum,
                   vector<int>& nums,
                   vector<vector<int>>& dp) {

        // Target achieved
        if (currSum == target) {
            return true;
        }

        // Invalid case
        if (idx >= nums.size() || currSum > target) {
            return false;
        }

        // Already computed
        if (dp[idx][currSum] != -1) {
            return dp[idx][currSum];
        }

        // Take current element
        bool take = solveMemo(idx + 1,
                              target,
                              currSum + nums[idx],
                              nums,
                              dp);

        // Do not take current element
        bool notTake = solveMemo(idx + 1,
                                 target,
                                 currSum,
                                 nums,
                                 dp);

        return dp[idx][currSum] = take || notTake;
    }

    bool canPartitionMemo(vector<int>& nums) {

        int totalSum = 0;

        for (int num : nums) {
            totalSum += num;
        }

        // Odd sum cannot be equally divided
        if (totalSum % 2 != 0) {
            return false;
        }

        int target = totalSum / 2;

        int n = nums.size();

        vector<vector<int>> dp(
            n,
            vector<int>(target + 1, -1)
        );

        return solveMemo(0, target, 0, nums, dp);
    }

    /*
    =========================================================
                2. TABULATION (BOTTOM-UP DP)
    =========================================================

    Intuition:
    ---------------------------------------------------------
    dp[i][j] = can we make sum j using
               first i elements?

    Transition:
    ---------------------------------------------------------
    take     -> include current element
    notTake  -> exclude current element

    Time Complexity:
    O(n * target)

    Space Complexity:
    O(n * target)
    */

    bool canPartitionTabulation(vector<int>& nums) {

        int totalSum = 0;

        for (int num : nums) {
            totalSum += num;
        }

        if (totalSum % 2 != 0) {
            return false;
        }

        int target = totalSum / 2;

        int n = nums.size();

        vector<vector<bool>> dp(
            n + 1,
            vector<bool>(target + 1, false)
        );

        // Sum 0 is always possible
        for (int i = 0; i <= n; i++) {
            dp[i][0] = true;
        }

        for (int i = 1; i <= n; i++) {

            for (int j = 1; j <= target; j++) {

                bool notTake = dp[i - 1][j];

                bool take = false;

                if (nums[i - 1] <= j) {
                    take = dp[i - 1][j - nums[i - 1]];
                }

                dp[i][j] = take || notTake;
            }
        }

        return dp[n][target];
    }

    /*
    =========================================================
                3. SPACE OPTIMIZATION
    =========================================================

    Intuition:
    ---------------------------------------------------------
    In tabulation, current row only depends
    on previous row.

    So instead of storing whole matrix,
    we store only one row.

    Time Complexity:
    O(n * target)

    Space Complexity:
    O(target)
    */

    bool canPartitionSpaceOptimized(vector<int>& nums) {

        int totalSum = 0;

        for (int num : nums) {
            totalSum += num;
        }

        if (totalSum % 2 != 0) {
            return false;
        }

        int target = totalSum / 2;

        vector<bool> dp(target + 1, false);

        // Sum 0 always possible
        dp[0] = true;

        for (int num : nums) {

            // Traverse backwards
            for (int j = target; j >= num; j--) {

                dp[j] = dp[j] || dp[j - num];
            }
        }

        return dp[target];
    }
};

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements: ";

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution sol;

    cout << "\nUsing Memoization: ";

    if (sol.canPartitionMemo(nums)) {
        cout << "Possible" << endl;
    } else {
        cout << "Not Possible" << endl;
    }

    cout << "Using Tabulation: ";

    if (sol.canPartitionTabulation(nums)) {
        cout << "Possible" << endl;
    } else {
        cout << "Not Possible" << endl;
    }

    cout << "Using Space Optimization: ";

    if (sol.canPartitionSpaceOptimized(nums)) {
        cout << "Possible" << endl;
    } else {
        cout << "Not Possible" << endl;
    }

    return 0;
}