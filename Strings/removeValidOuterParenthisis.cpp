#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;

    string result;
    int balance = 0;

    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') {
            if(balance > 0) {
                result += s[i];
            }
            balance++;
        } else {
            balance--;
            if(balance > 0) {
                result += s[i];
            }
        }
    }

    cout << result << endl;
    return 0;
}