// Method 2 :-
// Time Complexcity :- O(n)
// space Complexcity :- O(maxi+1)

// #include <bits/stdc++.h>
// using namespace std;

// int max(const vector<int> &arr) {
//     int maxi = arr[0];
//     for(int i = 0; i < arr.size(); i++) {
//         if(maxi < arr[i]) {
//             maxi = arr[i];
//         }
//     }
//     return maxi;
// }
// int hashFunction(vector<int> &arr , int target) {
//     int maxi = max(arr);
//     vector<int> hsh(maxi+1, 0);

//     for(int i = 0; i < arr.size(); i++) {
//         hsh[arr[i]] += 1;
//     }
//     int count = hsh[target];
//     return count;
// }
// int main()
// {
//     int n , target;
//     cin >> n;
    
//     vector<int> arr(n);
//     for(int i = 0; i < n; i++) {
//         cin >> arr[i];
//     }
//     cin >> target;
//     cout << hashFunction(arr , target);

//     return 0;
// }

// Method 2:- 
// Time Complexcity :- O(n)
// space Complexcity :- O(maxi+1)

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n , target;
    cin >> n;

    vector<int> arr(n);    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> target;

    map<int , int> mp;
    for(int i = 0; i < n; i++) {
        mp[arr[i]]++;
    }

    cout << mp[target] << endl;
    return 0;
} 


