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

 int checkIsBalanced(TreeNode* node)
 {
     if (node == nullptr)
     {
         return 0;
     }
     int left = checkIsBalanced(node->left);
     if (left == -1)
     {
         return -1;
     }
     int right = checkIsBalanced(node->right);
     if (right == -1)
     {
         return -1;
     }

     if (abs(left - right) > 1)
     {
         return -1;
     }

     return max(left, right) + 1;
 }


class Solution {
public:
    bool isBalanced(TreeNode* root) {
        // could go bottom up.
        // visit nodes till nullptr, return 0 if so
        // else visit left, save left, if left == - 1, return -1
        // so with right
        // compare left and right, if abs > 1, return -1
        // else return max(left, right) + 1.
        // the max left, right, will take largest subtree, and the + 1 is adding as we go up, bottom up
        // 
        // time complexity: O(N)
        // space complexity: O(logn)
        return checkIsBalanced(root) != -1;
    }
};

