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

    int maxi = arr[0];
    for(int i = 0; i < arr.size(); i++) {
        if(maxi < arr[i]) {
            maxi = arr[i];
        }
    }
    cout << maxi << endl;
    return 0;
}