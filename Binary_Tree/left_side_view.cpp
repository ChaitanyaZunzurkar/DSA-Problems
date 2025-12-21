#include <bits/stdc++.h>
using namespace std;

/*
    Definition of Binary Tree Node
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
    Left View of a Binary Tree means:
    - From each level, pick the node that appears first when viewed from the left side.

    Approach (DFS):
    ----------------
    1. Traverse the tree using DFS.
    2. Maintain a map where:
       - key   = level (row)
       - value = node->data
    3. Always traverse LEFT subtree first, then RIGHT subtree.
    4. Store the node value for a level ONLY IF that level is not already present.
       This ensures the leftmost node at that level is captured.
*/

void dfs(Node* node, int level, map<int, int>& mp) {
    // Base case
    if (node == NULL) {
        return;
    }

    // If this is the first node at this level,
    // then it is the leftmost node
    if (mp.find(level) == mp.end()) {
        mp[level] = node->data;
    }

    // Visit left child first (important for left view)
    dfs(node->left, level + 1, mp);

    // Then visit right child
    dfs(node->right, level + 1, mp);
}

/*
    Function to return Left View of Binary Tree
*/
vector<int> leftView(Node* root) {
    vector<int> result;
    if (root == NULL) return result;

    map<int, int> mp;
    dfs(root, 0, mp);

    // Extract the left view nodes level-wise
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

        Left View: 1 2 5
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(5);
    root->right->right = new Node(4);

    vector<int> ans = leftView(root);

    cout << "Left View of Binary Tree: ";
    for (int x : ans) {
        cout << x << " ";
    }

    return 0;
}
