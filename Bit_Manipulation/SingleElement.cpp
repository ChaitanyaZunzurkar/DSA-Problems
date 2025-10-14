#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        // Intuition:
        // XOR of a number with itself is 0: a ^ a = 0
        // XOR of a number with 0 is the number itself: a ^ 0 = a
        // So if we XOR all numbers in the array, 
        // the pairs cancel each other and only the single number remains.
        int XOR = nums[0];
        for(int i = 1; i < nums.size(); i++) {
            XOR ^= nums[i];
        }
        return XOR;
    }
};

int main() {
    Solution sol;

    // Example input
    vector<int> nums = {4, 1, 2, 1, 2};

    // Call the function
    int result = sol.singleNumber(nums);

    // Output the result
    cout << "The single number is: " << result << endl;

    return 0;
}
