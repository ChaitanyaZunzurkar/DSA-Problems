#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
INTUITION (VERY IMPORTANT — READ THIS FIRST)

We are solving the "Course Schedule" problem.

- Each course is a NODE
- Each prerequisite is a DIRECTED EDGE

If there is a CYCLE in the directed graph,
→ you can NEVER finish all courses.

So the problem becomes:
👉 Detect a cycle in a directed graph

We use:
- DFS (Depth First Search)
- visited[]  → to mark nodes visited at least once
- path[]     → to track nodes in the current DFS recursion stack

If during DFS:
- we reach a node that is already in the current path[],
→ a cycle exists
===========================================================
*/

class Solution {
private:
    /*
    dfs(node) returns:
    - true  → if a cycle is found
    - false → if no cycle from this node
    */
    bool dfs(int node,
             vector<int> &vis,
             vector<int> &path,
             vector<vector<int>> &adj) {

        // Mark current node as visited
        vis[node] = 1;

        // Mark current node as part of current DFS path
        path[node] = 1;

        // Explore all neighbors of this node
        for (int next : adj[node]) {

            // If neighbor is not visited, explore it
            if (!vis[next]) {
                if (dfs(next, vis, path, adj))
                    return true;   // cycle found below
            }
            // If neighbor is visited AND still in recursion stack
            else if (path[next]) {
                return true;      // cycle detected
            }
        }

        // Remove node from current DFS path before backtracking
        path[node] = 0;
        return false;             // no cycle from this node
    }

public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {

        /*
        Build adjacency list

        prerequisite [a, b] means:
        to take course 'a', you must complete course 'b' first

        Edge direction:
        b → a
        */
        vector<vector<int>> adj(numCourses);
        for (auto &p : prerequisites) {
            adj[p[1]].push_back(p[0]);
        }

        vector<int> vis(numCourses, 0);   // visited array
        vector<int> path(numCourses, 0);  // recursion stack

        // Run DFS from every unvisited node
        for (int i = 0; i < numCourses; i++) {
            if (!vis[i]) {
                if (dfs(i, vis, path, adj))
                    return false;   // cycle found → cannot finish
            }
        }

        return true; // no cycle → can finish all courses
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /*
    INPUT FORMAT (USER INPUT)

    numCourses
    number_of_prerequisites
    a b   (meaning: to take course a, you must take b first)

    Example:
    4
    3
    1 0
    2 1
    3 2
    */

    int numCourses;
    cin >> numCourses;

    int m; // number of prerequisite pairs
    cin >> m;

    vector<vector<int>> prerequisites;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        prerequisites.push_back({a, b});
    }

    Solution sol;
    bool result = sol.canFinish(numCourses, prerequisites);

    if (result)
        cout << "YES, all courses can be finished\n";
    else
        cout << "NO, it is not possible to finish all courses (cycle exists)\n";

    return 0;
}