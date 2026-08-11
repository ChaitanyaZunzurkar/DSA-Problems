#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {

        /*
            INTUITION:

            We want:

                subarraySum % k == 0

            Using prefix sums:

                subarraySum = currentPrefixSum - previousPrefixSum

            Therefore:

                (currentPrefixSum - previousPrefixSum) % k == 0

            This happens when:

                currentPrefixSum % k
                    ==
                previousPrefixSum % k

            In other words:

                TWO PREFIX SUMS WITH THE SAME REMAINDER
                PRODUCE A SUBARRAY DIVISIBLE BY K.

            Example:

                k = 5

                Previous prefix sum = 7
                Current prefix sum  = 17

                7 % 5  = 2
                17 % 5 = 2

                Same remainder!

                Their difference:

                    17 - 7 = 10

                10 is divisible by 5.

            Therefore, unlike the previous problem,
            we DON'T store the exact prefix sum.

            We store:

                remainder -> frequency


            IMPORTANT:

                C++ can produce negative remainders.

                Example:

                    -2 % 5 = -2

                But we want the remainder to be in:

                    0, 1, 2, 3, 4

                Therefore:

                    if (rem < 0)
                        rem += k;
        */

        int sum = 0;
        int result = 0;

        unordered_map<int, int> ump;

        // Remainder 0 has occurred once before starting.
        //
        // This allows us to count subarrays starting from index 0
        // whose sum itself is divisible by k.
        ump[0] = 1;

        for (int i = 0; i < nums.size(); i++) {

            // Calculate current prefix sum
            sum += nums[i];

            // Find its remainder
            int rem = sum % k;

            // Convert negative remainder into positive remainder
            if (rem < 0) {
                rem += k;
            }

            /*
                If we have already seen the same remainder,
                each previous occurrence gives us one valid subarray.

                Example:

                    Previous remainder = 2
                    Current remainder  = 2

                    Difference is divisible by k.
            */
            result += ump[rem];

            // Store the current remainder for future prefix sums
            ump[rem]++;
        }

        return result;
    }
};

int main() {

    Solution obj;

    vector<int> nums = {4, 5, 0, -2, -3, 1};
    int k = 5;

    cout << obj.subarraysDivByK(nums, k) << endl;

    return 0;
}