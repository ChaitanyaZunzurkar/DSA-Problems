#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s , t;
    cin >> s >> t;

    unordered_map<char , int> smap;
    unordered_map<char , int> tmap;

    bool flag = 1;
    for(int i = 0; i < s.length(); i++) {
        if(smap.find(s[i]) != smap.end()) {
            smap[s[i]] = i;
        }

        if(tmap.find(t[i]) != tmap.end()) {
            tmap[t[i]] = i;
        }

        if(smap[s[i]] != tmap[t[i]]) {
            flag = 0;
            break;
        }
    }

    if (flag == 0) {
        cout << false << endl;
    } else {
        cout << true << endl;
    }
    return 0;
}