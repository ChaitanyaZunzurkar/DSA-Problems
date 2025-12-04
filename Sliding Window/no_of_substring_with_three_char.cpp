#include <bits/stdc++.h>
using namespace std;

/*
    INTUITION (brute-force):
    ------------------------
    We want to count all substrings that contain at least one 'a', one 'b' and one 'c'.

    Brute-force approach:
    - Fix a starting index i.
    - Build/extend the substring by moving j from i to n-1.
    - Maintain three boolean flags (hasA, hasB, hasC) as we extend.
    - Once all three flags are true, the current substring s[i..j] qualifies;
      continue extending j to count other substrings starting at i.
    - This examines every substring exactly once (nested loops), and checks
      membership incrementally (O(1) per extension).

    Complexity:
    - Time: O(n^2) in the worst case.
    - Space: O(1) extra.
*/

long long numberOfSubstrings_bruteforce(const string& s) {
    int n = s.size();
    long long count = 0;

    for (int i = 0; i < n; ++i) {
        bool hasA = false, hasB = false, hasC = false;
        for (int j = i; j < n; ++j) {
            char ch = s[j];
            if (ch == 'a') hasA = true;
            else if (ch == 'b') hasB = true;
            else if (ch == 'c') hasC = true;

            if (hasA && hasB && hasC) ++count;
        }
    }

    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!getline(cin, s)) return 0; // read the input string (whole line)

    cout << numberOfSubstrings_bruteforce(s) << '\n';
    return 0;
}
