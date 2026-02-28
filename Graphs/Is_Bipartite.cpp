#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /*
        dfs(node, col):

        Intuition:
        - We try to put the current node into a "group" represented by color `col`
        - col = 0  → Group A
        - col = 1  → Group B

        Rule of bipartite graph:
        - Every edge must connect nodes of DIFFERENT groups

        What DFS does:
        1. Color the current node
        2. Visit all its neighbors
        3. If a neighbor is uncolored, give it the opposite color and continue DFS
        4. If a neighbor already has the SAME color → conflict → NOT bipartite
    */
    bool dfs(int node, int col, vector<int> &color, vector<vector<int>> &graph) {
        // Assign color to current node
        color[node] = col;

        // Visit all adjacent nodes
        for (auto &neighbor : graph[node]) {

            // If neighbor is not colored yet
            if (color[neighbor] == -1) {
                // Assign opposite color and continue DFS
                if (!dfs(neighbor, !col, color, graph))
                    return false;
            }
            // If neighbor already has SAME color → violation
            else if (color[neighbor] == col) {
                return false;
            }
        }
        return true;
    }

public:
    /*
        isBipartite():

        Intuition:
        - Graph can be DISCONNECTED
        - So we must check EACH connected component
        - Start DFS from every unvisited node

        If ANY component is not bipartite → answer is false
    */
    bool isBipartite(vector<vector<int>> &graph) {
        int n = graph.size();
        vector<int> color(n, -1); // -1 = uncolored

        // Check all components
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                if (!dfs(i, 0, color, graph))
                    return false;
            }
        }
        return true;
    }
};

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    vector<vector<int>> graph(n);

    /*
        Input format:
        For each node i:
        - Enter number of neighbors
        - Then enter the neighbors

        Example:
        Node 0 has neighbors 1 and 3
        Input:
        2 1 3
    */
    for (int i = 0; i < n; i++) {
        int k;
        cout << "Enter number of neighbors of node " << i << ": ";
        cin >> k;

        cout << "Enter neighbors of node " << i << ": ";
        for (int j = 0; j < k; j++) {
            int v;
            cin >> v;
            graph[i].push_back(v);
        }
    }

    Solution sol;
    bool result = sol.isBipartite(graph);

    if (result)
        cout << "Graph is Bipartite\n";
    else
        cout << "Graph is NOT Bipartite\n";

    return 0;
}