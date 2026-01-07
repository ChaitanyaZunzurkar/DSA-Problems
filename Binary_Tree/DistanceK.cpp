#include <bits/stdc++.h>
using namespace std;

/*
 Binary Tree Node definition
*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) {
        val = x;
        left = right = nullptr;
    }
};

vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {

    /*
    INTUITION STEP 1:
    A binary tree does not allow moving upward.
    So first, we store parent of every node using BFS.
    This converts the tree into an undirected graph.
    */

    unordered_map<TreeNode*, TreeNode*> parents;
    queue<TreeNode*> q;

    q.push(root);   // start BFS from root

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr->left) {
            parents[curr->left] = curr;   // store parent
            q.push(curr->left);
        }

        if (curr->right) {
            parents[curr->right] = curr;  // store parent
            q.push(curr->right);
        }
    }

    /*
    INTUITION STEP 2:
    Now we do BFS starting from the target node.
    BFS level = distance from target.
    We stop when distance == k.
    */

    unordered_set<TreeNode*> visited;
    queue<TreeNode*> bfs;

    bfs.push(target);
    visited.insert(target);

    int distance = 0;

    while (!bfs.empty()) {

        int size = bfs.size();

        // When we reach distance K, stop expanding further
        if (distance == k) break;

        while (size--) {
            TreeNode* curr = bfs.front();
            bfs.pop();

            // Move to left child
            if (curr->left && !visited.count(curr->left)) {
                visited.insert(curr->left);
                bfs.push(curr->left);
            }

            // Move to right child
            if (curr->right && !visited.count(curr->right)) {
                visited.insert(curr->right);
                bfs.push(curr->right);
            }

            // Move to parent (upward movement)
            if (parents.count(curr) && !visited.count(parents[curr])) {
                visited.insert(parents[curr]);
                bfs.push(parents[curr]);
            }
        }

        distance++;
    }

    /*
    INTUITION STEP 3:
    All nodes remaining in the queue are exactly
    at distance K from the target.
    */

    vector<int> result;
    while (!bfs.empty()) {
        result.push_back(bfs.front()->val);
        bfs.pop();
    }

    return result;
}

/*
 Helper function to build tree using level-order input
 -1 means NULL
*/
TreeNode* buildTree() {
    int val;
    cin >> val;

    if (val == -1) return nullptr;

    TreeNode* root = new TreeNode(val);
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        int leftVal, rightVal;
        cin >> leftVal >> rightVal;

        if (leftVal != -1) {
            curr->left = new TreeNode(leftVal);
            q.push(curr->left);
        }

        if (rightVal != -1) {
            curr->right = new TreeNode(rightVal);
            q.push(curr->right);
        }
    }

    return root;
}

int main() {

    /*
    Input format (level order):
    Example:
    1
    2 3
    4 5 6 7
    -1 -1 -1 -1 -1 -1 -1 -1

    Target value and K:
    2 2
    */

    cout << "Enter tree (level order, -1 for NULL):\n";
    TreeNode* root = buildTree();

    int targetVal, k;
    cout << "Enter target value and K:\n";
    cin >> targetVal >> k;

    // Find target node using BFS
    queue<TreeNode*> q;
    q.push(root);
    TreeNode* target = nullptr;

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr->val == targetVal) {
            target = curr;
            break;
        }

        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }

    vector<int> ans = distanceK(root, target, k);

    cout << "Nodes at distance " << k << ": ";
    for (int x : ans) cout << x << " ";

    return 0;
}
