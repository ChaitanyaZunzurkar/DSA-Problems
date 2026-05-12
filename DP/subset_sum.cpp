#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:

    /*
        Intuition:
        -------------------------
        We try all possible subsets using recursion.

        For every element, we have 2 choices:
        1. Take the element in the subset
        2. Do not take the element

        We keep adding selected elements into 'currentSum'.

        Base Cases:
        -------------------------
        1. If currentSum becomes equal to target,
           then subset exists -> return true

        2. If we reach the end of array and still
           do not get target sum -> return false

        Time Complexity:
        -------------------------
        O(2^n) because each element has 2 choices

        Space Complexity:
        -------------------------
        O(n) recursion stack
    */

    bool solve(vector<int>& arr, int idx, int currentSum, int target) {

        // If target sum is achieved
        if (currentSum == target)
            return true;

        // If all elements are processed
        if (idx == arr.size())
            return false;

        // Choice 1: Include current element
        bool take = solve(arr, idx + 1,
                          currentSum + arr[idx],
                          target);

        // Choice 2: Exclude current element
        bool notTake = solve(arr, idx + 1,
                             currentSum,
                             target);

        // If any choice gives true
        return take || notTake;
    }

    bool isSubsetSum(vector<int>& arr, int target) {
        return solve(arr, 0, 0, target);
    }
};

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int target;

    cout << "Enter target sum: ";
    cin >> target;

    Solution obj();

    // Creating object properly
    Solution sol;

    bool ans = sol.isSubsetSum(arr, target);

    if (ans)
        cout << "Subset with given sum exists." << endl;
    else
        cout << "Subset with given sum does not exist." << endl;

    return 0;
}