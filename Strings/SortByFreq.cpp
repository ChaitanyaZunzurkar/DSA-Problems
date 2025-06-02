#include <bits/stdc++.h>
using namespace std;

int main()
{
    string str;
    cin >> str;

    unordered_map<char , int> strHash;
    for(int i = 0; i < str.length(); i++) {
        strHash[str[i]]++;
    }

    vector<pair<char , int>> freqVector(strHash.begin() , strHash.end());
    sort(freqVector.begin() , freqVector.end() , [&](auto &a , auto &b) {
        return a.second > b.second;
    });

    string result;
    for(auto &ch : freqVector) {
        result += string(ch.second , ch.first);
    }

    cout << result << endl;
    return 0;
}