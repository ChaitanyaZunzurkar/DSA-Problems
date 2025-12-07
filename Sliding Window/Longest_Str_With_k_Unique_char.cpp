#include <bits/stdc++.h>
using namespace std;

/*
   Function: longestKSubstr_brute
   Intuition:
   → We want the longest substring that has exactly K distinct characters.
   → For every starting index i, we expand the substring to the right.
   → We maintain a set to track distinct characters.
   → If at any moment the set size equals K, update the answer.
   → This is brute force O(n²) because we try each starting index.
*/
int longestKSubstr_brute(string &s, int k) {
    int n = s.size();
    int maxi = -1;

    for (int i = 0; i < n; i++) {
        set<char> st; // keeps unique characters in current substring

        for (int j = i; j < n; j++) {
            st.insert(s[j]); // add new character

            // If number of distinct characters becomes exactly k,
            // we update maximum length.
            if (st.size() == k) {
                maxi = max(maxi, j - i + 1);
            }
        }
    }

    return maxi;
}

/*
    Intuition (Sliding Window Approach):

    → Maintain a window [l, r] and a map to count character frequencies.
    → Expand window by moving r and inserting s[r] into the map.
    → If number of distinct characters exceeds k,
        shrink window from left (move l forward) while reducing character counts.
        erase a character from map when its count becomes zero.
    → Whenever the map has exactly k distinct characters,
        update maxi with current window size.
    → If no window ever reaches k distinct characters, return -1.
*/

int longestKSubstr_optimal(string &s, int k) {
    int n = s.size();
    int maxi = -1;
    int l = 0; 
    int r = 0;
    
    map<char , int> mp;

    while(r < n) {
        mp[s[r]]++;  // include current character into window
        
        // shrink window if distinct characters > k
        if(mp.size() > k) {
            while(mp.size() > k) {
                mp[s[l]]--;
                if(mp[s[l]] == 0) mp.erase(s[l]); // erase if freq becomes zero
                l++; // shrink from left
            }
        }
        
        // update max length if window has exactly k distinct characters
        if(mp.size() == k) {
            maxi = max(maxi , r - l + 1);
        }

        r++; // expand window to right
    }
    
    return maxi;
}


int main() {
    string s;
    int k;

    cout << "Enter string: ";
    cin >> s;

    cout << "Enter value of k: ";
    cin >> k;

    int result = longestKSubstr_optimal(s, k);

    cout << "Longest substring length with "
         << k << " distinct characters: " << result << endl;

    return 0;
}
