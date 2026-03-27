#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int n = g.size();
        int m = s.size();

        sort(g.begin(), g.end());  // greed factors
        sort(s.begin(), s.end());  // cookie sizes

        /*
        INTUITION:

        - We want to satisfy maximum number of children.
        - Each child has a greed factor g[i]
        - Each cookie has size s[j]

        GREEDY IDEA:
        - Always try to satisfy the least greedy child first.
        - Give the smallest possible cookie that can satisfy that child.

        WHY?
        - If we waste a big cookie on a small greed child,
          we might not be able to satisfy a more greedy child later.

        APPROACH:
        - Sort both arrays.
        - Use two pointers:
            i -> child
            j -> cookie
        - If cookie >= greed → assign it and move both
        - Else → try next bigger cookie
        */

        int i = 0; // pointer for children
        int j = 0; // pointer for cookies

        while(i < n && j < m) {
            if(s[j] >= g[i]) {
                i++; // child satisfied
            }
            j++; // move to next cookie
        }

        return i; // number of satisfied children
    }
};

int main() {
    int n, m;

    // input size of greed array
    cout << "Enter number of children: ";
    cin >> n;

    vector<int> g(n);
    cout << "Enter greed factors: ";
    for(int i = 0; i < n; i++) cin >> g[i];

    // input size of cookies array
    cout << "Enter number of cookies: ";
    cin >> m;

    vector<int> s(m);
    cout << "Enter cookie sizes: ";
    for(int i = 0; i < m; i++) cin >> s[i];

    Solution obj;
    int ans = obj.findContentChildren(g, s);

    cout << "Maximum content children: " << ans << endl;

    return 0;
}