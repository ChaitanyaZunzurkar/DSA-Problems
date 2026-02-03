#include <bits/stdc++.h>
using namespace std;

int main() {
    int n , m;
    cin >> n >> m;

    vector<int> adjacencyList[n+1];
    for(int i = 0; i < m; i++) {
        int u , v;
        cin >> u >> v;
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }
    return 0;
}
