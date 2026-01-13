#include <bits/stdc++.h>
using namespace std;

/*
    Binary Tree Node
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

class Codec {
public:

    /*
        SERIALIZATION INTUITION
        -----------------------
        We perform a level-order (BFS) traversal of the tree.

        For every node:
        - If it is NOT null → store its value
        - If it IS null     → store "#"

        This way the structure of the tree is preserved.
        Example:
                 1
               /   \
              2     3
                   /
                  4

        Serialized string:
        "1,2,3,#,#,4,#,#,#,"

        The commas allow us to separate each token later.
    */
    string serialize(TreeNode* root) {
        if (root == nullptr) return "";

        queue<TreeNode*> q;
        q.push(root);

        string s = "";

        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();

            if (curr == nullptr) {
                s.append("#,");   // store null
            } else {
                s.append(to_string(curr->val) + ","); // store value
                // push children so their structure is also recorded
                q.push(curr->left);
                q.push(curr->right);
            }
        }
        return s;
    }

    /*
        DESERIALIZATION INTUITION
        ------------------------
        We read the serialized string token by token (split by commas).

        First token → root of the tree.

        Then we again use BFS:
        - Take one node from queue
        - Next token → its left child
        - Next token → its right child
        - If token is not "#", create a node and push it into queue

        This exactly reconstructs the same tree.
    */
    TreeNode* deserialize(string data) {
        if (data.size() == 0) return nullptr;

        stringstream s(data);
        string str;

        // First value is root
        getline(s, str, ',');
        TreeNode* root = new TreeNode(stoi(str));

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            // Read left child
            getline(s, str, ',');
            if (str == "#") {
                node->left = nullptr;
            } else {
                TreeNode* leftNode = new TreeNode(stoi(str));
                node->left = leftNode;
                q.push(leftNode);
            }

            // Read right child
            getline(s, str, ',');
            if (str == "#") {
                node->right = nullptr;
            } else {
                TreeNode* rightNode = new TreeNode(stoi(str));
                node->right = rightNode;
                q.push(rightNode);
            }
        }
        return root;
    }
};

/*
    Helper function: Print tree in level order
    This helps verify if the tree was rebuilt correctly.
*/
void printLevelOrder(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr == nullptr) {
            cout << "# ";
        } else {
            cout << curr->val << " ";
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    cout << endl;
}

int main() {
    Codec codec;

    cout << "Enter serialized tree (use # for null, comma separated):\n";
    cout << "Example: 1,2,3,#,#,4,#,#,#,\n\n";

    string data;
    getline(cin, data);

    // Deserialize string to tree
    TreeNode* root = codec.deserialize(data);

    cout << "\nTree after deserialization (Level Order):\n";
    printLevelOrder(root);

    // Serialize it back
    string serialized = codec.serialize(root);
    cout << "\nSerialized again:\n" << serialized << endl;

    return 0;
}
