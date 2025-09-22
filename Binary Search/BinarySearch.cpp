#include <bits/stdc++.h>
using namespace std;

int binarySearch(const vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (nums[mid] == target) {
            return mid; 
        } else if (nums[mid] < target) {
            low = mid + 1; 
        } else {
            high = mid - 1; 
        }
    }

    return -1; 
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
    cout << "\nEnter the target value to search for: ";
    cin >> target;

    int result = binarySearch(nums, target);

    if (result != -1) {
        cout << "\nElement found at index: " << result << endl;
    } else {
        cout << "\nElement not found in the array." << endl;
    }

    return 0;
}