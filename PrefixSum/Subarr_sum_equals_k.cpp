#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {

        /*
            INTUITION:

            Suppose prefixSum[i] = sum of elements from 0 to i.

            If we want a subarray whose sum is exactly k:

                prefixSum[i] - prefixSum[j] = k

            Rearranging:

                prefixSum[j] = prefixSum[i] - k

            So, when we calculate the current prefix sum "sum",
            we need to check:

                How many times have we previously seen
                (sum - k)?

            Every such previous prefix sum gives us one
            subarray whose sum is exactly k.

            Therefore, our hashmap stores:

                prefix sum -> frequency

            Example:

                nums = [1, 1, 1]
                k = 2

                Prefix sums:
                0, 1, 2, 3

                At sum = 2:

                    sum - k = 2 - 2 = 0

                We have already seen prefix sum 0 once.

                Therefore, [1, 1] is a valid subarray.

            IMPORTANT:

                ump[0] = 1

            Why?

            Before processing any element, we consider that
            prefix sum = 0 has already occurred once.

            This allows us to detect subarrays starting from index 0.
        */

        int sum = 0;
        int result = 0;

        unordered_map<int, int> ump;

        // Prefix sum 0 exists once before we start.
        ump[0] = 1;

        for (int i = 0; i < nums.size(); i++) {

            // Calculate current prefix sum
            sum += nums[i];

            // We need a previous prefix sum equal to sum - k
            int query = sum - k;

            // Every occurrence of query gives one valid subarray
            result += ump[query];

            // Store current prefix sum for future subarrays
            ump[sum]++;
        }

        return result;
    }
};

int main() {

    Solution obj;

    vector<int> nums = {1, 1, 1};
    int k = 2;

    cout << obj.subarraySum(nums, k) << endl;

    return 0;
}