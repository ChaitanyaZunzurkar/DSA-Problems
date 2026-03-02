#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /*
        INTUITION (DFS based Topological Sort):
        -------------------------------------
        In a Directed Acyclic Graph (DAG), a node should appear
        AFTER all the nodes it depends on.

        Using DFS:
        - Visit a node
        - Recursively visit all its neighbors
        - Once all neighbors are processed, push the node into a stack

        Why stack?
        ----------
        Because the last finished node should come first in topo order.
    */

    void dfs(int node, vector<vector<int>>& adj, vector<int>& vis, stack<int>& st) {
        // Mark current node as visited
        vis[node] = 1;

        // Visit all adjacent nodes
        for (auto &it : adj[node]) {
            if (!vis[it]) {
                dfs(it, adj, vis, st);
            }
        }

        // Push node AFTER visiting all its neighbors
        // This ensures correct topological order
        st.push(node);
    }

public:
    vector<int> topoSort(int V, vector<vector<int>>& edges) {

        /*
            edges[i] = {u, v} means there is a directed edge u -> v
            V = number of vertices
        */

        vector<vector<int>> adj(V);  // adjacency list
        vector<int> vis(V, 0);       // visited array
        stack<int> st;               // stack to store topo order

        // Build adjacency list from edges
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            adj[u].push_back(v);
        }

        // Call DFS for all components (important for disconnected graph)
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, adj, vis, st);
            }
        }

        // Pop elements from stack to get topo order
        vector<int> result;
        while (!st.empty()) {
            result.push_back(st.top());
            st.pop();
        }

        return result;
    }
};

int main() {
    /*
        INPUT FORMAT:
        -------------
        Enter number of vertices (V)
        Enter number of edges (E)
        Then E lines follow, each containing:
        u v  (directed edge from u to v)

        Example:
        --------
        Input:
        6
        6
        5 2
        5 0
        4 0
        4 1
        2 3
        3 1
    */

    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> edges(E, vector<int>(2));

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i][0] >> edges[i][1];
    }

    Solution obj;
    vector<int> topo = obj.topoSort(V, edges);

    cout << "Topological Sort Order:\n";
    for (int x : topo) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}