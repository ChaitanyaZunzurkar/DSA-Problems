#include <bits/stdc++.h>
using namespace std;

int lowerBound(const vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    int result = arr.size();
    
    while(high >= low) {
        int mid = low + (high - low) / 2;
        if(arr[mid] >= target) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    return result;
}

int main() {
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter the elements of the array (in any order):" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    sort(nums.begin(), nums.end());

    cout << "\nSorted array is: ";
    for(int i = 0; i < n; ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;

    int target;
    cout << "\nEnter the target value to find the lower bound for: ";
    cin >> target;

    int result = lowerBound(nums, target);

    cout << "\nLower bound is at index: " << result << endl;

    return 0;
}

