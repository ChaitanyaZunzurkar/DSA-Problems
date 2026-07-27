#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:

    // Compare the frequency arrays.
    // If they are identical, then the current window
    // is a permutation of s1.
    bool solve(const vector<int>& need, const vector<int>& have) {
        for (int i = 0; i < 128; i++) {
            if (need[i] != have[i])
                return false;
        }
        return true;
    }

    bool checkInclusion(string s1, string s2) {

        int n = s1.size();
        int m = s2.size();

        // If s1 is longer than s2,
        // permutation is impossible.
        if (n > m)
            return false;

        // need -> frequency of characters in s1
        // have -> frequency of current sliding window
        vector<int> need(128, 0), have(128, 0);

        // Store frequencies of s1
        for (char ch : s1)
            need[ch]++;

        int low = 0;

        // Expand the window
        for (int high = 0; high < m; high++) {

            // Include current character
            have[s2[high]]++;

            // Maintain a fixed window of size n
            while ((high - low + 1) > n) {
                have[s2[low]]--;
                low++;
            }

            // If both frequency arrays are equal,
            // the current window is a permutation of s1.
            if (solve(need, have))
                return true;
        }

        return false;
    }
};

int main() {

    Solution obj;

    string s1 = "ab";
    string s2 = "eidbaooo";

    if (obj.checkInclusion(s1, s2))
        cout << "True\n";
    else
        cout << "False\n";

    return 0;
}