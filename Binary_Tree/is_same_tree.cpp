#include <iostream>
using namespace std;

/*
 Intuition:
 ----------
 We are checking whether two binary trees are exactly the same.

 "Same" means:
 1) Both trees have nodes at the same positions
 2) The values of corresponding nodes are equal
 3) Left subtrees are identical AND right subtrees are identical

 We compare trees node-by-node using recursion.
*/

// Definition of binary tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};

/*
 Function: isSameTree

 Intuition:
 ----------
 - If one node is NULL and the other is not → trees are different
 - If both nodes are NULL → trees are same up to this point
 - If values differ → trees are different
 - Otherwise:
     • Recursively compare left subtrees
     • Recursively compare right subtrees
 - Trees are same only if BOTH left and right subtrees are same
*/
bool isSameTree(TreeNode* p, TreeNode* q) {
    // One is NULL and other is not → not same
    if (p == NULL && q != NULL) return false;
    if (p != NULL && q == NULL) return false;

    // Both are NULL → same subtree
    if (p == NULL || q == NULL) return true;

    // Values differ → not same
    if (p->val != q->val) {
        return false;
    }

    // Compare left subtrees
    bool isLeftSame = isSameTree(p->left, q->left);

    // Compare right subtrees
    bool isRightSame = isSameTree(p->right, q->right);

    // Both sides must match
    if (isLeftSame && isRightSame) {
        return true;
    }

    return false;
}

int main() {
    /*
      Example Trees:

      Tree 1:        Tree 2:
          1              1
         / \            / \
        2   3          2   3
    */

    // Construct first tree
    TreeNode* p = new TreeNode(1);
    p->left = new TreeNode(2);
    p->right = new TreeNode(3);

    // Construct second tree
    TreeNode* q = new TreeNode(1);
    q->left = new TreeNode(2);
    q->right = new TreeNode(3);

    // Check if trees are same
    if (isSameTree(p, q)) {
        cout << "Trees are SAME" << endl;
    } else {
        cout << "Trees are DIFFERENT" << endl;
    }

    return 0;
}
