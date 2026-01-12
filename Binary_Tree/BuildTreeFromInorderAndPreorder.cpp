#include <bits/stdc++.h>
using namespace std;

/*
    Tree Node definition
*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};

unordered_map<int , int> mp;
/*
    build(...) means:
    Construct the binary tree formed by:
    inorder[inStart ... inEnd]
    postorder[postStart ... postEnd]
*/
TreeNode* build(vector<int>& inorder, vector<int>& postorder,
                int inStart, int inEnd,
                int postStart, int postEnd)
{
    /*
        If no elements are left in either traversal,
        this subtree does not exist
    */
    if (inStart > inEnd || postStart > postEnd)
        return nullptr;

    /*
        In postorder traversal:
        Left → Right → Root

        So the LAST element of current postorder range
        is always the root of this subtree
    */
    int rootVal = postorder[postEnd];
    TreeNode* root = new TreeNode(rootVal);

    /*
        Find root position in inorder traversal
        inorder is: Left → Root → Right
    */
    int k = mp[rootVal];

    /*
        Number of nodes in left subtree
    */
    int leftSize = k - inStart;

    /*
        Left subtree is formed from:
        inorder:   inStart → k-1
        postorder: postStart → postStart + leftSize - 1
    */
    root->left = build(inorder, postorder,
                       inStart, k - 1,
                       postStart, postStart + leftSize - 1);

    /*
        Right subtree is formed from:
        inorder:   k+1 → inEnd
        postorder: postStart + leftSize → postEnd - 1
        (postEnd is root, so we exclude it)
    */
    root->right = build(inorder, postorder,
                        k + 1, inEnd,
                        postStart + leftSize, postEnd - 1);

    return root;
}

/*
    Function to start the construction
*/
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
{
    /*
        Store inorder value → index
        This lets us find root position in O(1) time
    */
    for (int i = 0; i < inorder.size(); i++)
        mp[inorder[i]] = i;

    return build(inorder, postorder,
                 0, inorder.size() - 1,
                 0, postorder.size() - 1);
}

/*
    Preorder print to verify the tree
*/
void printPreorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    vector<int> inorder(n), postorder(n);

    cout << "Enter inorder traversal:\n";
    for (int i = 0; i < n; i++)
        cin >> inorder[i];

    cout << "Enter postorder traversal:\n";
    for (int i = 0; i < n; i++)
        cin >> postorder[i];

    TreeNode* root = buildTree(inorder, postorder);

    cout << "\nPreorder traversal of constructed tree:\n";
    printPreorder(root);

    return 0;
}
