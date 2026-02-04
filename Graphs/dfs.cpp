#include <bits/stdc++.h>
using namespace std;

/*
===========================================================
INTUITION OF DFS

DFS = go as deep as possible before coming back.

Recursive DFS:
Works using the FUNCTION CALL STACK
0 -> 1 -> 2 -> 5 -> backtrack -> explore remaining

Iterative DFS:
We manually simulate recursion using STACK
(stack behaves same as recursion call stack)

Golden Idea:
recursive call stack == explicit stack

===========================================================
*/


// ================= RECURSIVE DFS =================
/*
We visit a node
Then recursively visit all unvisited neighbours

IMPORTANT:
result & visited passed by reference -> shared across calls
node passed by value -> represents current position
*/
void dfsRecursiveUtil(int node,
                      vector<vector<int>> &adj,
                      vector<int> &visited,
                      vector<int> &result)
{
    // mark visited when we ENTER node (same as recursion entry)
    visited[node] = 1;
    result.push_back(node);

    // explore neighbours depth-wise
    for(int neighbour : adj[node])
    {
        if(!visited[neighbour])
            dfsRecursiveUtil(neighbour, adj, visited, result);
    }
}

vector<int> dfsRecursive(vector<vector<int>> &adj)
{
    vector<int> visited(adj.size(), 0);
    vector<int> result;

    // handles disconnected graph also
    for(int i = 0; i < adj.size(); i++)
        if(!visited[i])
            dfsRecursiveUtil(i, adj, visited, result);

    return result;
}



// ================= ITERATIVE DFS =================
/*
We simulate recursion manually using stack

Key Rules:
1) push node
2) pop node
3) if not visited -> process
4) push neighbours

IMPORTANT:
visited marked when POPPING
(because that is when recursion actually processes node)
*/
vector<int> dfsIterative(vector<vector<int>>& adj) {
    vector<int> visited(adj.size() , 0);
    vector<int> result;
    stack<int> st;
        
    st.push(0);
        
    while(!st.empty()) {
        int node = st.top();
        st.pop();
            
        if(visited[node]) continue;
        visited[node] = 1; 
            
        result.push_back(node);
        for(int i = adj[node].size()-1; i>=0; i--) {
            int it = adj[node][i];
            if(!visited[it])
                st.push(it);
        }
    }
        
    return result;
}



// ================= MAIN FUNCTION =================
int main()
{
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<int>> adj(n);

    cout << "Enter edges (u v):\n";
    for(int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        // undirected graph
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // run DFS
    vector<int> rec = dfsRecursive(adj);
    vector<int> iter = dfsIterative(adj);

    // print results
    cout << "\nRecursive DFS: ";
    for(int x : rec) cout << x << " ";

    cout << "\nIterative DFS: ";
    for(int x : iter) cout << x << " ";

    cout << endl;
}
