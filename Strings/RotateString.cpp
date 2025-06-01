#include <bits/stdc++.h>
using namespace std;\

bool rotateString(string s , string goal) {
    if(s.length() != goal.length()) return false;
    string str = s + s;
    return str.find(goal) != string::npos;
}

int main() {
    string s , goal;
    cin >> s >> goal;

    cout << rotateString(s , goal);
    return 0;
}