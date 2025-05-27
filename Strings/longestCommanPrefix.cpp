#include <bits/stdc++.h>
using namespace std;

string longestCommanPrefix(vector<string>& arr){
    int i = 0;
    int j = 1;
    string result = arr[0];
    int mini = INT_MAX;

    while(i < arr.size() && j < arr.size()) {
        int k = 0;
        while(k < result.length() && k < arr[j].length()) {
            if(result[k] != arr[j][k]) {
                break;
            }
            k++;
        }
        mini = min(mini , k);
        i++;
        j++;
    }
    return arr[0].substr(0 , mini);
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
