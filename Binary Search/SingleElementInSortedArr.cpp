```cpp
#include <bits/stdc++.h>
using namespace std;

/*
Intuition for Approach 1:
-------------------------
We know the array is sorted and every element except one appears twice. 
If we carefully observe:
- Before the single element, pairs are aligned such that the first element of 
  the pair appears at even index and the second at odd index.
- After the single element, this pattern breaks.
We handle edge cases first (if the unique element is at start or end).
Then, using binary search:
1. If nums[mid] is unique (different from both neighbors), return it.
2. Otherwise, depending on index parity and whether nums[mid] forms a pair 
   with left or right neighbor, we discard half of the search space.
This ensures O(log n) time.
*/
class Solution1 {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int low = 1;
        int high = nums.size() - 2;
        int mid;

        if(nums.size() == 1) return nums[0];
        if(nums[0] != nums[1]) return nums[0];
        if(nums[nums.size() - 1] != nums[nums.size() - 2]) return nums[nums.size() - 1];

        while(high >= low) {
            mid = low + (high - low) / 2;
            if((nums[mid - 1] != nums[mid]) && (nums[mid] != nums[mid + 1])) {
                return nums[mid];
            } else if((nums[mid - 1] == nums[mid]) || (nums[mid] == nums[mid + 1])) {
                if(((mid % 2 != 0) && (nums[mid - 1] == nums[mid])) || ((mid % 2 == 0) && (nums[mid] == nums[mid + 1]))) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            } 
        }

        return nums[mid];
    } 
};

/*
Intuition for Approach 2:
-------------------------
This is a cleaner binary search approach.
- Ensure `mid` always points to the first element of a pair (so if mid is odd, reduce by 1).
- If nums[mid] == nums[mid+1], the unique element must lie in the right half → move low = mid+2.
- Else, it must be in the left half (including mid) → high = mid.
Loop until low == high, which will be the answer.
This is simpler and runs in O(log n).
*/
class Solution2 {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int low = 0;
        int high = nums.size() - 1;
        int mid;
        
        while(high > low) {
            mid = low + (high - low) / 2;
            if(mid % 2 == 1) {
                mid--; // ensure mid is even
            } 

            if(nums[mid] == nums[mid + 1]) {
                low = mid + 2;
            } else {
                high = mid;
            }
        }

        return nums[low];
    } 
};

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Enter elements of sorted array: ";
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution1 sol; // using Approach 1
    cout << "Single non-duplicate element is: " << sol.singleNonDuplicate(nums) << endl;

    return 0;
}
```
