#include <bits/stdc++.h>
using namespace std;

int findThePeak(const vector<int> &nums , int low , int high) {

    int n = nums.size();
    if(n == 1) return nums[0];
    if(arr[0] > arr[1]) return arr[0];
    if(arr[n-1] > arr[n-2]) return arr[n-1];

    while(high >= low) {
        int mid = (high + low)/2;
        if(nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1]) {
            return nums[mid];
        }
        else if(nums[mid] > nums[mid - 1]){
            low = low + 1;
        }
        else {
            high = mid + 1;
        }
    }

    return -1;
}

void display(const vector<int>& arr){
    for(int i = 0; i < arr.size(); i++) {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

int main()
{
    int n , target;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0;i < n; i++) {
        cin >> nums[i];
    }
    display(nums);

    int low = 0 , high = n-1;
    cout << findThePeak(nums , 0 , n-1) << endl;
    return 0;
}