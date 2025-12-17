#include <bits/stdc++.h>
using namespace std;

/*
===========================
BRUTE FORCE APPROACH
===========================
Intuition:
- Try every possible pair (i, j)
- Check if nums[i] + nums[j] == target
- If yes, return indices
- Time: O(n^2)
- Space: O(1)
*/
vector<int> twoSumBrute(vector<int>& nums, int target) {
    int n = nums.size();

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(nums[i] + nums[j] == target) {
                return {i, j}; // 0-based index
            }
        }
    }
    return {-1, -1};
}

/*
===========================
BETTER APPROACH (HASHING)
===========================
Intuition:
- Store each number in a map with its index
- For every element x, check if (target - x) already exists
- If yes → we found the pair
- Time: O(n)
- Space: O(n)
*/
vector<int> twoSumBetter(vector<int>& nums, int target) {
    unordered_map<int, int> mp;

    for(int i = 0; i < nums.size(); i++) {
        int need = target - nums[i];

        if(mp.find(need) != mp.end()) {
            return {mp[need], i};
        }

        mp[nums[i]] = i;
    }
    return {-1, -1};
}

/*
===========================
OPTIMAL APPROACH (TWO POINTERS)
===========================
Intuition:
- Works only on sorted array
- Place one pointer at start, one at end
- If sum == target → found
- If sum > target → move right pointer left
- If sum < target → move left pointer right
- Time: O(n)
- Space: O(1)
*/
vector<int> twoSumOptimal(vector<int>& nums, int target) {
    int i = 0;
    int j = nums.size() - 1;

    while(i < j) {
        int sum = nums[i] + nums[j];

        if(sum == target) {
            return {i, j};
        }
        else if(sum > target) {
            j--;
        }
        else {
            i++;
        }
    }
    return {-1, -1};
}

int main() {
    int n, target;
    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter elements: ";
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << "Enter target sum: ";
    cin >> target;

    vector<int> ans1 = twoSumBrute(nums, target);
    cout << "\nBrute Force Result: " << ans1[0] << " " << ans1[1];

    vector<int> ans2 = twoSumBetter(nums, target);
    cout << "\nBetter (Hashing) Result: " << ans2[0] << " " << ans2[1];

    // For optimal approach, array must be sorted
    sort(nums.begin(), nums.end());
    vector<int> ans3 = twoSumOptimal(nums, target);
    cout << "\nOptimal (Two Pointer) Result (on sorted array): "
         << ans3[0] << " " << ans3[1];

    return 0;
}
