#include <bits/stdc++.h>
using namespace std;

/*
    ✅ Intuition (Optimized Binary Search on Answer)

    The problem asks us to split the array into k subarrays such that 
    the largest subarray sum is minimized.

    Let's define a "possible" function:
    For a given max subarray sum (mid), can we split the array into ≤ k parts
    so that no part’s sum exceeds mid?

    - If yes, try smaller 'mid' (move left)
    - If no, increase 'mid' (move right)

    So, the search space for the answer lies between:
        low = max element in array  (smallest possible max sum)
        high = total sum of array   (largest possible max sum)
    
    Using binary search on this space gives us O(N * log(sum(nums))) complexity.
*/

int splitArrayOptimized(vector<int>& nums, int k) {
    int n = nums.size();
    int maxi = *max_element(nums.begin(), nums.end());
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    int low = maxi, high = totalSum, ans = totalSum;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int count = 1;  // number of subarrays formed
        int sum = 0;

        for (int num : nums) {
            if (sum + num > mid) {
                count++;
                sum = num;
            } else {
                sum += num;
            }
        }

        if (count <= k) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}


int main() {
    int n, k;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Enter k: ";
    cin >> k;

    cout << "\nMinimum largest subarray sum (Optimized): " << splitArrayOptimized(nums, k) << endl;

    return 0;
}

