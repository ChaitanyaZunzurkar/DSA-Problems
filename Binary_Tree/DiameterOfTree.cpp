
#include <iostream>
#include <algorithm>

using namespace std;

// Node structure for
// the binary tree
struct Node
{
    int data;
    Node *left;
    Node *right;
    // Constructor to initialize
    // the node with a value
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

int maxi = 0;

// Function to calculate height of a subtree
int height(Node* node) {
    // If node is null, height is 0
    if (node == nullptr) return 0;

    // Height of a node is:
    // 1 (current node) + maximum height of its left or right subtree
    return 1 + max(height(node->left), height(node->right));
}

int diameterOfBinaryTree_brute(Node* root) {
    // If tree (or subtree) is empty, diameter is 0
    if (root == nullptr) return 0;

    // Step 1:
    // Compute height of left subtree of current node
    int leftHeight = height(root->left);

    // Step 2:
    // Compute height of right subtree of current node
    int rightHeight = height(root->right);

    // Step 3:
    // Diameter passing through the current node is
    // leftHeight + rightHeight.
    // Update the global maximum diameter if this is larger.
    maxi = max(maxi, leftHeight + rightHeight);

    // Step 4:
    // Recursively repeat the same process for left subtree
    // so that diameter is checked at every node.
    diameterOfBinaryTree_brute(root->left);

    // Step 5:
    // Recursively repeat the same process for right subtree
    // so that diameter is checked at every node.
    diameterOfBinaryTree_brute(root->right);

    // Step 6:
    // Return the maximum diameter found so far in the entire tree.
    return maxi;
}

// Function to find the diameter of a binary tree (OPTIMAL APPROACH)
int diameterOfBinaryTree_optimal(Node *root)
{
    // This variable will store the maximum diameter found so far.
    // It is passed by reference so that all recursive calls
    // can update the same value.
    int diameter = 0;

    // We start a depth-first traversal of the tree.
    // While computing the height of each subtree,
    // we will also update the diameter.
    height_optimal(root, diameter);

    // After the full traversal, 'diameter' contains
    // the longest path between any two nodes in the tree.
    return diameter;
}

int height_optimal(Node *node, int &diameter)
{
    // Base case:
    // If the current node is NULL, the height of this subtree is 0.
    if (!node)
    {
        return 0;
    }

    // Recursively compute the height of the left subtree.
    // During this recursion, the diameter may get updated.
    int lh = height_optimal(node->left, diameter);

    // Recursively compute the height of the right subtree.
    // During this recursion, the diameter may get updated.
    int rh = height_optimal(node->right, diameter);

    // For the current node, the longest path that passes through it
    // is the sum of heights of its left and right subtrees.
    // We compare this value with the maximum diameter seen so far
    // and update it if needed.
    diameter = max(diameter, lh + rh);

    // Return the height of the current subtree.
    // Height is defined as:
    // 1 (current node) + maximum of left and right subtree heights.
    return 1 + max(lh, rh);
}

// Main function
int main()
{
    // Creating a sample binary tree
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->right = new Node(6);
    root->left->right->right->right = new Node(7);

    // Calculate the diameter of the binary tree
    int diameter = diameterOfBinaryTree_optimal(root);

    cout << "The diameter of the binary tree is: " << diameter << endl;

    return 0;
}

