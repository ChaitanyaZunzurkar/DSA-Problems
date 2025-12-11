#include <bits/stdc++.h>
using namespace std;

/*
INTUITION:
---------
Each child has a greed value g[i].
Each cookie has a size s[j].

A child is satisfied ONLY IF:
        cookie_size >= child_greed

To maximize the number of satisfied children:
1. Sort both arrays.
2. Use the smallest cookie that can satisfy the smallest greed child.
   - If cookie ≥ greed → child is satisfied → move to next child.
   - Else → cookie is too small → try next cookie.

This greedy strategy works because:
- Using small cookies for children with small greed saves large cookies for later.
- We never waste a cookie that could satisfy a future child.
*/

int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end()); // smallest greed first
    sort(s.begin(), s.end()); // smallest cookie first

    int i = 0; // child pointer
    int j = 0; // cookie pointer
    int n1 = g.size();
    int n2 = s.size();

    while (i < n1 && j < n2) {
        if (g[i] <= s[j]) {
            // Cookie satisfies this child
            i++; 
        }
        // Move to next cookie no matter what
        j++;
    }

    return i; // number of satisfied children
}

int main() {
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nChildren;
    cout << "Enter number of children: ";
    cin >> nChildren;

    vector<int> g(nChildren);
    cout << "Enter greed values of children:\n";
    for (int i = 0; i < nChildren; i++)
        cin >> g[i];

    int nCookies;
    cout << "Enter number of cookies: ";
    cin >> nCookies;

    vector<int> s(nCookies);
    cout << "Enter sizes of cookies:\n";
    for (int i = 0; i < nCookies; i++)
        cin >> s[i];

    int ans = findContentChildren(g, s);

    cout << "Maximum number of satisfied children = " << ans << "\n";

    return 0;
}
