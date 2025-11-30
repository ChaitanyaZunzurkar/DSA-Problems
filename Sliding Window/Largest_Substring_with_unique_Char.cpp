#include <iostream>
#include <string>
#include <climits>
using namespace std;

// Intuition of the brute force approach:
// --------------------------------------
// We try ALL POSSIBLE substrings.
// For each starting index i:
//    - create an empty string 'str'
//    - keep adding characters one by one using j
//    - if the character is already in 'str', break
// This forces us to check every substring → O(n^3) in worst case.
// We store the maximum length found.

int lengthOfLongestSubstring_brute(string s) {
    int n = s.size();
    int maxi = INT_MIN;

    string str = "";
    int length = 0;

    for(int i = 0; i < n; i++) {
        str = "";
        length = 0;

        for(int j = i; j < n; j++) {

            // check if current character already exists in the substring
            if(str.find(s[j]) != string::npos) {   // 'contains' doesn't exist in C++
                break;
            }

            str += s[j];
            length++;
        }

        maxi = max(maxi, length);
    }

    maxi = max(length, maxi);
    return maxi;
}

int main() {
    string s;

    cout << "Enter a string: ";
    getline(cin, s);

    int ans = lengthOfLongestSubstring_brute(s);

    cout << "Length of longest substring without repeating characters: " << ans << endl;

    return 0;
}
