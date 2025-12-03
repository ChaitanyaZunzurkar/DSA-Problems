#include <bits/stdc++.h>
using namespace std;

/*
 Brute-force solution (O(n^2)):
 For every starting index i, expand j from i..n-1,
 maintain a frequency array `hsh` for s[i..j],
 keep track of maxFreq (most frequent character in the window).
 Required replacements = window_length - maxFreq.
 If required <= k, window is valid.

 This is easy to understand and good for learning,
 but too slow for very large strings (n up to 1e5).
*/
int characterReplacementBrute(const string &s, int k) {
    int n = (int)s.size();
    int maxi = 0;

    for (int i = 0; i < n; ++i) {
        vector<int> hsh(26, 0);
        int maxFreq = 0;
        for (int j = i; j < n; ++j) {
            int idx = s[j] - 'A';      // assume uppercase letters
            if (idx < 0 || idx >= 26) continue; // skip unexpected characters safely
            hsh[idx]++;                // include s[j]
            maxFreq = max(maxFreq, hsh[idx]);

            int len = j - i + 1;
            int changes = len - maxFreq; // how many chars to replace
            if (changes <= k) {
                maxi = max(maxi, len);
            }
            // do NOT break here: a future j might increase maxFreq and make a longer substring valid
        }
    }
    return maxi;
}

/*
 Optimal sliding-window solution (O(n), O(1) extra space):
 Maintain a window [l..r], a frequency array `count`, and maxCount = max frequency inside current window.
 If (window_size - maxCount) > k, shrink from left until valid.
 Note: we never recompute maxCount on shrinking (it may become stale), but algorithm remains correct
 and runs in linear time.
*/
int characterReplacement_better(const string &s, int k) {
    int n = (int)s.size();
    vector<int> count(26, 0);
    int l = 0, maxCount = 0, ans = 0;

    for (int r = 0; r < n; ++r) {
        int idx = s[r] - 'A';
        if (0 <= idx && idx < 26) {
            count[idx]++;
            maxCount = max(maxCount, count[idx]);
        } else {
            // If string may contain non-uppercase characters, you could handle them differently.
            // For this implementation we simply ignore (do not count) unexpected characters.
        }

        // If we need more than k replacements, shrink from left
        while ((r - l + 1) - maxCount > k) {
            int leftIdx = s[l] - 'A';
            if (0 <= leftIdx && leftIdx < 26) {
                count[leftIdx]--;
            }
            l++;
            // Do not recompute maxCount here for speed.
        }

        ans = max(ans, r - l + 1);
    }

    return ans;
}

int characterReplacement_optimal(string s, int k) { 
    
    int n = s.size();
    int maxi = 0;
    int l = 0;           // left pointer of sliding window
    int r = 0;           // right pointer

    int maxFreq = 0;     // stores frequency of the MOST frequent char in current window
    vector<int> hsh(26); // frequency array for characters in window

    while (r < n) {

        // include s[r] into the window and update its frequency
        hsh[s[r] - 'A']++;

        // update maxFreq because a new char count may become the highest
        maxFreq = max(maxFreq, hsh[s[r] - 'A']);

        // calculate how many characters we need to change
        // to make the entire window contain one single repeating character
        //
        // window_size = (r - l + 1)
        // maxFreq = freq of the char that appears the MOST
        //
        // so remaining = window_size - maxFreq (these need to be replaced)
        int changes = (r - l + 1) - maxFreq;

        // If changes > k, we are using more replacements than allowed.
        // So shrink the window from the left.
        if (changes > k) {
            hsh[s[l] - 'A']--;  // remove the effect of s[l]
            l++;                // move left pointer forward
        }

        // update the maximum valid window size found so far
        maxi = max(maxi, r - l + 1);

        // expand the window from the right
        r++;
    }

    return maxi;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Enter the string s (uppercase letters recommended):\n";
    string s;
    // Read a full line for the string (handles spaces if any)
    if (!std::getline(cin, s)) return 0;

    // If the user pressed Enter without typing the string (empty line),
    // try reading a token (handles interactive inputs where newline remains)
    if (s.size() == 0) {
        if (!(cin >> s)) return 0;
        // consume the leftover newline before reading k
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter k (max replacements):\n";
    int k;
    if (!(cin >> k)) {
        cerr << "Invalid input for k.\n";
        return 0;
    }

    int result_opt  = characterReplacement_optimal(s, k);
    cout << "Optimal (sliding)    = " << result_opt  << "\n";

    return 0;
}
