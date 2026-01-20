#include <bits/stdc++.h>
using namespace std;

int longestSubarray(vector<int> &arr, int k) {
    int n = arr.size();

    // Map to store: prefixSum -> first index where it appeared
    map<long long, int> mp;

    long long sum = 0; // prefix sum
    int maxi = 0;      // longest length found

    /*
    Intuition:
    - If prefixSum[i] - prefixSum[j] = k
      then subarray (j+1 to i) has sum = k
    - So we store earliest index of every prefix sum
    - Using earliest index gives maximum length
    */

    // Important base case:
    // prefix sum 0 occurs before array starts (index -1)
    mp[0] = -1;

    for (int i = 0; i < n; i++) {
        sum += arr[i];

        // Store the prefix sum only if it is seen first time
        // (we want earliest index for longest subarray)
        if (mp.find(sum) == mp.end()) {
            mp[sum] = i;
        }

        // If (sum - k) exists, we found a subarray with sum = k
        if (mp.find(sum - k) != mp.end()) {
            maxi = max(maxi, i - mp[sum - k]);
        }
    }

    return maxi;
}

int main() {
    int n, k;
    cout << "Enter size of array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter value of k: ";
    cin >> k;

    int result = longestSubarray(arr, k);

    cout << "Length of longest subarray with sum " << k << " is: " << result << endl;

    return 0;
}
