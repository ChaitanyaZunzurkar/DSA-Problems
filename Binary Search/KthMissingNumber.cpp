#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
      Brute Force Approach (O(n)):
      ----------------------------
      - Start with k
      - For every element arr[i]:
          If arr[i] <= k, it means this number is not missing (it's present in array),
          so shift k by +1 because the k-th missing is further ahead.
      - At the end, k will itself represent the answer.
    */
    int findKthPositiveBrute(vector<int>& arr, int k) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] <= k) {
                k++; // shift the window of missing numbers
            } else {
                break; // no need to check further, array is sorted
            }
        }
        return k;
    }

    /*
      Optimized Binary Search Approach (O(log n)):
      --------------------------------------------
      Idea:
      - At index mid:
          missing = arr[mid] - (mid+1)
          This tells how many numbers are missing before arr[mid].
      - If missing < k → search right (need more missing)
      - Else search left.
      - At the end, 'low' points to the first index where missing >= k.
      - Answer = low + k
    */
    int findKthPositiveOptimized(vector<int>& arr, int k) {
        int n = arr.size();
        int low = 0, high = n - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int missing = arr[mid] - (mid + 1);

            if (missing < k) {
                low = mid + 1;  // need more missing → go right
            } else {
                high = mid - 1; // too many missing → go left
            }
        }

        // Answer is (low + k)
        return low + k;
    }
};

int main() {
    Solution sol;

    int n, k;
    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements (sorted, distinct, positive): ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter k: ";
    cin >> k;

    // Using the Optimized Binary Search approach
    int result = sol.findKthPositiveOptimized(arr, k);
    cout << "The " << k << "-th missing positive number is: " << result << endl;

    // If you want to also test brute force:
    // int resultBrute = sol.findKthPositiveBrute(arr, k);
    // cout << "(Brute Force) The " << k << "-th missing positive number is: " << resultBrute << endl;

    return 0;
}
