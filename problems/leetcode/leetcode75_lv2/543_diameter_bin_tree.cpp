/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

int diameterBinTree(TreeNode* node, int& max_path)
{
    if (node == nullptr)
    {
        return 0;
    }

    int left = diameterBinTree(node->left, max_path);
    int right = diameterBinTree(node->right, max_path);
    if (left + right > max_path)
    {
        max_path = left + right;
    }

    return max(left, right) + 1;
}


class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        // longest path between tree
        // get height of left subtree. get height of right subtree.
        // add them together, check if bigger than current max. if so, update.
        int max_path = 0;
        diameterBinTree(root, max_path);
        return max_path;
    }
};
