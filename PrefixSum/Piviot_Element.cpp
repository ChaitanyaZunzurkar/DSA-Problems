#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {

        /*
            INTUITION:

            We need to find an index where:

                sum of elements on LEFT
                    ==
                sum of elements on RIGHT

            Example:

                nums = [1, 7, 3, 6, 5, 6]

                At index 3:

                Left side:
                    1 + 7 + 3 = 11

                Right side:
                    5 + 6 = 11

                Therefore, index 3 is the pivot index.


            ------------------------------------------------
            KEY OBSERVATION
            ------------------------------------------------

            First calculate the total sum of the array.

                totalSum = sum of all elements


            Suppose we are currently at index i.

            Let:

                leftSum = sum of elements before i

            Then:

                rightSum = totalSum - leftSum - nums[i]


            We need:

                leftSum == rightSum


            Therefore:

                leftSum == totalSum - leftSum - nums[i]


            So we simply check this condition for every index.


            ------------------------------------------------
            WHY DON'T WE NEED A HASHMAP?
            ------------------------------------------------

            In the previous problems, we needed to count how many
            previous prefix sums/remainders existed.

            Here, we only need the LEFT SUM.

            We can maintain it using one variable:

                leftSum


            After checking the current index, add nums[i] to
            leftSum before moving to the next index.
        */

        int totalSum = 0;

        // Step 1: Calculate the total sum of the array
        for (int x : nums) {
            totalSum += x;
        }

        int leftSum = 0;

        // Step 2: Check every index as a possible pivot
        for (int i = 0; i < nums.size(); i++) {

            /*
                Right sum = everything except:

                1. Elements on the left
                2. Current element

                Therefore:

                    rightSum = totalSum - leftSum - nums[i]
            */
            int rightSum = totalSum - leftSum - nums[i];

            // If both sides are equal, we found the pivot
            if (leftSum == rightSum) {
                return i;
            }

            /*
                Current element becomes part of the LEFT side
                when we move to the next index.
            */
            leftSum += nums[i];
        }

        // No pivot index exists
        return -1;
    }
};

int main() {

    Solution obj;

    vector<int> nums = {1, 7, 3, 6, 5, 6};

    cout << obj.pivotIndex(nums) << endl;

    return 0;
}