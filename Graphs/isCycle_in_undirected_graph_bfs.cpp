#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/* ================================================================================
   USER QUESTION & ANSWER (Logic Clarification)
   ================================================================================
   
   Question: 
   "In the 'else if' statement, we are not checking if the node is visited or not. 
    How are you identifying if it is visited?"

   Answer: 
   The check is hidden inside the structure of the if-else logic itself!
   
   1. The first line says: if (!visited[x]) 
      -> "Is this node NOT visited?"
      
   2. If that condition is FALSE (meaning the node IS visited), the code 
      automatically falls into the 'else if' block.
      
   So, simply by reaching the 'else if', we know for a fact that visited[x] is true.
   We don't need to write 'if (visited[x] == true)' because that is the only way 
   to reach that line.
   ================================================================================
*/

// Function to detect cycle in an undirected graph using BFS
bool isCycle(int V, vector<vector<int>>& edges) {
    // INTUITION: 
    // We need 'visited' to track where we've been so we don't process nodes forever.
    // We need 'adj' because the input gives us raw edges (pairs), but BFS needs
    // to know "who are my neighbors?" efficiently.
    vector<int> visited(V, 0);
    
    // FIX FROM PREVIOUS ERROR: 
    // We initialize adj with size V immediately. 
    // Creating an empty vector and trying to access adj[u] would crash.
    vector<vector<int>> adj(V);

    // Step 1: Build the Adjacency List
    // Convert raw edge list {{1,2}, {2,3}} into a graph structure:
    // 1 -> {2}
    // 2 -> {1, 3}
    // 3 -> {2}
    for(auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph: connection goes both ways
    }

    // Step 2: Handle Disconnected Components
    // The graph might be split into separate islands. We loop through 0 to V-1
    // to ensure we check every island.
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            
            // Start BFS for this component
            visited[i] = 1;
            queue<pair<int,int>> q;
            
            // Push {current_node, parent_node}
            // The starting node has no parent, so we use -1.
            q.push({i, -1});

            while (!q.empty()) {
                int node = q.front().first;
                int parent = q.front().second;
                q.pop();

                // Iterate through all neighbors of the current node
                for (int neighbor : adj[node]) {
                    
                    // CASE A: Neighbor is NOT visited
                    // This is a new path. Mark it and add to queue.
                    if (!visited[neighbor]) {
                        visited[neighbor] = 1;
                        // The current 'node' becomes the parent of 'neighbor'
                        q.push({neighbor, node}); 
                    } 
                    
                    // CASE B: Neighbor IS visited (Implicit else)
                    // If we reach here, we know 'neighbor' is already visited.
                    // We check: "Is this neighbor the one who sent me here?"
                    else if (neighbor != parent) {
                        // If it's NOT our parent, it means we found a different 
                        // path to an already visited node. That is a cycle!
                        return true; 
                    }
                }
            }
        }
    }
    
    return false;
}

int main() {
    // Test Case 1: The user's original failing case
    // Graph: 1 -- 2 -- 3 (No Cycle)
    // Note: Node 0 exists but is isolated.
    int V1 = 4;
    vector<vector<int>> edges1 = {{1, 2}, {2, 3}};
    
    cout << "Test Case 1 (1-2-3): " << (isCycle(V1, edges1) ? "Cycle Detected" : "No Cycle") << endl;

    // Test Case 2: A graph with a cycle
    // Graph: 0 -- 1 -- 2 -- 0 (Triangle)
    int V2 = 3;
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}, {2, 0}};
    
    cout << "Test Case 2 (Triangle): " << (isCycle(V2, edges2) ? "Cycle Detected" : "No Cycle") << endl;

    return 0;
}