#include <bits/stdc++.h>
using namespace std;

bool isSorted(const vector<int> &arr) {
    int n = arr.size();
    int count = 0;
    for(int i = 1; i < arr.size(); i++) {
        if(arr[i-1] > arr[i]) {
            count++;
        }
    }
    if(arr[n-1] > arr[0]) {
        count++;
    }

    return count <= 1;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << isSorted(arr);
    return 0;
}


