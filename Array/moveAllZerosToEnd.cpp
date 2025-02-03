#include <bits/stdc++.h>
using namespace std;

vector<int> moveAllZerosToEnd(vector<int> arr) {
    int n = arr.size();
    int j = 0;
        
    for(int i = 0;i < n; i++) {
        if(arr[i] != 0) {
            swap(arr[j] ,arr[i]);
            j++;
        }
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

    vector<int> result = moveAllZerosToEnd(arr);
    for(int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    return 0;
}