#include <bits/stdc++.h>
using namespace std;

/*
    Node structure for a binary tree
*/
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

/*
    Intuition:
    ----------
    We want to find all root-to-leaf paths.
    
    To do this, we use DFS (Depth First Search).
    While moving down the tree, we store the current path in a temporary vector `temp`.

    Key idea:
    - When we ENTER a node → add it to `temp`
    - When we REACH a leaf → store the current path
    - When we EXIT a node → remove it from `temp` (backtracking)

    This ensures `temp` always represents the path from root to the current node.
*/

void dfs(Node *node, vector<int> &temp, vector<vector<int>> &result) {
    // Base case: if node is NULL, nothing to process
    if (node == NULL) {
        return;
    }

    /*
        Step 1: Include current node in the path
        This represents moving DOWN the tree
    */
    temp.push_back(node->data);

    /*
        Step 2: Check if this node is a LEAF
        A leaf node has no left and no right child
    */
    if (node->left == NULL && node->right == NULL) {
        // We have reached the end of one root-to-leaf path
        result.push_back(temp);

        /*
            Backtracking:
            Remove current node before returning to parent
        */
        temp.pop_back();
        return;
    }

    /*
        Step 3: Recurse on left subtree
        This explores paths going through the left child
    */
    dfs(node->left, temp, result);

    /*
        Step 4: Recurse on right subtree
        This explores paths going through the right child
    */
    dfs(node->right, temp, result);

    /*
        Step 5: Backtracking
        Remove current node before going back to parent call
        This ensures sibling paths don't get polluted
    */
    temp.pop_back();
}

/*
    Wrapper function
    ----------------
    Initializes data structures and starts DFS from root
*/
vector<vector<int>> Paths(Node* root) {
    vector<vector<int>> result; // stores all root-to-leaf paths
    vector<int> temp;           // stores current path

    dfs(root, temp, result);
    return result;
}

/*
    Driver code to test the implementation
*/
int main() {
    /*
            1
           / \
          2   3
           \
            5

        Expected paths:
        1 -> 2 -> 5
        1 -> 3
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(5);

    vector<vector<int>> paths = Paths(root);

    // Print all paths
    for (auto &path : paths) {
        for (int val : path) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
