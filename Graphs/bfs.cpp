#include <bits/stdc++.h>
using namespace std;

/*
    Function: bfsTraversal

    INTUITION:
    ----------
    Breadth First Search (BFS) explores a graph level by level.
    We start from a node, visit all its immediate neighbors first,
    then move to their neighbors, and so on.

    IMPORTANT IDEA:
    - The queue stores NODE INDICES, not data values.
    - Each number pushed into the queue represents a node of the graph.
    - Using a visited array prevents revisiting the same node.

    WHY WE LOOP OVER ALL NODES?
    ---------------------------
    Graph may be disconnected.
    So we start BFS from every unvisited node to cover all components.
*/

vector<int> bfsTraversal(vector<vector<int>> &adj, int V) {
    vector<int> visited(V, 0);   // visited[i] = 1 means node i is already visited
    vector<int> result;          // stores BFS traversal order
    queue<int> q;                // queue for BFS (stores node indices)

    // Loop over all nodes to handle disconnected graphs
    for(int start = 0; start < V; start++) {

        // If node is not visited, start BFS from it
        if(!visited[start]) {
            visited[start] = 1;
            q.push(start);   // push node index into queue

            while(!q.empty()) {
                int node = q.front();  // current node index
                q.pop();

                result.push_back(node);  // record BFS order

                // Traverse all neighbors of current node
                for(int neighbor : adj[node]) {
                    if(!visited[neighbor]) {
                        visited[neighbor] = 1; // mark visited before pushing
                        q.push(neighbor);      // push neighbor index
                    }
                }
            }
        }
    }
    return result;
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> adj(V);

    cout << "Enter edges (u v) one per line:\n";
    for(int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;

        // Undirected graph
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> bfs = bfsTraversal(adj, V);

    cout << "BFS Traversal: ";
    for(int node : bfs) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
