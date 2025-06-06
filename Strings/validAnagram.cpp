// Time complexcity :- O(n log n)

// #include <bits/stdc++.h>
// using namespace std;

// int main()
// {
//     string s , t;
//     cin >> s >> t;

//     sort(s.begin() , s.end());
//     sort(t.begin() , t.end());

//     if(s == t) {
//         cout << true << endl;
//     } else {
//         cout << false << endl;
//     }
//     return 0;
// }



// Time complexcity :- O(n)
#include <bits/stdc++.h>
using namespace std;

bool isValidAnagram(string &s , string &t) {
    if(s.length() != t.length()) {
        return false;
    }

    vector<int> shash(26 , 0);
    vector<int> thash(26 , 0);

    for(int i = 0; i < s.length(); i++) {
        shash[s[i] - 'a']++;
        thash[t[i] - 'a']++;
    }

    for(int i = 0; i < s.length(); i++) {
        if(shash[i] != thash[i]) {
            return false;
        }
    }

    return true;
}

int main()
{
    string s , t;
    cin >> s >> t;

    cout << isValidAnagram(s , t);
    return 0;
}