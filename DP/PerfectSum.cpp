#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
PROBLEM:
Count the number of subsets whose sum is equal to target
===========================================================

We will solve this problem using:

1. Memoization (Top Down DP)
2. Tabulation (Bottom Up DP)
3. Space Optimization

-----------------------------------------------------------
INPUT:
n = size of array
array elements
target sum

OUTPUT:
Number of subsets having sum = target
-----------------------------------------------------------
*/


class Solution {
public:

    /*
    ===========================================================
    1. MEMOIZATION (TOP DOWN DP)
    ===========================================================

    INTUITION:

    State:
    dp[idx][currSum]

    Meaning:
    Number of ways to reach target starting from index idx
    when current formed sum is currSum.

    Choices:
    1. Take current element
    2. Do not take current element

    Recurrence:
    solve(idx, currSum)
        =
    solve(idx+1, currSum + arr[idx])
        +
    solve(idx+1, currSum)

    Base Case:
    If all elements are processed:
        return 1 if currSum == target
        else return 0
    ===========================================================
    */

    int solveMemo(int idx,
                  int target,
                  int currSum,
                  vector<int>& arr,
                  vector<vector<int>>& dp) {

        // Base Case
        if(idx == arr.size()) {
            return (currSum == target);
        }

        // Already computed
        if(dp[idx][currSum] != -1) {
            return dp[idx][currSum];
        }

        int take = 0;

        // Take current element if sum does not exceed target
        if(currSum + arr[idx] <= target) {
            take = solveMemo(idx + 1,
                             target,
                             currSum + arr[idx],
                             arr,
                             dp);
        }

        // Do not take current element
        int notTake = solveMemo(idx + 1,
                                target,
                                currSum,
                                arr,
                                dp);

        return dp[idx][currSum] = take + notTake;
    }


    int perfectSumMemo(vector<int>& arr, int target) {

        int n = arr.size();

        vector<vector<int>> dp(n + 1,
                               vector<int>(target + 1, -1));

        return solveMemo(0, target, 0, arr, dp);
    }



    /*
    ===========================================================
    2. TABULATION (BOTTOM UP DP)
    ===========================================================

    INTUITION:

    We convert recursion into loops.

    Recursive State:
    solve(idx, currSum)

    DP State:
    dp[idx][currSum]

    Base Case:
    When idx == n:
        dp[n][target] = 1

    Since recursion moves:
        idx -> idx + 1

    Tabulation moves backwards:
        idx from n-1 -> 0

    Transition:
    dp[idx][currSum]
        =
    dp[idx+1][currSum + arr[idx]]
        +
    dp[idx+1][currSum]
    ===========================================================
    */

    int perfectSumTab(vector<int>& arr, int target) {

        int n = arr.size();

        vector<vector<int>> dp(n + 1,
                               vector<int>(target + 1, 0));

        // Base Case
        dp[n][target] = 1;

        // Fill DP table
        for(int idx = n - 1; idx >= 0; idx--) {

            for(int currSum = target; currSum >= 0; currSum--) {

                int take = 0;

                // Take current element
                if(currSum + arr[idx] <= target) {
                    take = dp[idx + 1][currSum + arr[idx]];
                }

                // Do not take current element
                int notTake = dp[idx + 1][currSum];

                dp[idx][currSum] = take + notTake;
            }
        }

        return dp[0][0];
    }



    /*
    ===========================================================
    3. SPACE OPTIMIZATION
    ===========================================================

    INTUITION:

    In tabulation:
    dp[idx][currSum] depends only on dp[idx+1][...]

    So we only need:
    1. Current row
    2. Next row

    Thus space complexity reduces from:
        O(n * target)
    to:
        O(target)

    IMPORTANT:
    We cannot use a single array here because current row
    depends completely on next row.
    ===========================================================
    */

    int perfectSumSpaceOpt(vector<int>& arr, int target) {

        int n = arr.size();

        // Represents next row
        vector<int> next(target + 1, 0);

        // Base Case
        next[target] = 1;

        for(int idx = n - 1; idx >= 0; idx--) {

            // Represents current row
            vector<int> curr(target + 1, 0);

            for(int currSum = target; currSum >= 0; currSum--) {

                int take = 0;

                // Take current element
                if(currSum + arr[idx] <= target) {
                    take = next[currSum + arr[idx]];
                }

                // Do not take current element
                int notTake = next[currSum];

                curr[currSum] = take + notTake;
            }

            // Move current row to next row
            next = curr;
        }

        return next[0];
    }
};



int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter array elements: ";

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int target;

    cout << "Enter target sum: ";
    cin >> target;

    Solution obj;

    cout << "\n===== ANSWERS =====\n";

    cout << "Memoization Answer: "
         << obj.perfectSumMemo(arr, target)
         << endl;

    cout << "Tabulation Answer: "
         << obj.perfectSumTab(arr, target)
         << endl;

    cout << "Space Optimization Answer: "
         << obj.perfectSumSpaceOpt(arr, target)
         << endl;

    return 0;
}