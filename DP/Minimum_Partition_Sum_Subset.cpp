#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
        ---------------------------------------------------------
        APPROACH 1 : RECURSION + MEMOIZATION
        ---------------------------------------------------------

        INTUITION:

        We need to divide the array into 2 subsets such that:

        1. Both subsets contain exactly n/2 elements
        2. Difference of sums is minimum

        We recursively decide for every element:

        -> take into subset 1
        -> do not take

        State:
        idx      -> current index
        cnt      -> how many elements taken
        currSum  -> current subset sum

        At the end:
        subset1 sum = currSum
        subset2 sum = totalSum - currSum

        difference = abs(s1 - s2)

        This works but gives TLE for large constraints.
    */

    map<tuple<int,int,int>, int> dp;

    int solve(int idx,
              int cnt,
              int currSum,
              vector<int>& nums,
              int totalSum,
              int n) {

        if(idx >= n) {

            if(cnt == n / 2) {

                int s1 = currSum;
                int s2 = totalSum - currSum;

                return abs(s1 - s2);
            }

            return INT_MAX;
        }

        if(dp.find({idx, cnt, currSum}) != dp.end()) {
            return dp[{idx, cnt, currSum}];
        }

        int take = INT_MAX;

        // take current element
        if(cnt < n / 2) {

            take = solve(idx + 1,
                         cnt + 1,
                         currSum + nums[idx],
                         nums,
                         totalSum,
                         n);
        }

        // skip current element
        int notTake = solve(idx + 1,
                            cnt,
                            currSum,
                            nums,
                            totalSum,
                            n);

        return dp[{idx, cnt, currSum}] =
               min(take, notTake);
    }

    int minimumDifferenceMemo(vector<int>& nums) {

        int totalSum = 0;

        for(int x : nums) {
            totalSum += x;
        }

        dp.clear();

        return solve(0,
                     0,
                     0,
                     nums,
                     totalSum,
                     nums.size());
    }

    /*
        ---------------------------------------------------------
        APPROACH 2 : MEET IN THE MIDDLE (OPTIMIZED)
        ---------------------------------------------------------

        INTUITION:

        Constraints are large for normal recursion.

        Observation:
        n <= 30

        So split array into 2 halves.

        left half  -> first n/2 elements
        right half -> remaining n/2 elements

        Generate ALL possible subset sums for both halves.

        Store:
        left[k]  -> all subset sums using k elements
        right[k] -> all subset sums using k elements

        Then:

        if we take cnt elements from left,
        we must take (N-cnt) elements from right.

        Goal:
        Find subset sum closest to totalSum/2

        Binary search is used on right half sums.

        Complexity:
        O(2^(n/2) * log(2^(n/2)))

        This passes all constraints.
    */

    int minimumDifference(vector<int>& nums) {

        int n = nums.size();
        int N = n / 2;

        int totalSum = 0;

        for(int i = 0; i < n; i++) {
            totalSum += nums[i];
        }

        vector<vector<int>> left(N + 1);
        vector<vector<int>> right(N + 1);

        /*
            Generate all subset sums
        */
        for(int mask = 0; mask < (1 << N); mask++) {

            int cnt = 0;

            int leftSum = 0;
            int rightSum = 0;

            for(int i = 0; i < N; i++) {

                if(mask & (1 << i)) {

                    cnt++;

                    leftSum += nums[i];
                    rightSum += nums[i + N];
                }
            }

            left[cnt].push_back(leftSum);
            right[cnt].push_back(rightSum);
        }

        /*
            Sort right half for binary search
        */
        for(int i = 0; i <= N; i++) {
            sort(right[i].begin(),
                 right[i].end());
        }

        int mini = INT_MAX;

        /*
            Try every left subset sum
        */
        for(int cnt = 0; cnt <= N; cnt++) {

            for(int leftSum : left[cnt]) {

                int remaining = N - cnt;

                /*
                    We want:

                    s1 as close as possible to totalSum/2

                    s1 = leftSum + rightSum
                */
                int target =
                    totalSum / 2 - leftSum;

                auto it =
                    lower_bound(right[remaining].begin(),
                                right[remaining].end(),
                                target);

                /*
                    Check current iterator
                */
                if(it != right[remaining].end()) {

                    int s1 = leftSum + *it;
                    int s2 = totalSum - s1;

                    mini =
                        min(mini,
                            abs(s1 - s2));
                }

                /*
                    Check previous iterator
                */
                if(it != right[remaining].begin()) {

                    it--;

                    int s1 = leftSum + *it;
                    int s2 = totalSum - s1;

                    mini =
                        min(mini,
                            abs(s1 - s2));
                }
            }
        }

        return mini;
    }
};

int main() {

    int n;

    cout << "Enter size of array : ";
    cin >> n;

    vector<int> nums(n);

    cout << "Enter array elements : ";

    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution obj;

    cout << "\nUsing Recursion + Memoization : ";
    cout << obj.minimumDifferenceMemo(nums);

    cout << "\nUsing Meet in the Middle : ";
    cout << obj.minimumDifference(nums);

    return 0;
}