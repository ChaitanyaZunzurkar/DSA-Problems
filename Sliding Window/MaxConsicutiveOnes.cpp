#include <bits/stdc++.h>
using namespace std;

// ------------------------------------------------------------
// BRUTE FORCE INTUITION
// ------------------------------------------------------------
// We try every possible starting index i.
// For each i, we extend the window to the right (j = i → n-1).
// We count how many zeros are inside the window.
// If zeros ≤ k, window is valid → update maximum length.
// If zeros > k, window becomes invalid → break.
// This checks every window starting at every i → O(n²).
// ------------------------------------------------------------
int longestOnes_brute(vector<int>& nums, int k) {
    if (k >= nums.size()) return nums.size();
    
    int n = nums.size();
    int maxi = 0;
    int length = 0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        count = 0;
        for (int j = i; j < n; j++) {

            // add the new element and update zero count
            if (nums[j] == 0) {
                count++;
            }

            // valid window
            if (count <= k) {
                length = j - i + 1;
                maxi = max(maxi, length);
            } 
            else {
                // more than k zeros → break from j loop
                break;
            }
        }
    }

    return maxi;
}

// ------------------------------------------------------------
// BETTER INTUITION (Sliding Window with shrink while invalid)
// ------------------------------------------------------------
// We maintain a window [l, r].
// Expand r one-by-one.
// If nums[r] is zero, increase zero count.
// If window has more than k zeros, shrink from the left (l++)
// until the window becomes valid again.
// At each valid window, calculate length (r - l + 1).
// Every index moves at most once → O(n).
// ------------------------------------------------------------
int longestOnes_better(vector<int>& nums, int k) {
    if (k == nums.size()) return nums.size();
    int n = nums.size();
    int maxi = 0;
    int length = 0;
    int count = 0;
    int l = 0; 
    int r = 0;
        
    while (r < n) {

        // include nums[r] and update zero count
        if (nums[r] == 0) {
            count++;
        }

        // shrink window until it becomes valid
        while (count > k) {
            if (nums[l] == 0) {
                count--;
            }
            l++;
        }

        // valid window → update answer
        length = r - l + 1;
        maxi = max(maxi , length);

        r++;
    }

    return maxi;
}

// ------------------------------------------------------------
// OPTIMAL INTUITION (More concise sliding window)
// ------------------------------------------------------------
// Same sliding window idea as "better".
// The only difference: instead of using a while-loop to shrink,
// we use a slightly more compact shrinking logic.
// Window always maintained such that zeros ≤ k.
// r expands, l shrinks, and window length updates.
// Overall O(n) time, O(1) space.
// ------------------------------------------------------------
int longestOnes_optimal(vector<int>& nums, int k) {
    if (k == nums.size()) return nums.size();
    int n = nums.size();
    int maxi = 0;
    int length = 0;
    int count = 0;
    int l = 0; 
    int r = 0;
        
    while (r < n) {

        // expand window
        if (nums[r] == 0) {
            count++;
        }

        // shrink by one step if invalid
        if (count > k) {
            if (nums[l] == 0) {
                count--;
            }
            l++;
        }

        // valid window → update result
        length = r - l + 1;
        maxi = max(maxi , length);

        r++;
    }

    return maxi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << longestOnes_optimal(nums, k) << "\n";

    return 0;
}
