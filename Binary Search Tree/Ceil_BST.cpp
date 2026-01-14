#include <bits/stdc++.h>
using namespace std;

/*
    Node structure for BST
*/
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

/*
    Insert a value into BST
    Standard BST insertion:
    - smaller values go to left subtree
    - larger values go to right subtree
*/
Node* insertBST(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }

    if (val < root->data) {
        root->left = insertBST(root->left, val);
    } else {
        root->right = insertBST(root->right, val);
    }

    return root;
}

/*
    Function to find Ceil of x in BST

    INTUITION:
    -----------
    We traverse the BST just like binary search.

    1. If current node value == x
       → This is the ceil itself, return it.

    2. If current node value > x
       → This node CAN be a ceil.
       → Store it as a candidate.
       → Move LEFT to see if a smaller valid ceil exists.

    3. If current node value < x
       → This node cannot be ceil.
       → Move RIGHT to find larger values.

    We keep updating the best possible answer during traversal.
*/
int findCeil(Node* root, int x) {
    if (root == nullptr) {
        return -1;
    }

    int result = INT_MAX; // stores best ceil candidate

    while (root != nullptr) {

        // Case 1: exact match
        if (root->data == x) {
            return root->data;
        }

        // Case 2: current value is greater than x
        else if (root->data > x) {
            // possible ceil found
            result = min(result, root->data);
            // try to find smaller ceil in left subtree
            root = root->left;
        }

        // Case 3: current value is smaller than x
        else {
            // ceil must be in right subtree
            root = root->right;
        }
    }

    // If no ceil was found
    if (result == INT_MAX) {
        return -1;
    }

    return result;
}

int main() {
    Node* root = nullptr;

    int n;
    cout << "Enter number of nodes in BST: ";
    cin >> n;

    cout << "Enter BST elements: ";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        root = insertBST(root, val);
    }

    int x;
    cout << "Enter value to find ceil: ";
    cin >> x;

    int ceilValue = findCeil(root, x);

    if (ceilValue == -1) {
        cout << "Ceil does not exist\n";
    } else {
        cout << "Ceil of " << x << " is: " << ceilValue << endl;
    }

    return 0;
}
