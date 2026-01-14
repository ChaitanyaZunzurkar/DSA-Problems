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
    Function to find Floor of x in BST

    INTUITION:
    -----------
    Floor(x) = largest value <= x

    We traverse the BST similar to binary search.

    1. If current node value == x
       → Exact match, this is the floor.

    2. If current node value < x
       → This node CAN be a floor.
       → Save it as a candidate.
       → Move RIGHT to search for a larger valid floor.

    3. If current node value > x
       → This node cannot be floor.
       → Move LEFT to search smaller values.

    We keep updating the best possible floor while traversing.
*/
int floorBST(Node* root, int x) {
    if (root == nullptr) {
        return -1;
    }

    int result = -1; // stores best floor candidate

    while (root != nullptr) {

        // Case 1: exact match
        if (root->data == x) {
            return root->data;
        }

        // Case 2: current value is smaller than x
        else if (root->data < x) {
            // possible floor found
            result = max(result, root->data);
            // try to find larger floor in right subtree
            root = root->right;
        }

        // Case 3: current value is greater than x
        else {
            // floor must be in left subtree
            root = root->left;
        }
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
    cout << "Enter value to find floor: ";
    cin >> x;

    int floorValue = floorBST(root, x);

    if (floorValue == -1) {
        cout << "Floor does not exist\n";
    } else {
        cout << "Floor of " << x << " is: " << floorValue << endl;
    }

    return 0;
}
