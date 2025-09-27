#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;
        int result = INT_MAX;

        // If the array is already sorted (no rotation), the first element is the minimum.
        if(nums[low] < nums[high]) return nums[low];

        while(high >= low) {
            int mid = low + (high - low) / 2;

            // If the subarray is sorted, the minimum will be at nums[low].
            if(nums[low] <= nums[high]) {
                result = min(result , nums[low]);
                break;
            }

            // Right half is sorted, so minimum must lie in the left half (including mid).
            if(nums[mid] <= nums[high]) {
                result = min(nums[mid] , result);
                high = mid - 1;
            } 
            // Left half is sorted, so minimum lies in the right half.
            else {
                low = mid + 1;
            }
        } 

        return result;
    }
};

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter array elements: ";
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution sol;
    int result = sol.findMin(nums);

    cout << "Minimum element in the rotated sorted array is: " << result << endl;

    return 0;
}

