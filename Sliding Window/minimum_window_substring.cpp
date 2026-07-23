#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

class Solution {
public:

    /*
        solve() checks whether the current window contains
        all the characters required by string 't'.

        need[i] -> Frequency of character i required.
        have[i] -> Frequency of character i present in current window.

        If for any character:
            have < need
        then the current window is invalid.

        Time Complexity: O(128)
    */
    bool solve(vector<int> &need, vector<int> &have) {
        for(int i = 0; i < 128; i++) {
            if(need[i] > have[i]) {
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {

        int n = s.size();
        int m = t.size();

        // res = minimum window length found so far
        int res = INT_MAX;

        // starting index of the minimum window
        int start = -1;

        /*
            need[] stores frequency of every character
            required from string t.

            Example:
            t = "AABC"

            need['A'] = 2
            need['B'] = 1
            need['C'] = 1
        */
        vector<int> need(128, 0);

        /*
            have[] stores frequency of characters
            currently present inside the sliding window.
        */
        vector<int> have(128, 0);

        // Fill the frequency array of string t
        for(int i = 0; i < m; i++) {
            need[t[i]]++;
        }

        // left pointer of sliding window
        int low = 0;

        /*
            Expand the window using high pointer.
        */
        for(int high = 0; high < n; high++) {

            // Include current character into the window
            have[s[high]]++;

            /*
                If the current window already contains all
                required characters, try shrinking it.

                Our goal:
                Keep the window VALID while making it
                as small as possible.
            */
            while(solve(need, have)) {

                int len = high - low + 1;

                // Update minimum answer
                if(len < res) {
                    res = len;
                    start = low;
                }

                /*
                    Remove left character and move
                    left pointer forward.
                */
                have[s[low]]--;
                low++;
            }
        }

        // No valid window found
        if(start == -1)
            return "";

        return s.substr(start, res);
    }
};

int main() {

    string s, t;

    cout << "Enter string s: ";
    cin >> s;

    cout << "Enter string t: ";
    cin >> t;

    Solution obj;

    string ans = obj.minWindow(s, t);

    if(ans == "")
        cout << "No valid window exists.\n";
    else
        cout << "Minimum Window Substring = " << ans << endl;

    return 0;
}