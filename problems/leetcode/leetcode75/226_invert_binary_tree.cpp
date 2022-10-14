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

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        // check for nullptr root, return if so
        // make a new root, set equal to old root
        // make a queue, fifo
        // put the root in the queue
        // while queue is not empty
        // pop from the queue, add right to queue, add left to queue
        // add val to tree, new method for that
        // new method takes node to add to, compares to value of node,
        // if greater than and left is not nullptr recurse left
        // else if greater than set left and return
        // else if ! greater than and right is not nullptr recurse right
        // else if ! greater than and right is nullptr set and return
        //once queue is empty, return new root
        
        // time complexity O(N) visit each node
        // space complexity O(1)
        
        std::queue<TreeNode*> node_q;
        node_q.push(root);
        TreeNode* tmp = nullptr;
        while (!node_q.empty())
        {
            TreeNode* node = node_q.front();
            node_q.pop();
            if (node == nullptr)
            {
                continue;
            }
            node_q.push(node->right);
            node_q.push(node->left);
            tmp = node->left;
            node->left = node->right;
            node->right = tmp;
        }

        return root;
        
    }
};
