#include <bits/stdc++.h>
using namespace std;

// Binary Tree Node definition
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
INTUITION (Top View of Binary Tree using DFS):

1. From the top view, for each vertical line (horizontal distance = hd),
   we should only see the node that appears first from the top.

2. "Appears first from the top" means:
   → the node with the MINIMUM level (depth) for that horizontal distance.

3. We track three things during DFS:
   - node pointer
   - horizontal distance (hd)
   - level (depth)

4. Use a map:
   map<hd, {node_value, level}>
   - hd is the key (ensures left to right order automatically)
   - store the node value and its level

5. While traversing:
   - If an hd is seen for the first time → store it
   - If hd already exists → update ONLY if current node is at a smaller level

6. DFS traversal:
   - Left child  → hd - 1, level + 1
   - Right child → hd + 1, level + 1
*/

void dfs(Node* node, int hd, int level, map<int, pair<int,int>> &mp) {

    // Base case: stop if node is NULL
    if (node == NULL) return;

    // If this horizontal distance is seen for the first time
    // OR if the current node is at a higher position (smaller level)
    if (mp.find(hd) == mp.end() || level < mp[hd].second) {
        mp[hd] = {node->data, level};
    }

    // Traverse left subtree
    // Horizontal distance decreases by 1
    // Level increases by 1
    dfs(node->left, hd - 1, level + 1, mp);

    // Traverse right subtree
    // Horizontal distance increases by 1
    // Level increases by 1
    dfs(node->right, hd + 1, level + 1, mp);
}

vector<int> topView(Node *root) {
    vector<int> result;

    // Edge case: empty tree
    if (root == NULL) return result;

    // Map to store topmost node for each horizontal distance
    // key   -> horizontal distance
    // value -> {node value, level}
    map<int, pair<int,int>> mp;

    // Start DFS from root
    // hd = 0, level = 0
    dfs(root, 0, 0, mp);

    // Extract answer from map
    // Map keeps keys sorted, so result is left-to-right
    for (auto it : mp) {
        result.push_back(it.second.first);
    }

    return result;
}

// Optional: main function for testing
int main() {
    /*
            1
           / \
          2   3
           \
            4
             \
              5
               \
                6

        Top View: 2 1 3 6
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(4);
    root->left->right->right = new Node(5);
    root->left->right->right->right = new Node(6);

    vector<int> ans = topView(root);

    for (int x : ans) {
        cout << x << " ";
    }

    return 0;
}
