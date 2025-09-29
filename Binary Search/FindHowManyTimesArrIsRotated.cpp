#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int findKRotation(vector<int> &arr) {
        /*
        Approach:
        - The problem is to find the index of the minimum element in a rotated sorted array.
        - That index represents how many times the sorted array has been rotated.
        
        Steps:
        1. Use binary search to find the minimum element.
        2. If the middle element is less than or equal to the high element,
           it means the right half is sorted, so the minimum lies in the left half (including mid).
        3. If the middle element is greater than the high element,
           it means the minimum lies in the right half.
        4. Track the minimum element and its index during the search.
        5. Return the index of the minimum element (rotation count).
        */

        int low = 0;
        int high = arr.size() - 1;
        int mini = INT_MAX;
        int index = -1;

        while (high >= low) {
            int mid = low + (high - low) / 2;
            if (arr[mid] <= arr[high]) {
                mini = min(arr[mid], mini);
                if (mini == arr[mid]) {
                    index = mid;
                }
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return index;
    }
};

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements of rotated sorted array:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    Solution obj;
    int rotations = obj.findKRotation(arr);

    cout << "The array is rotated " << rotations << " times.\n";

    return 0;
}
