#include <iostream>
#include <vector>

using namespace std;

// Helper function for DFS
bool isCycleDFS(int node, int parent, vector<int>& visited, vector<vector<int>>& adj) {
    // 1. Mark the current node as visited
    visited[node] = 1;

    // 2. Iterate through all adjacent nodes
    for(int neighbour : adj[node]) {
        // Case A: If the neighbour has not been visited, recurse on it
        if(!visited[neighbour]) {
            // Pass 'node' as the new parent for the neighbour
            if (isCycleDFS(neighbour, node, visited, adj)) {
                return true;
            }
        } 
        // Case B: If the neighbour is visited, but it is NOT the parent
        // This means we found a back-edge to an ancestor -> CYCLE DETECTED
        else if(neighbour != parent) {
            return true;
        }
    }

    return false;
}

// Main function to solve the problem
bool checkForCycle(int V, vector<vector<int>>& edges) {
    vector<int> visited(V, 0);
    vector<vector<int>> adj(V);

    // 1. Convert Edge List to Adjacency List
    for(auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph: add edge both ways
    }

    // 2. Handle disconnected components
    // We must check every node in case the graph is split into parts
    for(int i = 0; i < V; i++) {
        if(!visited[i]) {
            // Start DFS from unvisited nodes with parent as -1 (no parent)
            if (isCycleDFS(i, -1, visited, adj)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    // Example 1: Graph with a cycle (0-1, 1-2, 2-0)
    int V = 3;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}};

    if(checkForCycle(V, edges)) {
        cout << "Graph 1: Cycle Detected? YES" << endl;
    } else {
        cout << "Graph 1: Cycle Detected? NO" << endl;
    }

    // Example 2: Linear graph (0-1, 1-2)
    int V2 = 3;
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}};

    if(checkForCycle(V2, edges2)) {
        cout << "Graph 2: Cycle Detected? YES" << endl;
    } else {
        cout << "Graph 2: Cycle Detected? NO" << endl;
    }

    return 0;
}