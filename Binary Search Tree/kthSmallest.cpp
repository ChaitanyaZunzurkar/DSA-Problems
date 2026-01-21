#include <bits/stdc++.h>
using namespace std;

/*
 Definition for a binary tree node.
*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* =========================================================
   SOLUTION 1: Sub-optimal (Brute / Basic Thinking)
   ---------------------------------------------------------
   Intuition:
   - Do an inorder traversal of the BST.
   - Inorder traversal of a BST gives values in sorted order.
   - Store all values in a vector.
   - Return the (k-1)th index element.

   Why this is not optimal?
   - We store all n elements even though we only need kth.
   - Extra space O(n).
   ========================================================= */

void inorderStore(TreeNode* root, vector<int>& arr) {
    if (!root) return;

    inorderStore(root->left, arr);
    arr.push_back(root->val);
    inorderStore(root->right, arr);
}

int kthSmallest_Brute(TreeNode* root, int k) {
    vector<int> arr;
    inorderStore(root, arr);
    return arr[k - 1];
}

/* =========================================================
   SOLUTION 2: Optimal (Inorder + Counter)
   ---------------------------------------------------------
   Intuition:
   - BST inorder traversal gives sorted order.
   - Instead of storing all elements, count nodes as we traverse.
   - Decrease k when visiting each node.
   - When k becomes 0, current node is the answer.
   - Stop traversal early once answer is found.

   Time Complexity:
   - O(n) worst case
   Space Complexity:
   - O(h) recursion stack (h = height of tree)
   ========================================================= */

void inorderOptimal(TreeNode* root, int& k, int& ans) {
    if (!root || k == 0) return;

    inorderOptimal(root->left, k, ans);

    if (--k == 0) {
        ans = root->val;
        return;
    }

    inorderOptimal(root->right, k, ans);
}

int kthSmallest_Optimal(TreeNode* root, int k) {
    int ans = -1;
    inorderOptimal(root, k, ans);
    return ans;
}

/* =========================================================
   Driver Code
   ========================================================= */

int main() {
    /*
            5
           / \
          3   6
         / \
        2   4
       /
      1

      Inorder: 1 2 3 4 5 6
    */

    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->left->left->left = new TreeNode(1);

    int k = 3;

    cout << "Brute Solution Answer: "
         << kthSmallest_Brute(root, k) << endl;

    cout << "Optimal Solution Answer: "
         << kthSmallest_Optimal(root, k) << endl;

    return 0;
}
