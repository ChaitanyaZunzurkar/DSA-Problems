#include <bits/stdc++.h>
using namespace std;

class Solution {
private: 

    /*
    DFS:
    Visits all cities connected (directly or indirectly)
    to the starting city.

    Entire reachable group = ONE PROVINCE
    */
    void dfs(int node , vector<int> &visited, vector<vector<int>> &adj) {

        visited[node] = 1;

        for(int neighbor : adj[node]) {
            if(!visited[neighbor]) {
                dfs(neighbor, visited, adj);
            }
        }
    }

public:

    /*
    A province = connected component in an undirected graph

    Steps:
    1) Convert adjacency matrix -> adjacency list
    2) Run DFS from every unvisited node
    3) Number of DFS calls = number of provinces
    */
    int findCircleNum(vector<vector<int>>& isConnected) {

        int n = isConnected.size();

        vector<vector<int>> adjList(n);
        vector<int> visited(n , 0);

        // STEP 1: Build graph
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {

                if(isConnected[i][j] == 1 && i != j) {
                    adjList[i].push_back(j);
                    adjList[j].push_back(i);
                }
            }
        }

        // STEP 2: Count connected components
        int count = 0;

        for(int i = 0; i < n; i++) {
            if(!visited[i]) {
                count++;
                dfs(i , visited , adjList);
            }
        }

        return count;
    }
};


int main() {

    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> isConnected(n, vector<int>(n));

    cout << "Enter adjacency matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> isConnected[i][j];
        }
    }

    Solution obj;
    int provinces = obj.findCircleNum(isConnected);

    cout << "Number of Provinces: " << provinces << endl;

    return 0;
}
