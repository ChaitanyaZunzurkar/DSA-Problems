#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // BRUTE FORCE APPROACH
    int minSubArrayLenBrute(int target, vector<int>& nums) {
        int n = nums.size();
        int mini = INT_MAX;

        // Intuition:
        // Try every possible subarray starting from index i
        // Keep adding elements until sum >= target
        // Track minimum length

        for(int i = 0; i < n; i++) {
            int sum = 0;

            for(int j = i; j < n; j++) {
                sum += nums[j];

                // If condition satisfied, update answer
                if(sum >= target) {
                    mini = min(mini, j - i + 1);

                    // No need to expand further for this i
                    break;
                }
            }
        }

        return mini == INT_MAX ? 0 : mini;
    }


    // OPTIMAL APPROACH (SLIDING WINDOW)
    int minSubArrayLenOptimal(int target, vector<int>& nums) {
        int n = nums.size();
        int mini = INT_MAX;

        int sum = 0;
        int i = 0;

        // Intuition:
        // Use two pointers (i, j)
        // Expand window using j
        // When sum >= target, shrink window using i
        // This works because all numbers are positive

        for(int j = 0; j < n; j++) {
            sum += nums[j]; // include current element

            // shrink window until sum < target
            while(sum >= target) {
                mini = min(mini, j - i + 1);

                sum -= nums[i]; // remove left element
                i++;
            }
        }

        return mini == INT_MAX ? 0 : mini;
    }
};


int main() {
    int n, target;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter elements: ";
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << "Enter target: ";
    cin >> target;

    Solution obj;

    int bruteAns = obj.minSubArrayLenBrute(target, nums);
    int optimalAns = obj.minSubArrayLenOptimal(target, nums);

    cout << "\nBrute Force Answer: " << bruteAns << endl;
    cout << "Optimal Answer: " << optimalAns << endl;

    return 0;
}