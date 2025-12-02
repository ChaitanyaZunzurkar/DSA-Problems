#include <iostream>
#include <string>
#include <climits>
#include <vector>
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

// Intuition of the optimal approach (Sliding Window + Hash array):
// ---------------------------------------------------------------
// Instead of checking every substring like brute force,
// we keep a window [l, r] that always remains VALID
//     (meaning all characters inside it are unique)
//
// We expand 'r' every step and include s[r] in the window.
// If we see a repeating character:
//     - We know the last index where it appeared using hsh[].
//     - If that index is inside our current window (>= l),
//       then the window becomes invalid.
//       So we MOVE 'l' to just after the last repeated character.
//       This removes the repetition.
//
// At each step, the window [l, r] is valid → compute its length.
// No element is visited more than 2 times (once by r, once by l),
// making time complexity O(n).

int lengthOfLongestSubstring_optimal(string s) {
    int n = s.size();
    int maxi = 0;
    int length = 0;
    int l = 0;
    int r = 0;

    // hsh[c] = last index where character 'c' appeared.
    // initialized to -1 (means character not seen yet)
    vector<int> hsh(256 , -1);

    while (r < n) {

        // If character s[r] was seen before AND
        // its last occurrence is inside the current window
        if(hsh[s[r]] != -1) {
            if(hsh[s[r]] >= l) {
                // Shift the left pointer to make window valid again
                l = hsh[s[r]] + 1;
            }
        }

        // Window [l, r] is now valid → update length
        length = r - l + 1;
        maxi = max(length , maxi);

        // Update last seen index of this character
        hsh[s[r]] = r;

        r++;
    }

    return maxi;
}

int main() {
    string s;

    cout << "Enter a string: ";
    getline(cin, s);

    int ans = lengthOfLongestSubstring_optimal(s);

    cout << "Length of longest substring without repeating characters: " << ans << endl;

    return 0;
}
