#include <bits/stdc++.h>
using namespace std;

vector<int> reverse(vector<int> arr) {
    int n = arr.size();
    int half = n/2;

    cout << half << endl;
    int j = n-1;
    for(int i = 0; i < half; i++) {
        swap(arr[i] , arr[j]);
        j--;
    }
    return arr;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> result = reverse(arr);
    for(int i = 0; i < n; i++) {
        cout << result[i] << " ";
    }

    return 0;
}