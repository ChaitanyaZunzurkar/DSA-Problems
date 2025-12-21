#include <bits/stdc++.h>
using namespace std;

/*
    Node structure for Binary Tree
*/
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

/*
    Intuition:
    ----------
    Right View of a Binary Tree means:
    - From each level, pick the node that appears last when viewed from the right side.

    Approach (DFS):
    ----------------
    1. Traverse the tree using DFS.
    2. Maintain a map where:
       - key   = level (row)
       - value = node->data
    3. Always traverse RIGHT subtree first, then LEFT subtree.
    4. Store the node value for a level ONLY IF that level is not already present.
       This ensures the rightmost node at that level is saved.
*/

void dfs(Node* node, int level, map<int, int>& mp) {
    // Base case: if node is null, stop recursion
    if (node == NULL) return;

    // If this level is encountered for the first time,
    // then this node is the rightmost node for that level
    if (mp.find(level) == mp.end()) {
        mp[level] = node->data;
    }

    // Visit right child first (important for right view)
    dfs(node->right, level + 1, mp);

    // Then visit left child
    dfs(node->left, level + 1, mp);
}

/*
    Function to return Right View of Binary Tree
*/
vector<int> rightView(Node* root) {
    vector<int> result;
    map<int, int> mp;

    dfs(root, 0, mp);

    // Extract values from map in level order
    for (auto& it : mp) {
        result.push_back(it.second);
    }

    return result;
}

/*
    Driver Code
*/
int main() {
    /*
            1
           / \
          2   3
           \   \
            5   4

        Right View: 1 3 4
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(5);
    root->right->right = new Node(4);

    vector<int> ans = rightView(root);

    cout << "Right View of Binary Tree: ";
    for (int x : ans) {
        cout << x << " ";
    }

    return 0;
}
