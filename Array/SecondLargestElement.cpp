#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int largest = -1;
    int secondLargest = -1;
    for (int i = 0; i < arr.size(); i++){
        if (largest < arr[i] ){
            secondLargest = largest;
            largest = arr[i];
        }
        else if(arr[i] > secondLargest && largest != arr[i]) {
            secondLargest = arr[i];
        }
    }
    cout << secondLargest << endl;
    return 0;
}