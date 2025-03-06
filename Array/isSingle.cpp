#include <bits/stdc++.h>
using namespace std;

int isSingle(const vector<int> &arr) {
    int ans = 0;
    for(int val : arr) {
        ans = ans ^ val;
    }

    return ans;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << isSingle(arr) << endl;
    return 0;
}