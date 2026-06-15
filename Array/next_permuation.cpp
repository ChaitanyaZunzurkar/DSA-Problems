#include <bits/stdc++.h>
using namespace std;

void backtracking(vector<int>& nums, int start, vector<vector<int>>& allPermutations) {
    if(start == nums.size()) {
        allPermutations.push_back(nums);
        return;
    }

    for(int i = start; i < nums.size(); i++) {
        swap(nums[start], nums[i]);

        backtracking(nums, start + 1, allPermutations);

        swap(nums[start], nums[i]);
    }
}

void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int ind = -1;
    for(int i = n-2; i >= 0; i--) {
        if(nums[i] < nums[i+1]) {
            ind = i;
            break;
        }
    }

    if(ind == -1) {
        reverse(nums.begin() , nums.end());
        return;
    }

    for(int i = n-1; i > ind; i--) {
        if(nums[i] > nums[ind]) {
            swap(nums[i] , nums[ind]);
            break;
        }
    }

    reverse(nums.begin() + ind + 1 , nums.end());
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    nextPermutation(nums);
    for(int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }

    // vector<vector<int>> allPermutations;
    // backtracking(nums, 0, allPermutations);
    // sort(allPermutations.begin(), allPermutations.end());

    // auto last = unique(allPermutations.begin(), allPermutations.end());
    // allPermutations.erase(last, allPermutations.end());

    // for(int i = 0; i < allPermutations.size(); i++) {
    //     if(nums == allPermutations[i]) {
    //         nums = allPermutations[(i + 1) % allPermutations.size()];
    //         break;
    //     }
    // }

    return 0;
}