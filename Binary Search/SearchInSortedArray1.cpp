#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        while (high >= low) {
            int mid = low + (high - low) / 2;

            // If mid element is the target, return its index
            if (nums[mid] == target) {
                return mid;
            } 
            
            // Check if right half is sorted
            else if (nums[mid] <= nums[high]) {
                // If target lies in sorted right half, move low to mid+1
                if (nums[mid] < target && target <= nums[high]) {
                    low = mid + 1;
                } 
                // Else, search in left half
                else {
                    high = mid - 1;
                }
            } 
            
            // Left half is sorted
            else {
                // If target lies in sorted left half, move high to mid-1
                if (nums[low] <= target && target < nums[mid]) {
                    high = mid - 1;
                } 
                // Else, search in right half
                else {
                    low = mid + 1;
                }
            }
        }

        // Target not found
        return -1;
    }
};

int main() {
    int n, target;
    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter elements of rotated sorted array: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << "Enter target element: ";
    cin >> target;

    Solution sol;
    int index = sol.search(nums, target);

    if (index != -1) {
        cout << "Target found at index: " << index << endl;
    } else {
        cout << "Target not found in the array." << endl;
    }

    return 0;
}
