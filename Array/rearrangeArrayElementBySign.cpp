// Variation 1
// Time Complexcity :- O(n)
// Space Complexcity :- O(n)

// #include <bits/stdc++.h>
// using namespace std;

// vector<int> rearrangeArrayBySign(vector<int> &arr) {
//     int n = arr.size();
//     vector<int> result;
//     result.resize(n);
//     int positiveIndex = 0;
//     int negativeIndex = 1;

//     for(int i = 0; i < n; i++) {
//         if(arr[i] > 0) {
//             result[positiveIndex] = arr[i];
//             positiveIndex += 2;
//         } else {
//             result[negativeIndex] = arr[i];
//             negativeIndex += 2;
//         }  
//     }
//     return result;
// }

// int main()
// {
//     int n;
//     cin >> n;
//     vector<int> arr(n);
//     for(int i = 0; i < n; i++) {
//         cin >> arr[i];
//     }

//     vector<int> result = rearrangeArrayBySign(arr);
    
//     for(int x : result) {
//         cout << x << " ";
//     }
//     return 0;
// }



// Variation 2
// Time Complexcity :- O(n)
// Space Complexcity :- O(n)

#include <bits/stdc++.h>
using namespace std;

vector<int> rearrangeArrayBySign(vector<int> &arr) {
    int n = arr.size();
    int posCount = 0;
    int negCount = 0;

    for(int i = 0; i < n; i++) {
        if(arr[i] > 0) {
            posCount++;
        } else {
            negCount++;
        }
    }

    int mini = min(posCount , negCount);

    vector<int> result;
    result.resize(n);
    int positiveIndex = 0;
    int negativeIndex = 1;

    for(int i = 0; i < 2*mini; i++) {
        if(arr[i] > 0) {
            result[positiveIndex] = arr[i];
            positiveIndex += 2;
        } else {
            result[negativeIndex] = arr[i];
            negativeIndex += 2;
        }  
    }
    int k = 2 * mini;
    while(k < n) {
        result[k] = arr[k];
        k++;
    }
    return result;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> result = rearrangeArrayBySign(arr);
    
    for(int x : result) {
        cout << x << " ";
    }
    return 0;
}


