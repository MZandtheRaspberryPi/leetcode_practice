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

int max(int a, int b)
{
    if (a > b) return a;
    else return b;
}

int abs(int a)
{
    if (a > 0) return a;
    else return a * -1;
}

int depth(TreeNode* root)
{
    if (root == nullptr)
    {
        return 0;
    }
    
    int left_depth = depth(root->left);
    if (left_depth == -1) return -1;
    int right_depth = depth(root->right);
    if (right_depth == -1) return -1;
    
    if (abs(left_depth - right_depth) > 1) return -1;
    else return max(left_depth, right_depth) + 1;
}

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        // could go from top down approach
        // if root is nullptr return 0
        // else return max of depth(left), depth(right)), plus 1
        // but for this visit each node at teh bottom for however many subtrees, O(N^2)

        // so, bottom up dfs
        // return count of depth, or -1 if notbalanced
        // so new function int depth(root)
        // if nullptr, return 0
        // else int left_depth = depth root->left
        // if left_depth == -1, return -1
        // int right_depth = depth(root->right)
        // if right_depth == -1, return -1
        //
        // return max(left_depth, right_depth) + 1
        // time complexity O(N), visit each node
        // space complexity O(logn) as recursing into tree store stack
        
        int tree_depth = depth(root);
        return tree_depth != -1;
    }
};
