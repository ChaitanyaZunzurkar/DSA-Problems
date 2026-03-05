#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HouseRobber {
public:
    /* INTUITION:
       In a circular street, House[0] and House[n-1] are neighbors.
       To avoid alerting police, we can't rob both.
       
       This breaks the problem into two linear sub-problems:
       1. Rob from index 0 to n-2 (Excluding the last house)
       2. Rob from index 1 to n-1 (Excluding the first house)
       
       The final answer is max(Result1, Result2).
    */

    // --- 1. MEMOIZATION APPROACH (Top-Down) ---
    // Uses recursion + a table to store results of subproblems.
    int memoSolve(int i, vector<int>& nums, vector<int>& memo) {
        if (i < 0) return 0;
        if (i == 0) return nums[0];
        if (memo[i] != -1) return memo[i];

        int pick = nums[i] + memoSolve(i - 2, nums, memo);
        int skip = memoSolve(i - 1, nums, memo);
        
        return memo[i] = max(pick, skip);
    }

    // --- 2. TABULATION APPROACH (Bottom-Up) ---
    // Uses an array to build the solution iteratively from the base case.
    int tabulationSolve(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i - 1], nums[i] + dp[i - 2]);
        }
        return dp[n - 1];
    }

    // --- 3. SPACE OPTIMIZED APPROACH ($O(1)$ Space) ---
    // Since we only need the last two results, we replace the DP array with two variables.
    int spaceOptimizedSolve(vector<int>& nums, int start, int end) {
        int prev2 = 0; // dp[i-2]
        int prev1 = 0; // dp[i-1]

        for (int i = start; i <= end; i++) {
            int current = max(prev1, nums[i] + prev2);
            prev2 = prev1;
            prev1 = current;
        }
        return prev1;
    }

    int rob(vector<int>& nums, int choice) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        if (choice == 1) { // Memoization
            vector<int> v1(nums.begin(), nums.end() - 1);
            vector<int> v2(nums.begin() + 1, nums.end());
            vector<int> m1(n, -1), m2(n, -1);
            return max(memoSolve(v1.size() - 1, v1, m1), memoSolve(v2.size() - 1, v2, m2));
        } 
        else if (choice == 2) { // Tabulation
            vector<int> v1(nums.begin(), nums.end() - 1);
            vector<int> v2(nums.begin() + 1, nums.end());
            return max(tabulationSolve(v1), tabulationSolve(v2));
        } 
        else { // Space Optimized
            return max(spaceOptimizedSolve(nums, 0, n - 2), spaceOptimizedSolve(nums, 1, n - 1));
        }
    }
};

int main() {
    int n, choice;
    cout << "Enter number of houses: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter money in each house: ";
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "\nChoose Approach:\n1. Memoization\n2. Tabulation\n3. Space Optimized\nChoice: ";
    cin >> choice;

    HouseRobber sol;
    int result = sol.rob(nums, choice);

    cout << "\nMaximum money that can be robbed: " << result << endl;

    return 0;
}