// Brute Force Method with time complexcity O(n^2)

// #include <bits/stdc++.h>
// using namespace std;

// string longestCommanPrefix(vector<string>& arr){
//     int i = 0;
//     int j = 1;
//     string result = arr[0];
//     int mini = INT_MAX;

//     while(i < arr.size() && j < arr.size()) {
//         int k = 0;
//         while(k < result.length() && k < arr[j].length()) {
//             if(result[k] != arr[j][k]) {
//                 break;
//             }
//             k++;
//         }
//         mini = min(mini , k);
//         i++;
//         j++;
//     }
//     return arr[0].substr(0 , mini);
// }

// int main(){

//     int n;
//     cin >> n;
//     vector<string> arr(n);
//     for(int i = 0; i < n; i++) {
//         cin >> arr[i];
//     }

//     cout << longestCommanPrefix(arr) << endl;
//     return 0;
// }


#include <bits/stdc++.h>
using namespace std;

string longestCommanPrefix(vector<string>& arr){
    sort(arr.begin() , arr.end());
    int i = 0; 
    int j = 0;
    int n = arr.size();
    string result;
    while(i < n && j < n) {
        if(arr[0][i] != arr[n-1][j]) {
            break;
        }
        result += arr[0][i];
        i++;
        j++;
    }

    return result;
}

int main(){

    int n;
    cin >> n;
    vector<string> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << longestCommanPrefix(arr) << endl;
    return 0;
}
