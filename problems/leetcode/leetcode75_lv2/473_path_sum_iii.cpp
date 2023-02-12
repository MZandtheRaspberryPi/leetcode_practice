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

void findPaths(TreeNode* node, const int& targ_count, long long& cur_count, long long& num_paths)
{
    if (node == nullptr)
    {
        return;
    }
    cur_count += node->val;
    if (cur_count == targ_count)
    {
        num_paths++;
    }
    findPaths(node->left, targ_count, cur_count, num_paths);
    findPaths(node->right, targ_count, cur_count, num_paths);
    cur_count -= node->val;
    return;
}

class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        // take each node as a potential starting point
        // do BFS, and for each node, to DFS on it, carrying running sum (starting at zero)
        // in BFS, add current node to running sum, if it adds up to target then add 1 to found paths, and go left.
        // then go right
        // then subtract val from runnign sum and return.

        // time complexity: we visit each node, and for each node visit each other node, roughl O(N^2)
        // space complexity: we store N nodes, when doing DFS, and store logn to do recursion. O(N)

        // feedback from sol, could have done all with recursion
        // something like pathSum.....return sumUp(root, 0, sum) + pathSum(root->left, sum) + pathSum(root->right, sum)

        std::queue<TreeNode*> nodes_to_visit;
        nodes_to_visit.push(root);
        int num_total_paths = 0;
        while (nodes_to_visit.size() > 0)
        {
            TreeNode* node = nodes_to_visit.front();
            nodes_to_visit.pop();
            if (node == nullptr)
            {
                continue;
            }
            nodes_to_visit.push(node->left);
            nodes_to_visit.push(node->right);
            long long cur_count = 0;
            long long num_paths = 0;
            findPaths(node, targetSum, cur_count, num_paths);
            num_total_paths += num_paths;
        }
        return num_total_paths;
        
    }
};
