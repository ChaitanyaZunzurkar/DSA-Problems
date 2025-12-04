#include <bits/stdc++.h>
using namespace std;

/*
    INTUITION for this brute-force solution:
    ----------------------------------------

    We want to count how many subarrays contain EXACTLY k odd numbers.

    The simplest approach:
    - Fix a starting index i
    - Expand the subarray by moving j from i → n-1
    - Maintain a running count of odd numbers in nums[i..j]
    - Whenever the number of odd numbers becomes exactly k, 
      we increment our answer.

    Why it works:
    - A subarray is defined by [i, j].
    - By trying every i and every j, we examine ALL possible subarrays.
    - Counting odd numbers as we extend j lets us decide if the subarray 
      meets the requirement (exactly k odds).

    Complexity:
    - Time:  O(n²) because we check all pairs (i, j).
    - Space: O(1)
*/

int numberOfSubarrays_brute(vector<int>& nums, int k) {
    int n = nums.size();
    int count = 0;        // counts odd numbers in current subarray
    int no_subarr = 0;    // final answer

    // Fix the starting index i
    for (int i = 0; i < n; i++) {
        count = 0;  // reset odd count for new starting point

        // Expand j to form subarrays [i..j]
        for (int j = i; j < n; j++) {
            if (nums[j] % 2 != 0) { 
                count++;          // nums[j] is odd → increment counter
            }

            if (count == k) {
                no_subarr++;      // found a subarray with exactly k odds
            }
        }
    }

    return no_subarr;
}

long long helper(vector<int>& nums, int k) {

    /*
        INTUITION for helper(nums, k):
        --------------------------------
        This function counts how many subarrays have 
                "at most k odd numbers".

        How the sliding window works:
        - r moves forward and expands the window.
        - Whenever nums[r] is odd, we increase `count`.
        - If count becomes more than k, the window is invalid.
          Therefore, we move `l` forward (shrink from left)
          and reduce the odd count when nums[l] is odd.
        - Once the window has at most k odd numbers again,
          every subarray ending at r with starting point in [l..r]
          is valid.
        
        Why add (r - l + 1)?
        - All subarrays:
                [l..r], [l+1..r], [l+2..r], ..., [r..r]
          have at most k odd numbers.
        - Number of such subarrays = window size = (r - l + 1).
    */

    int n = nums.size();
    int count = 0;        // number of odd numbers in current window
    int no_subarr = 0;    // total subarrays with at most k odds
    int l = 0;
    int r = 0;

    while (r < n) {

        // include nums[r] in the window
        if (nums[r] % 2 != 0) {
            count++;
        }

        // shrink window until it becomes valid (at most k odds)
        while (l < n && count > k) {
            if (nums[l] % 2 != 0) {
                count--;
            }
            l++;
        }

        // add all valid subarrays ending at r
        no_subarr += (r - l + 1);
        r++;
    }

    return no_subarr;
}

int numberOfSubarrays(vector<int>& nums, int k) {

    /*
        INTUITION for final formula:
        -----------------------------
        We want:
            number of subarrays with EXACTLY k odd numbers.

        Using the identity:
            exactly(k) = atMost(k) - atMost(k - 1)

        - helper(nums, k)     gives subarrays with at most k odds
        - helper(nums, k-1)   gives subarrays with at most k-1 odds
        Their difference isolates the subarrays that have
        exactly k odd numbers.
    */

    return helper(nums, k) - helper(nums, k - 1);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;                // number of elements

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    int k;
    cin >> k;                // target number of odd numbers

    cout << numberOfSubarrays_brute(nums, k) << "\n";

    return 0;
}
