
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

// Function to find the
// diameter of a binary tree
int diameterOfBinaryTree_optimal(Node *root)
{
    // Initialize the variable to
    // store the diameter of the tree
    int diameter = 0;
    // Call the height function to traverse
    // the tree and calculate diameter
    height_optimal(root, diameter);
    // Return the calculated diameter
    return diameter;
}

int height_optimal(Node *node, int &diameter)
{
    // Base case: If the node is null,
    // return 0 indicating the
    // height of an empty tree
    if (!node)
    {
        return 0;
    }

    // Recursively calculate the
    // height of left and right subtrees
    int lh = height_optimal(node->left, diameter);
    int rh = height_optimal(node->right, diameter);

    // Update the diameter with the maximum
    // of current diameter or sum of
    // left and right heights
    diameter = max(diameter, lh + rh);

    // Return the height of
    // the current node's subtree
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

