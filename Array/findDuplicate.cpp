#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {

        /*
        ------------------------------------------------------------
        INTUITION (Floyd's Cycle Detection / Tortoise and Hare)
        ------------------------------------------------------------

        We are given an array of size n+1 containing numbers from 1 to n.
        Since there are n+1 numbers but only n unique values,
        at least one number must be repeated.

        Think of every index as a node.

        From index i, we move to nums[i].

        Example:
        nums = [1,3,4,2,2]

        Index : 0 -> 1 -> 3 -> 2 -> 4
                          ^         |
                          |_________|

        Since one value repeats, two different indices point to
        the same node, which creates a cycle.

        So the problem becomes:
        "Find the entrance of the cycle."

        Floyd's Algorithm has two phases.

        Phase 1:
        ----------
        Move:
        slow = one step
        fast = two steps

        Eventually both pointers meet inside the cycle.

        Phase 2:
        ----------
        Move slow back to index 0.

        Now move both pointers one step at a time.

        The point where they meet again is the duplicate number.

        Time Complexity  : O(n)
        Space Complexity : O(1)
        */

        int slow = 0;
        int fast = 0;

        // Phase 1: Find the meeting point inside the cycle
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];

            if (slow == fast) {

                // Phase 2: Find the entrance of the cycle
                slow = 0;

                while (slow != fast) {
                    slow = nums[slow];
                    fast = nums[fast];
                }

                return slow;
            }
        }

        return -1;
    }
};

int main() {

    int n;

    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements:\n";

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution obj;

    int duplicate = obj.findDuplicate(nums);

    cout << "\nDuplicate Number = " << duplicate << endl;

    return 0;
}