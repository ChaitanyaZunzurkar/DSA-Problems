#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        // Intuition:
        // This is a modified binary search for a rotated sorted array
        // with possible duplicates.
        // 1. If nums[mid] == target, we found it.
        // 2. If nums[low] == nums[mid] == nums[high], we can't determine
        //    which half is sorted, so we shrink the search space from both sides.
        // 3. If right half is sorted:
        //       - Check if target lies in right half. If yes, move low to mid+1.
        //       - Else, search in left half by moving high to mid-1.
        // 4. If left half is sorted:
        //       - Check if target lies in left half. If yes, move high to mid-1.
        //       - Else, search in right half by moving low to mid+1.
        while (high >= low) {
            int mid = low + (high - low) / 2;

            if (nums[mid] == target) {
                return true;
            }

            if ((nums[mid] == nums[low]) && (nums[mid] == nums[high])) {
                low++;
                high--;
                continue;
            }

            // Right half is sorted
            if (nums[mid] <= nums[high]) {
                if (nums[mid] < target && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            // Left half is sorted
            else {
                if (nums[low] <= target && target < nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
        }

        return false;
    }
};

int main() {
    int n, target;
    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << "Enter target to search: ";
    cin >> target;

    Solution sol;
    if (sol.search(nums, target)) {
        cout << "Target found in the array." << endl;
    } else {
        cout << "Target not found in the array." << endl;
    }

    return 0;
}
