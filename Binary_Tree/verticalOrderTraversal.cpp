#include <bits/stdc++.h>
using namespace std;

/*
  Definition of a binary tree node
*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*
  INORDER DFS traversal

  Intuition:
  ----------
  1. Vertical traversal depends on COLUMN, not traversal order.
  2. Each node is assigned:
        - a column index (col)
        - a row index (row)
  3. Root starts at (col = 0, row = 0)
  4. Moving left:
        - column decreases by 1
        - row increases by 1
  5. Moving right:
        - column increases by 1
        - row increases by 1
  6. We use INORDER traversal (left → root → right) to visit nodes,
     but we STORE nodes based on column information.
*/
void inorder(TreeNode* node, int col, int row,
             map<int, vector<pair<int,int>>>& mp) {

    // Base case: no node to process
    if (node == NULL) return;

    // Visit left subtree
    //    Left child goes to column - 1 and next row
    inorder(node->left, col - 1, row + 1, mp);

    // Process current node (INORDER position)
    //    Store (row, value) in the map for this column
    mp[col].push_back({row, node->val});

    // Visit right subtree
    //    Right child goes to column + 1 and next row
    inorder(node->right, col + 1, row + 1, mp);
}

/*
  Vertical Order Traversal

  Intuition:
  ----------
  1. Use a map to group nodes by column (left to right order).
  2. Perform inorder DFS to fill the map.
  3. For each column:
        - sort nodes by row (top to bottom)
        - if rows are same, sort by value
  4. Extract values column-wise to form the final answer.
*/
vector<vector<int>> verticalTraversal(TreeNode* root) {
    // Map: column -> list of (row, value)
    map<int, vector<pair<int,int>>> mp;

    // Start inorder traversal from root
    inorder(root, 0, 0, mp);

    vector<vector<int>> result;

    // Process columns from leftmost to rightmost
    for (auto &it : mp) {
        auto &vec = it.second;

        // Sort by row first, then by value
        sort(vec.begin(), vec.end());

        vector<int> column;
        for (auto &p : vec) {
            column.push_back(p.second);
        }

        result.push_back(column);
    }

    return result;
}
/*
  Helper function to build a sample tree
*/
TreeNode* buildTree() {
    /*
            3
           / \
          9   20
             /  \
            15   7
    */
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    return root;
}

/*
  Driver code
*/
int main() {
    TreeNode* root = buildTree();

    vector<vector<int>> ans = verticalTraversal(root);

    cout << "Vertical Order Traversal:\n";
    for (auto &col : ans) {
        for (int x : col) cout << x << " ";
        cout << endl;
    }

    return 0;
}
