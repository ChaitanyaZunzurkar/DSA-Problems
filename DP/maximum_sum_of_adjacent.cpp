#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
                HOUSE ROBBER PROBLEM
===========================================================

PROBLEM:
You are given an array where each element represents money
in a house. You cannot rob two adjacent houses.

Return the maximum money you can rob.

Example:
nums = [2,7,9,3,1]

Rob house 1 (2)
Skip house 2
Rob house 3 (9)
Skip house 4
Rob house 5 (1)

Total = 12


===========================================================
                    INTUITION
===========================================================

At every house we have two choices:

1) Rob the current house
   If we rob it, we cannot rob the previous house.

2) Skip the current house
   Then we consider previous houses.


Your implementation thinks slightly differently:

To rob house 'idx', the previous robbed house can be:

1) idx - 2
2) idx - 3

Why?

Because if we rob idx, we skip idx-1.
The previous valid house could be idx-2 or idx-3.

So the recurrence becomes:

dp[idx] = max(
              nums[idx] + solve(idx-2),
              nums[idx] + solve(idx-3)
             )

This means:
Take the best robbery ending before idx.

===========================================================
                BASE CASES
===========================================================

idx == 0
Only one house exists.
Answer = nums[0]

idx == 1
Two houses exist but they are adjacent.
If we rob house 1, we cannot rob house 0.

So value = nums[1]


===========================================================
                MEMOIZATION
===========================================================

We store answers in dp array so recursion
does not recompute states.

dp[idx] = maximum money if last robbed house is idx


===========================================================
                FINAL ANSWER
===========================================================

The final robbed house could be

n-1 OR n-2

Because if we rob n-1 we cannot rob n-2.

So we compute both.

max( solve(n-1), solve(n-2) )

===========================================================
*/

class Solution {
public:

    int solve(vector<int>& nums, int idx, vector<int> &dp) {

        // Base case
        if(idx == 0)
            return nums[0];

        // If we rob house 1 we cannot rob house 0
        if(idx == 1)
            return nums[1];

        // If already computed return stored value
        if(dp[idx] != -1)
            return dp[idx];

        // Option 1: rob current house and previous robbed is idx-2
        int firstHouse = solve(nums, idx-2, dp) + nums[idx];

        // Option 2: rob current house and previous robbed is idx-3
        int secondHouse = 0;

        if(idx > 2)
            secondHouse = solve(nums, idx-3, dp) + nums[idx];

        // Store maximum result
        dp[idx] = max(firstHouse, secondHouse);

        return dp[idx];
    }


    int rob(vector<int>& nums) {

        int n = nums.size();

        // Edge case
        if(n == 1)
            return nums[0];

        if(n == 2)
            return max(nums[0], nums[1]);

        vector<int> dp(n, -1);

        // Case 1: last robbed house is n-1
        int last = solve(nums, n-1, dp);

        // Case 2: last robbed house is n-2
        int secondLast = solve(nums, n-2, dp);

        return max(last, secondLast);
    }
};

int main() {

    /*
    =========================================
            USER INPUT SECTION
    =========================================
    */

    int n;

    cout << "Enter number of houses: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter money in each house:\n";

    for(int i = 0; i < n; i++)
        cin >> nums[i];


    Solution obj;

    int ans = obj.rob(nums);

    cout << "\nMaximum money that can be robbed = " << ans << endl;

    return 0;
}