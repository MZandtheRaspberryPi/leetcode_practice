#include <queue>

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

 void swapChildren(TreeNode* node)
 {
     if (node == nullptr)
     {
         return;
     }
     TreeNode* tmp = node->left;
     node->left = node->right;
     node->right = tmp;
     swapChildren(node->left);
     swapChildren(node->right);
 }

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // check for nullptr root, return if so
       // DFS. pre-order traversal, switching left and right as we traverse.
       // time complexity O(N)
       // space complexity O(logn)
       if (root == nullptr)
       {
           return root;
       }        
       swapChildren(root);
       return root;
    }
};
