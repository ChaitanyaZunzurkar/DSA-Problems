#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------
 Intuition (Bottom View using DFS)
---------------------------------------------

Bottom View means:
For every vertical column of the tree,
we want the node that is visible from the bottom.

Key observations:
1. Every node has:
   - a column (horizontal distance from root)
   - a row (depth from root)

2. If two nodes lie in the same column:
   - the node with GREATER depth (row) is visible from bottom

So we:
- Traverse the tree using DFS
- Track (column -> {depth, node_value})
- Update the map if:
    a) column is seen first time
    b) current node is deeper than stored node

Why map?
- map keeps columns sorted automatically (left to right)

---------------------------------------------
 Coordinate System
---------------------------------------------
Root        -> row = 0, col = 0
Left child  -> row + 1, col - 1
Right child -> row + 1, col + 1
---------------------------------------------
*/

// Definition of Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// DFS helper function
void dfs(Node* node, int row, int col, map<int, pair<int,int>> &mp) {
    // Base case: empty node
    if(node == nullptr) {
        return;
    }

    /*
      If this column is not yet visited OR
      current node is deeper than previously stored node,
      then update the bottom view for this column.
    */
    if(mp.find(col) == mp.end() || row >= mp[col].first) {
        mp[col] = {row, node->data};  // {depth, value}
    }

    // Move to left subtree
    dfs(node->left, row + 1, col - 1, mp);

    // Move to right subtree
    dfs(node->right, row + 1, col + 1, mp);
}

// Function to return bottom view
vector<int> bottomView(Node* root) {
    vector<int> result;
    if(root == nullptr) return result;

    // Map: column -> {depth, value}
    map<int, pair<int,int>> mp;

    // Start DFS from root
    dfs(root, 0, 0, mp);

    // Extract values in sorted column order
    for(auto &it : mp) {
        result.push_back(it.second.second);
    }

    return result;
}

// Driver code
int main() {
    /*
            20
           /  \
          8   22
         / \    \
        5  3    25
           / \
          10 14

    Bottom View: 5 10 3 14 25
    */

    Node* root = new Node(20);
    root->left = new Node(8);
    root->right = new Node(22);
    root->left->left = new Node(5);
    root->left->right = new Node(3);
    root->right->right = new Node(25);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(14);

    vector<int> ans = bottomView(root);

    cout << "Bottom View: ";
    for(int x : ans) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
