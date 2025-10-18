#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();

        // 🧠 Intuition:
        // For n elements, there are 2^n possible subsets (including empty set)
        // We can represent each subset using a binary number of n bits:
        // - If bit j in number i is set (1), include nums[j] in subset
        // - If bit j is 0, exclude nums[j]
        //
        // Example: nums = [1, 2, 3]
        // i = 5 (binary 101) => include nums[0] and nums[2] => subset = [1,3]

        int totalSubsets = 1 << n; // 2^n subsets
        vector<vector<int>> ans;

        for (int i = 0; i < totalSubsets; i++) {
            vector<int> subset;
            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) != 0) {
                    subset.push_back(nums[j]);
                }
            }
            ans.push_back(subset);
        }

        return ans;
    }
};

int main() {
    // 🔹 INPUT FORMAT:
    // First line: an integer n (number of elements in array)
    // Second line: n space-separated integers (array elements)
    //
    // Example Input:
    // 3
    // 1 2 3
    //
    // Output: all subsets (order may vary)

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution obj;
    vector<vector<int>> ans = obj.subsets(nums);

    cout << "All subsets:\n";
    for (auto &subset : ans) {
        cout << "[";
        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if (i != subset.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }

    return 0;
}
