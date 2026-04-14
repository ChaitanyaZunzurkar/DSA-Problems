#include <bits/stdc++.h>
using namespace std;

/*
INTUITION:

Same as 3-sum, but target = 0

IMPORTANT DIFFERENCE:
We must avoid duplicate triplets

Why duplicates happen?
Because sorted array may contain repeated numbers

Solution:
- Skip duplicate i
- Skip duplicate left/right after finding answer
*/

void tripletSumZero(vector<int>& arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());

    for(int i = 0; i < n - 2; i++) {

        // skip duplicate i
        if(i > 0 && arr[i] == arr[i-1]) continue;

        int left = i + 1;
        int right = n - 1;

        while(left < right) {
            int sum = arr[i] + arr[left] + arr[right];

            if(sum == 0) {
                cout << arr[i] << " " << arr[left] << " " << arr[right] << "\n";

                // skip duplicates
                while(left < right && arr[left] == arr[left+1]) left++;
                while(left < right && arr[right] == arr[right-1]) right--;

                left++;
                right--;
            }
            else if(sum < 0) {
                left++;
            }
            else {
                right--;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];

    tripletSumZero(arr);

    return 0;
}