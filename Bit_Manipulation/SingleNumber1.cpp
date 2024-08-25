#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int XOR = 0;
    for(int i = 0; i < n; i++) {
        XOR ^= arr[i];
    }
    cout << XOR << endl;
    return 0;
}