#include <bits/stdc++.h>
using namespace std;

class Solution {
private:

    /*
    DFS Intuition:
    We start from one node and keep visiting all reachable neighbours.
    Because in a connected component, every node is reachable from any other node.

    So this DFS call will collect ONE FULL COMPONENT.
    */
    void dfs(int node, vector<int> &visited, vector<vector<int>> &adjList, vector<int> &component) {
        visited[node] = 1;              // mark current node visited
        component.push_back(node);      // add node to current component
        
        // visit all neighbours
        for(auto &nbr : adjList[node]) {
            if(!visited[nbr]) {
                dfs(nbr , visited , adjList , component);
            }
        }
    }
    
public:

    /*
    edges is an EDGE LIST:
    edges = { {u,v}, {u,v}, {u,v} }

    We first convert it into adjacency list because DFS works best on adjacency list.
    */
    vector<vector<int>> getComponents(int V, vector<vector<int>>& edges) {

        vector<vector<int>> components;
        vector<int> visited(V , 0);
        vector<vector<int>> adjList(V);

        // Step 1: Build graph (undirected)
        for(auto &e : edges) {
            int u = e[0];
            int v = e[1];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        // Step 2: Run DFS from every unvisited node
        for(int i = 0; i < V; i++) {
            if(!visited[i]) {
                vector<int> component;

                // This DFS call finds one entire component
                dfs(i , visited , adjList , component);

                components.push_back(component);
            }
        }

        return components;
    }
};

int main() {

    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> edges(E, vector<int>(2));

    cout << "Enter edges (u v):\n";
    for(int i = 0; i < E; i++) {
        cin >> edges[i][0] >> edges[i][1];
    }

    Solution obj;
    vector<vector<int>> result = obj.getComponents(V, edges);

    cout << "\nConnected Components:\n";
    for(auto &comp : result) {
        for(int node : comp)
            cout << node << " ";
        cout << endl;
    }

    return 0;
}
