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

int numberOfSubstrings_brute(string s) {
    int n = s.size();
    string str = "";
    int no_str = 0;

    for(int i = 0; i < n; i++) {
        str = "";
        for(int j = i; j < n; j++) {
            str += s[j];

            if(str.contains('a') && str.contains('b') && str.contains('c')) {

                /*
                   INTUITION:

                   The moment substring s[i..j] becomes valid
                   (contains 'a', 'b', and 'c'),

                   → any longer substring starting at i
                     and ending at j, j+1, j+2, ..., n-1
                     will ALSO contain a, b, c.

                   Why?  
                   Because appending more characters never removes
                   the existing a, b, or c.

                   So instead of counting only 1 substring,
                   we directly count all remaining valid substrings:

                        (n - j)

                   Example:
                   If valid substring found ending at j = 4
                   and n = 10,
                   then all ending indices 4,5,6,7,8,9 are valid,
                   so we add (10 - 4) = 6.
                */

                no_str += (n - j);

                // break here is optional but saves time
                // because longer ones are already counted
                // break;
            }
        }
    }

    return no_str;
}


int numberOfSubstrings_optimal(string s) {
    int n = s.size();
    int count = 0;

    // lastseen[0] → last index where 'a' appeared
    // lastseen[1] → last index where 'b' appeared
    // lastseen[2] → last index where 'c' appeared
    // initialize as -1 meaning not seen yet
    vector<int> lastseen(3 , -1);

    for(int i = 0; i < n; i++) {

        // update last seen position of current character
        // s[i] - 'a' converts 'a','b','c' → 0,1,2
        lastseen[s[i] - 'a'] = i;

        /*
           IDEA:
           We want to count substrings ending at index i
           that contain at least one 'a', 'b', and 'c'.

           If all three characters have been seen,
           then whichever of them has the smallest last occurrence
           decides how far left we can start the substring.

           Example:
           last occurrences:
                a at index 5
                b at index 4
                c at index 2

           Minimum = 2
           Meaning: Any substring starting at index 0,1,2
           and ending at i will contain all 3 characters.

           So number of valid substrings ending at i is:
               (min index + 1)

           We keep adding that to total count.
        */

        count = count + (1 + min(lastseen[0], min(lastseen[1], lastseen[2])));
    }

    return count;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!getline(cin, s)) return 0; // read the input string (whole line)

    cout << numberOfSubstrings_optimal(s) << '\n';
    return 0;
}
