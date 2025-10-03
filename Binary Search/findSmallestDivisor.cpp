#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Intuition (Brute Force - TLE):
    // -------------------------------
    // Try every possible divisor from 1 to max(nums). 
    // For each divisor, calculate the sum of ceil(nums[i]/divisor).
    // If sum <= threshold, keep track of the smallest divisor.
    // Works but slow because divisor range can be up to 1e6.
    int bruteForce(vector<int>& nums, int threshold) {
        int n = nums.size();
        int maxi = *max_element(nums.begin(), nums.end());
        int result = INT_MAX;

        for (int i = 1; i <= maxi; i++) {
            int sum = 0;
            for (int j = 0; j < n; j++) {
                sum += ceil((double)nums[j] / i);
            }
            if (sum <= threshold) {
                result = min(result, i);
            }
        }
        return result;
    }

    // Intuition (Optimized - Binary Search):
    // --------------------------------------
    // The sum of ceil(nums[i]/divisor) decreases as divisor increases.
    // So we can use binary search to find the smallest divisor such that sum <= threshold.
    // Time Complexity: O(n * log(max(nums)))
    int smallestDivisor(vector<int>& nums, int threshold) {
        int n = nums.size();
        int maxi = *max_element(nums.begin(), nums.end());

        int low = 1, high = maxi;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int sum = 0;
            for (int j = 0; j < n; j++) {
                sum += ceil((double)nums[j] / mid);
            }

            if (sum <= threshold) {
                high = mid - 1; // try smaller divisor
            } else {
                low = mid + 1; // need bigger divisor
            }
        }

        // After binary search, 'low' will be the smallest divisor satisfying the condition
        return low;
    }
};

int main() {
    int n, threshold;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Enter threshold: ";
    cin >> threshold;

    Solution sol;
    
    int ans = sol.smallestDivisor(nums, threshold);
    cout << "Smallest Divisor (Optimized): " << ans << endl;

    // For revision/future reference, brute force
    // int ansBrute = sol.bruteForce(nums, threshold);
    // cout << "Smallest Divisor (Brute Force): " << ansBrute << endl;

    return 0;
}
