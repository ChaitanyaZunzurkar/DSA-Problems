#include <bits/stdc++.h>
using namespace std;

int main()
{
    int no_Of_Vertex , no_of_edges;
    cin >> no_Of_Vertex >> no_of_edges;

    vector<vector<int>> adjacencyMatrix(no_Of_Vertex + 1 , vector<int>(no_Of_Vertex + 1));
    for(int i = 0; i < no_of_edges; i++)  {
        // u ------> v && u <------v 
        int u , v;
        cin >> u >> v;

        adjacencyMatrix[u][v] = 1;
        adjacencyMatrix[v][u] = 1;
    }

    // printing the adjacencey matrix 
    for(int i = 0; i < no_Of_Vertex; i++) {
        for(int j = 0; j < no_Of_Vertex; j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}