#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
    Problem:
    --------
    Find the maximum subarray sum if you are allowed to delete
    at most one element from the chosen subarray.

    Example:
    --------
    arr = [1, -2, 0, 3]

    Without deletion:
        Maximum Sum = 3

    Delete -2:
        1 + 0 + 3 = 4

    Answer = 4


    --------------------------------------------------------------------
    INTUITION
    --------------------------------------------------------------------

    This problem is an extension of Kadane's Algorithm.

    In Kadane's Algorithm we keep only one state:

        noDelete = Maximum subarray sum ending at current index.

    Since we are allowed to delete one element, we need one more state.

        oneDelete = Maximum subarray sum ending at current index
                    after deleting exactly one element.

    --------------------------------------------------------------------
    STATE TRANSITIONS
    --------------------------------------------------------------------

    1) noDelete

       Either

       a) Start a new subarray from current element.

               arr[i]

       OR

       b) Extend previous subarray.

               previousNoDelete + arr[i]

       Therefore,

       noDelete = max(arr[i], previousNoDelete + arr[i])


    ------------------------------------------------------------

    2) oneDelete

       Two possibilities:

       Case 1:
       --------
       We already deleted some element earlier.

            previousOneDelete + arr[i]

       Case 2:
       --------
       Delete the CURRENT element.

       If we delete arr[i], then the best sum ending here becomes

            previousNoDelete

       Therefore,

       oneDelete =
            max(previousOneDelete + arr[i],
                previousNoDelete)

    --------------------------------------------------------------------
    Time Complexity : O(n)

    Space Complexity : O(1)
*/

class Solution {
public:
    int maximumSum(vector<int>& arr) {

        int n = arr.size();

        // Maximum sum ending at current index without deletion
        int noDelete = arr[0];

        // Maximum sum ending at current index after one deletion
        int oneDelete = INT_MIN;

        // Final answer
        int ans = arr[0];

        for(int i = 1; i < n; i++) {

            // Store previous values because both states
            // depend on previous iteration.
            int prevNoDelete = noDelete;
            int prevOneDelete = oneDelete;

            // Normal Kadane transition
            noDelete = max(arr[i], prevNoDelete + arr[i]);

            // If one deletion already happened,
            // extend that subarray.
            int extendDeleted;

            if(prevOneDelete == INT_MIN)
                extendDeleted = INT_MIN;
            else
                extendDeleted = prevOneDelete + arr[i];

            // Either
            // 1. Extend previously deleted subarray
            // 2. Delete current element
            oneDelete = max(extendDeleted, prevNoDelete);

            // Update global answer
            ans = max(ans, max(noDelete, oneDelete));
        }

        return ans;
    }
};

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    Solution obj;

    cout << "\nMaximum Subarray Sum With At Most One Deletion = "
         << obj.maximumSum(arr);

    return 0;
}