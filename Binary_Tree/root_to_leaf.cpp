#include <bits/stdc++.h>
using namespace std;

/**
 * Binary Tree Node definition
 */
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) : data(x), left(NULL), right(NULL) {}
};

/**
 * Intuition:
 * We perform a depth-first traversal while maintaining a temporary path.
 * - Add the current node to the path
 * - If it is a leaf, store the path
 * - Explore left and right subtrees
 * - Remove the node while backtracking
 */
void dfs(Node* node, vector<int>& temp, vector<vector<int>>& result) {
    if (node == NULL) {
        return;
    }

    temp.push_back(node->data);

    // Leaf node check
    if (node->left == NULL && node->right == NULL) {
        result.push_back(temp);
        temp.pop_back();   // backtrack
        return;
    }

    dfs(node->left, temp, result);
    dfs(node->right, temp, result);

    temp.pop_back();   // backtrack
}

/**
 * Intuition:
 * Initialize containers and start DFS from the root.
 */
vector<vector<int>> Paths(Node* root) {
    vector<vector<int>> result;
    vector<int> temp;

    dfs(root, temp, result);
    return result;
}

int main() {
    /**
     * Constructing the binary tree:
     *
     *          1
     *         / \
     *        2   3
     *       / \   \
     *      4   5   6
     */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);

    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(6);

    // Get all root-to-leaf paths
    vector<vector<int>> result = Paths(root);

    // Print the paths
    cout << "Root-to-leaf paths:\n";
    for (const auto& path : result) {
        for (int val : path) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
