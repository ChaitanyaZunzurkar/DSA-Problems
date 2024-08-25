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

    // Method 1:- 
    // set<int> st;
    // for(int i = 0; i < arr.size(); i++) {
    //     st.insert(arr[i]);
    // }
    // int i = 0;
    // for(auto &val : st) {
    //     arr[i] = val;
    //     i++;
    // }
    // cout << st.size() << endl;

    // Method 2 :-
    if(nums.size() == 0) {
        cout << 0 << endl;
    }
    int j = 1;
    for(int i = 1; i < nums.size(); i++) {
         if(nums[i] != nums[j-1]) {
             nums[j] = nums[i];
             j++;
         }
    }
    cout << j << endl;
    return 0;
}
