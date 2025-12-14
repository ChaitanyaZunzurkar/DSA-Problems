#include <bits/stdc++.h>
using namespace std;

/*
    Definition of a Binary Tree Node
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

/*
    ITERATIVE INORDER TRAVERSAL

    Inorder = Left -> Root -> Right

    INTUITION:
    - Recursion internally uses a call stack
    - To remove recursion, we use our own stack
    - We cannot process a node until its left subtree is fully done
    - So whenever we see a node, we:
        1) Save it (push into stack)
        2) Move left
    - When left becomes NULL:
        - We backtrack using stack
        - Process the node
        - Move to its right subtree
*/
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;

    // If tree is empty, nothing to traverse
    if(root == NULL) return result;

    stack<TreeNode*> st;
    TreeNode* node = root;

    /*
        We continue traversal until:
        - There is no current node AND
        - There is nothing left in the stack to return to
    */
    while(true) {

        /*
            CASE 1: node is NOT NULL
            --------------------------------
            - We are moving down the left subtree
            - We cannot process this node yet
            - So we save it for later and go left
        */
        if(node != NULL) {
            st.push(node);
            node = node->left;
        }

        /*
            CASE 2: node is NULL
            --------------------------------
            - Left subtree is finished
            - Time to backtrack
        */
        else {
            // If there is nothing to backtrack to, traversal is complete
            if(st.empty()) break;

            // Get the last saved node
            node = st.top();
            st.pop();

            // Now it is safe to process the node
            result.push_back(node->val);

            // After Root, move to Right subtree
            node = node->right;
        }
    }

    return result;
}

/*
    Helper function to build a sample tree:

            1
           / \
          2   3
         / \
        4   5
*/
TreeNode* buildSampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    return root;
}

int main() {
    /*
        We build a sample binary tree.
        You can modify this or take input dynamically if needed.
    */
    TreeNode* root = buildSampleTree();

    vector<int> inorder = inorderTraversal(root);

    cout << "Inorder Traversal: ";
    for(int val : inorder) {
        cout << val << " ";
    }

    return 0;
}
