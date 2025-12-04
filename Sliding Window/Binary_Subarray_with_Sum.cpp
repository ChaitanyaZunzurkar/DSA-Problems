#include <bits/stdc++.h>
using namespace std;

/*
 Intuition (written as comments):
 --------------------------------
 We want to count all contiguous subarrays whose element-sum equals `goal`.
 A brute-force approach iterates over every possible starting index i,
 then extends the subarray to every possible ending index j >= i, 
 maintaining the running sum for that subarray. Whenever running sum == goal,
 we increment the answer.

 Complexity:
 - Time: O(n^2) in the worst-case because we examine every pair (i, j).
 - Space: O(1) extra space (only a few ints used).

 This implementation reads input from standard input (stdin).
 Input format expected:
   n             (number of elements in the array)
   nums[0] nums[1] ... nums[n-1]   (n integers, space or newline separated)
   goal          (integer target sum)

 Example:
   5
   1 0 1 0 1
   2
 Output (single integer printed):
   4

 That example counts subarrays with sum == 2.
*/

int numSubarraysWithSum_brute(const vector<int>& nums, int goal) {
    int n = nums.size();
    int count = 0;

    // For each starting index i, accumulate sum of subarray nums[i..j].
    for (int i = 0; i < n; ++i) {
        int sum = 0;                 // reset running sum for new start i
        for (int j = i; j < n; ++j) {
            sum += nums[j];          // extend subarray to include nums[j]
            if (sum == goal) {
                ++count;            // found a subarray with required sum
            }
        }
    }

    return count;
}

long long helper(vector<int>& nums, int goal) {

    /*
        INTUITION for helper(nums, goal):
        --------------------------------
        This function counts how many subarrays have sum <= goal 
        in a BINARY array (only 0s and 1s).

        Why does sliding window work?
        - When we expand the window by moving 'r', the sum only increases 
          because elements are 0 or 1.
        - If at any point sum > goal, we shrink from the left by moving 'l' 
          until the window becomes valid again (sum <= goal).

        Important observation (binary array):
        - Every time the window [l..r] becomes valid (sum <= goal),
          ALL subarrays ending at index r and starting anywhere from l..r 
          are also valid.
          Therefore, number of new valid subarrays = (r - l + 1).

        So helper() returns:
            Count of all subarrays whose sum ≤ goal.
    */

    if (goal < 0) return 0;
    int n = nums.size();
    long long count = 0;
    long long sum = 0;
    int l = 0;
    int r = 0;

    while (r < n) {
        sum += nums[r];          // expand window by including nums[r]

        // shrink window until sum <= goal
        while (sum > goal) {
            sum -= nums[l];
            l++;
        }

        // all subarrays ending at r and starting from l..r are valid
        count += (r - l + 1);
        r++;
    }

    return count;
}

int numSubarraysWithSum_optimal(vector<int>& nums, int goal) {

    /*
        INTUITION for the final formula:
        --------------------------------
        We want subarrays with sum == goal.

        helper(nums, goal)
            counts subarrays with sum <= goal

        helper(nums, goal - 1)
            counts subarrays with sum <= goal - 1

        The difference isolates the ones with exact sum:
        
            subarrays with sum == goal
            =
            helper(goal) - helper(goal - 1)

        This trick works because in a binary array,
        sums grow step-by-step and the counts can be separated cleanly.
    */

    return helper(nums, goal) - helper(nums, goal - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        // no input
        return 0;
    }

    vector<int> nums(n);
    for (int i = 0; i < n; ++i) cin >> nums[i];

    int goal;
    cin >> goal;

    int result = numSubarraysWithSum_brute(nums, goal);
    cout << result << '\n';

    return 0;
}
