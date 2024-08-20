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

    set<int> st;
    for(int i = 0; i < arr.size(); i++) {
        st.insert(arr[i]);
    }
    int i = 0;
    for(auto &val : st) {
        arr[i] = val;
        i++;
    }
    cout << st.size() << endl;
    return 0;
}