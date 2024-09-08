#include <bits/stdc++.h>
using namespace std;
void insertionSort(vector<int> &arr) {
    for(int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int pos = i - 1;

        while(pos >= 0 && arr[pos] > key) {
            arr[pos + 1] = arr[pos];
            pos = pos - 1;
        }
        arr[pos + 1] = key;
    }
}

int main()
{
    int n;
    cout << "Enter size of the array : ";
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cout << "Enter element at postion " << i+1 << " : ";
        cin >> arr[i];
    }
    cout << endl;
    cout << "Array before sorting : " << endl;
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    insertionSort(arr);
    cout << endl;
    cout << "Array After sorting : " << endl;
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}