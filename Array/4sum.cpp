#include <bits/stdc++.h>
using namespace std;

/*
INTUITION:

Goal: Find 4 elements such that sum = target

Brute force → O(n^4)

Optimization:
1. Sort array
2. Fix TWO elements (i, j)
3. Apply two-pointer for remaining

Why works?
We reduce problem:
4-sum → 2-sum (using two-pointer)

IMPORTANT:
- Avoid duplicates for i and j
- Use long long to prevent overflow
*/

void fourSum(vector<int>& arr, int target) {
    int n = arr.size();
    sort(arr.begin(), arr.end());

    for(int i = 0; i < n - 3; i++) {

        // skip duplicate i
        if(i > 0 && arr[i] == arr[i-1]) continue;

        for(int j = i + 1; j < n - 2; j++) {

            // skip duplicate j
            if(j > i + 1 && arr[j] == arr[j-1]) continue;

            int left = j + 1;
            int right = n - 1;

            while(left < right) {
                long long sum = (long long)arr[i] + arr[j] + arr[left] + arr[right];

                if(sum == target) {
                    cout << arr[i] << " " << arr[j] << " "
                         << arr[left] << " " << arr[right] << "\n";

                    // skip duplicates
                    while(left < right && arr[left] == arr[left+1]) left++;
                    while(left < right && arr[right] == arr[right-1]) right--;

                    left++;
                    right--;
                }
                else if(sum < target) {
                    left++;
                }
                else {
                    right--;
                }
            }
        }
    }
}

int main() {
    int n, target;
    cin >> n;

    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];

    cin >> target;

    fourSum(arr, target);

    return 0;
}