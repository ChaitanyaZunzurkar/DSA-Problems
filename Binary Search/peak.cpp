#include <bits/stdc++.h>
using namespace std;

/*
Intuition:
----------
A "peak" element is one which is strictly greater than its neighbors.
- If the array has only one element, that's the peak.
- If the first element is greater than the second → it's a peak at index 0.
- If the last element is greater than the second-last → it's a peak at index n-1.
Otherwise, we use binary search:
1. At any mid index, check if it's a peak (greater than both neighbors).
   → If yes, return mid.
2. If nums[mid] > nums[mid-1], then the slope is rising → the peak lies on the right side.
   → Move low = mid + 1.
3. Otherwise, the slope is falling → peak lies on the left side.
   → Move high = mid - 1.
This guarantees O(log n) time.
*/
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        int low = 1;
        int high = n - 1;

        if(n == 1) return 0;
        if(nums[0] > nums[1]) return 0;
        if(nums[n-1] > nums[n-2]) return n-1;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
                return mid;
            }

            // If slope is rising, move right
            if(nums[mid] > nums[mid - 1]) {
                low = mid + 1;
            } 
            // Else, move left
            else {
                high = mid - 1;
            }
        }

        return -1; // should not reach here
    }
};

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Enter elements of array: ";
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution sol;
    int peakIndex = sol.findPeakElement(nums);

    cout << "Peak element found at index: " << peakIndex 
         << " (value = " << nums[peakIndex] << ")" << endl;

    return 0;
}

