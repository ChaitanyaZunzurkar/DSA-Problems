#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(string s) {
    string str;

    for(int i = 0; i < s.length(); i++) {
        if((s[i] > 64 && s[i] < 91) || (s[i] > 96 && s[i] < 123) || (s[i] >= 48 && s[i] < 58))
            str += tolower(s[i]);
    }

    string cpstr = str;
    reverse(cpstr.begin() , cpstr.end());

    if(cpstr == str) {
        return true;
    }
    return false;
}

int main() {
    string s;
    getline(cin , s);

    if(isPalindrome(s)) {
        cout << true << endl;
    }
    else {
        cout << false << endl;
    }
    return 0;
}
