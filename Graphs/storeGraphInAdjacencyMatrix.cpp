#include <bits/stdc++.h>
using namespace std;

int main()
{
    int no_Of_Vertex, no_of_edges;
    cin >> no_Of_Vertex >> no_of_edges;

    // V x V adjacency matrix
    vector<vector<int>> adjacencyMatrix(
        no_Of_Vertex + 1, vector<int>(no_Of_Vertex + 1, 0)
    );

    for(int i = 0; i < no_of_edges; i++) {
        int u, v;
        cin >> u >> v;

        adjacencyMatrix[u][v] = 1;
        adjacencyMatrix[v][u] = 1; // undirected
    }

    // printing adjacency matrix
    for(int i = 1; i <= no_Of_Vertex; i++) {
        for(int j = 1; j <= no_Of_Vertex; j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
