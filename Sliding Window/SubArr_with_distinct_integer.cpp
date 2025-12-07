#include <bits/stdc++.h>
using namespace std;

/*
    INTUITION:
    We want to count subarrays that contain exactly K distinct elements.

    Brute Force Logic:
    1. Start from every index i.
    2. Expand j forward to form all subarrays starting at i.
    3. Maintain a set to store distinct elements in the current subarray.
    4. If set size == k → valid subarray → increase count.
    5. If set size > k → no need to continue because adding more elements
       will only increase distinct count → break early.
*/

int subarraysWithKDistinct_brute(vector<int>& nums, int k) { 
    int n = nums.size();
    int count = 0;

    for(int i = 0; i < n; i++) {
        set<int> st; // stores distinct elements in current subarray
        for(int j = i; j < n; j++) {
            st.insert(nums[j]);

            if(st.size() == k) {
                count++; // found a valid subarray
            }

            if(st.size() > k) {
                break; // further extension will only increase distinct elements
            }
        }
    }

    return count;
}

long long helper(vector<int>& nums, int k) {

    /*
        INTUITION OF helper(nums, k):

        This function counts subarrays that contain 
        AT MOST k DISTINCT elements using sliding window.

        Why sliding window works?
        - We expand window by moving r.
        - We shrink window when distinct elements exceed k.

        The key idea:
        For every right index r,
        all subarrays ending at r and starting from anywhere 
        in [l ... r] are valid as long as window has <= k distinct numbers.

        Hence, the number of valid subarrays ending at r is:
            (r - l + 1)
        
        We keep summing this.
    */

    int n = nums.size();
    long long count = 0;
    int l = 0, r = 0;

    map<int , int> mp; // stores frequency of elements in window

    while(r < n) {
        mp[nums[r]]++; // add element

        // shrink until we satisfy <= k distinct condition
        while(mp.size() > k) {
            mp[nums[l]]--;
            if(mp[nums[l]] == 0) mp.erase(nums[l]);
            l++;
        }
        
        // all subarrays ending at r and starting anywhere in [l..r] are valid
        count += (r - l + 1);

        r++;
    }
    
    return count;
}

int subarraysWithKDistinct_optimal(vector<int>& nums, int k) {

    /*
        INTUITION OF FINAL ANSWER:

        helper(nums, k)  -> number of subarrays with at most k distinct
        helper(nums, k-1)-> number of subarrays with at most k-1 distinct

        Their difference gives exactly k distinct:

            EXACT(K) = AT_MOST(K) - AT_MOST(K-1)

        This transforms a hard counting problem
        into two simpler sliding window computations.
    */

    return helper(nums , k) - helper(nums , k - 1);
}


int main() {
    int n, k;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter array elements: ";
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << "Enter value of k: ";
    cin >> k;

    int result = subarraysWithKDistinct_brute(nums, k);
    cout << "Number of subarrays with exactly " << k << " distinct elements = " << result << endl;

    return 0;
}
