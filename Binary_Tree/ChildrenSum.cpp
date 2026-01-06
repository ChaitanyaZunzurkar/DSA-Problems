#include <iostream>
#include <queue>
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
        left = NULL;
        right = NULL;
    }
};

/*
INTUITION (Sum Property of Binary Tree):

1. If the tree is empty → it trivially satisfies sum property.
2. If the node is a leaf → no children to sum, so it is valid.
3. For a non-leaf node:
   - Take value of left child (0 if absent)
   - Take value of right child (0 if absent)
   - Check if current node's data == left + right
4. If current node violates the condition → return false immediately.
5. Otherwise, recursively check left and right subtrees.
6. Final result is true only if:
   - current node satisfies sum property
   - left subtree satisfies sum property
   - right subtree satisfies sum property
*/

bool isSumProperty(Node *root) {

    // Base case: empty tree or leaf node
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return true;
    }

    int leftData = (root->left) ? root->left->data : 0;
    int rightData = (root->right) ? root->right->data : 0;

    // Check sum property at current node
    if (root->data != leftData + rightData) {
        return false;
    }

    // Recursively check left and right subtrees
    return isSumProperty(root->left) && isSumProperty(root->right);
}

/*
Build tree using level order input
-1 represents NULL
*/
Node* buildTree() {

    int rootData;
    cout << "Enter root value (-1 for NULL): ";
    cin >> rootData;

    if (rootData == -1) return NULL;

    Node* root = new Node(rootData);
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        int leftVal, rightVal;

        cout << "Enter left child of " << curr->data << " (-1 for NULL): ";
        cin >> leftVal;

        if (leftVal != -1) {
            curr->left = new Node(leftVal);
            q.push(curr->left);
        }

        cout << "Enter right child of " << curr->data << " (-1 for NULL): ";
        cin >> rightVal;

        if (rightVal != -1) {
            curr->right = new Node(rightVal);
            q.push(curr->right);
        }
    }

    return root;
}

int main() {

    Node* root = buildTree();

    if (isSumProperty(root)) {
        cout << "\nTree follows Sum Property" << endl;
    } else {
        cout << "\nTree does NOT follow Sum Property" << endl;
    }

    return 0;
}
