#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(string s, int k) {

        /*
        INTUITION OVERVIEW:
        ------------------
        Let:
        n = length of string
        m = number of '0's in the string

        Observation:
        - Each operation selects exactly k characters
        - Some of them are '0', some '1'
        - Flipping a '0' → '1' decreases zero count by 1
        - Flipping a '1' → '0' increases zero count by 1

        So after an operation:
        new_zero_count = m + (k - 2 * c)
        where c = number of '0's chosen in the operation

        This becomes a graph problem:
        - Each node = possible number of zeros (0 to n)
        - Edge between m → m2 if m2 is reachable in one operation
        - We want minimum operations to reach zero zeros (m = 0)
        - Use BFS since all edges have equal weight (1 operation)
        */

        int n = s.size();
        int m = 0;  // count of '0'

        for (char c : s) {
            if (c == '0') m++;
        }

        // dist[x] = minimum operations needed to reach x zeros
        vector<int> dist(n + 1, INT_MAX);

        /*
        We divide nodes by parity (even / odd)
        Because transitions always preserve parity:
        m2 = m + k - 2*c  => parity of m2 == parity of m
        */
        vector<set<int>> nodeSets(2);

        for (int i = 0; i <= n; i++) {
            nodeSets[i % 2].insert(i);
        }

        queue<int> q;
        q.push(m);
        dist[m] = 0;
        nodeSets[m % 2].erase(m);

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            /*
            c must satisfy:
            - c <= cur        (can't pick more 0s than exist)
            - k - c <= n-cur  (can't pick more 1s than exist)
            */

            int c1 = max(k - n + cur, 0);  // minimum c
            int c2 = min(cur, k);          // maximum c

            // range of reachable nodes
            int lnode = cur + k - 2 * c2;
            int rnode = cur + k - 2 * c1;

            auto &nodeSet = nodeSets[lnode % 2];

            // Visit all reachable nodes in range
            for (auto it = nodeSet.lower_bound(lnode);
                 it != nodeSet.end() && *it <= rnode;) {

                int nxt = *it;
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);

                it = next(it);
                nodeSet.erase(nxt); // mark visited
            }
        }

        // If zero zeros is unreachable
        return dist[0] == INT_MAX ? -1 : dist[0];
    }
};

int main() {
    string s;
    int k;

    cout << "Enter binary string: ";
    cin >> s;

    cout << "Enter k: ";
    cin >> k;

    Solution sol;
    int result = sol.minOperations(s, k);

    cout << "Minimum operations: " << result << endl;
    return 0;
}