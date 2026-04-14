#include <bits/stdc++.h>
using namespace std;

/*
INTUITION:

Goal: Find all triplets such that
arr[i] + arr[j] + arr[k] = target

Brute force → O(n^3)

Optimization:
1. Sort the array
2. Fix one element (i)
3. Use two-pointer for remaining array

Why sorting helps?
- If sum is small → move left forward (increase sum)
- If sum is large → move right backward (decrease sum)

This works because sorted array gives ORDER.
*/

void tripletSumK(vector<int>& arr, int k) {
    int n = arr.size();
    sort(arr.begin(), arr.end());

    for(int i = 0; i < n - 2; i++) {

        int left = i + 1;
        int right = n - 1;

        while(left < right) {
            int sum = arr[i] + arr[left] + arr[right];

            if(sum == k) {
                cout << arr[i] << " " << arr[left] << " " << arr[right] << "\n";
                left++;
                right--;
            }
            else if(sum < k) {
                left++;   // need bigger sum
            }
            else {
                right--;  // need smaller sum
            }
        }
    }
}

int main() {
    int n, k;
    cin >> n;

    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];

    cin >> k;

    tripletSumK(arr, k);

    return 0;
}