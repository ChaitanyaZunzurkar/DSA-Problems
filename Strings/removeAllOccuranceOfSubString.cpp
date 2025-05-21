#include <bits/stdc++.h>
using namespace std;

string removeOccurrences(string s, string part){
    int n = s.length();
    int m = part.length();

    int start = 0;
    while (n > 0 && s.find(part) < n) {
        start = s.find(part);
        s.erase(start, m);
    }
    return s;
}

int main(){
    string s;
    getline(cin, s);

    string part;
    getline(cin, part);

    cout << removeOccurrences(s , part) << endl;
    return 0;
}
