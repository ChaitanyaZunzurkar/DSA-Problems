#include <bits/stdc++.h>
using namespace std;

/*
    INTUITION (Brute Force Approach):

    - You can start picking fruits from ANY index i (left boundary of the window).
    - From that index, you extend forward (j = i → n-1) and keep adding fruits.
    - You are allowed ONLY TWO types of fruits in your baskets.
    - So we keep a set<int> to track which fruit types appear in the current window [i..j].

    - For every starting point i:
          Try extending j step by step:
              - Insert fruits[j] into the set.
              - If the set size <= 2 → still valid, update maximum window length.
              - If the set size becomes > 2 → break, because we cannot pick more fruits.

    - This tries ALL possible subarrays and picks the longest one
      that contains ≤ 2 distinct fruit types.

    - TIME COMPLEXITY: O(n^2)
      (because for each i, you may scan until the end)
*/

int totalFruit_brute(const vector<int>& fruits) {
    int n = fruits.size();
    int maxi = 0;

    for (int i = 0; i < n; ++i) {
        set<int> st;  // stores the distinct fruit types in current window

        for (int j = i; j < n; ++j) {
            st.insert(fruits[j]);   // add current fruit type

            if (st.size() <= 2) {
                // valid window, update maximum
                maxi = max(maxi, j - i + 1);
            } else {
                // more than 2 fruit types → cannot extend this window further
                break;
            }
        }
    }
    return maxi;
}

int totalFruit_better(vector<int>& fruits) { 
    int n = fruits.size();
    int maxi = 0;
    int l = 0;
    int r = 0;
    
    unordered_map<int , int> ump;

    while(r < n) {

        // expand window by including current fruit
        ump[fruits[r]]++;

        // if window has more than 2 types → invalid
        if(ump.size() > 2) {

            // reduce count of leftmost fruit
            ump[fruits[l]]--;

            // remove completely if count becomes zero
            if(ump[fruits[l]] == 0) {
                ump.erase(fruits[l]);
            }

            // shrink window until we again have at most 2 fruit types
            while(l < r && ump.size() > 2) {
                l++;
            }
        }

        // valid window → update answer
        if(ump.size() <= 2) {
            maxi = max(maxi , r - l + 1);
        }

        r++; // expand window
    }
    
    return maxi;
}

int totalFruit_optimal(vector<int>& fruits) { 
    int n = fruits.size();
    int maxi = 0;
    int l = 0;
    int r = 0;
    
    // map will store: fruitType → count of that fruit in the current window
    unordered_map<int , int> ump;

    // sliding window from l to r
    while(r < n) {

        // include current fruit into basket/window
        ump[fruits[r]]++;

        // if more than 2 types → window becomes invalid
        if(ump.size() > 2) {

            // start shrinking from left until window becomes valid again
            ump[fruits[l]]--;

            // if any fruit count becomes zero → completely remove that fruit type
            if(ump[fruits[l]] == 0) {
                ump.erase(fruits[l]);
            }

            l++; // shrink the window
        }

        // when the window has at most 2 fruit types → valid window
        if(ump.size() <= 2) {
            // update maximum length
            maxi = max(maxi , r - l + 1);
        }

        r++; // expand window to the right
    }
    
    return maxi;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;                             // number of fruits

    vector<int> fruits(n);
    for (int i = 0; i < n; ++i) {
        cin >> fruits[i];                 // input fruit types
    }

    cout << totalFruit_optimal(fruits) << "\n";
    return 0;
}
