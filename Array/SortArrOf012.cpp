#include <bits/stdc++.h>
using namespace std;

vector<int> sort012(vector<int> &arr) {
    int low = 0 , mid = 0 , high = arr.size() - 1;
    
    while(mid <= high) {
        if(arr[mid] == 0) {
            swap(arr[mid] , arr[low]);
            mid++;
            low++;
        } else if(arr[mid] == 1) {
            mid++;
        } else {
            swap(arr[mid] , arr[high]);
            high--;
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

    sort012(arr);
    for(int num : arr) {
        cout << num << " ";
    }
    return 0;
}