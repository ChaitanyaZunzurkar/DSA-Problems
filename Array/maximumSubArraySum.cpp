#include <bits/stdc++.h>
using namespace std;

int kadanes_Algorithm(const vector<int> &arr) {
    int maxi = INT_MIN;
    int sum = 0;

    for(int val : arr) {
        sum += val;
        maxi = max(maxi , sum);

        if(sum < 0) {
            sum = 0;
        }
    }

    return maxi;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << kadanes_Algorithm(arr) << endl;
    return 0;
}