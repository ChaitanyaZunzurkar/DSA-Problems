// time complexcity :- O(n)
// space complexcity :- O(1)

#include <bits/stdc++.h>
using namespace std;

vector<int> moveAllZerosToEnd(vector<int> arr) {
    int n = arr.size();
    int j = 0;
        
    for(int i = 0;i < n; i++) {
        if(arr[i] != 0) {
            swap(arr[j] ,arr[i]);
            j++;
        }
    }
    return arr;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> result = moveAllZerosToEnd(arr);
    for(int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    return 0;
}



// time complexcity :- O(n)
// space comoplexcity :- O(1)

// #include <bits/stdc++.h>
// using namespace std;

// vector<int> moveAllZerosToEnd(vector<int> arr) {
//     int n = arr.size();
//     int count = 0;

//     for(int i = 0; i < n; i++) {
//         if(arr[i] != 0) {
//             arr[count++] = arr[i];
//         }
//     }

//     while (count < n) {
//         arr[count++] = 0;
//     }
//     return arr;
// }

// int main()
// {
//     int n;
//     cin >> n;
//     vector<int> arr(n);
//     for(int i = 0; i < n; i++) {
//         cin >> arr[i];
//     }

//     vector<int> result = moveAllZerosToEnd(arr);
//     for(int i = 0; i < result.size(); i++) {
//         cout << result[i] << " ";
//     }
//     return 0;
// }




// time Complexcity :- O(n)
// space cmoplexcity :- O(n)

// #include <bits/stdc++.h>
// using namespace std;

// vector<int> moveAllZerosToEnd(vector<int> arr) {
//     int n = arr.size();
//     vector<int> temp(n);
//     int count = 0;
    
//     for(int i = 0; i < n; i++){
//         if(arr[i] != 0) {
//             temp[count++] = arr[i];
//         }
//     }

//     while(count < n) {
//         temp[count++] = 0;
//     }

//     for(int i = 0; i < n; i++) {
//         arr[i] = temp[i];
//     }

//     return arr;
// }

// int main()
// {
//     int n;
//     cin >> n;
//     vector<int> arr(n);
//     for(int i = 0; i < n; i++) {
//         cin >> arr[i];
//     }

//     vector<int> result = moveAllZerosToEnd(arr);
//     for(int i = 0; i < result.size(); i++) {
//         cout << result[i] << " ";
//     }
//     return 0;
// }