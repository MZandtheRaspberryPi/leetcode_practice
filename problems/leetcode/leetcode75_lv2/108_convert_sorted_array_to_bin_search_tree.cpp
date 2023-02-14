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

TreeNode* makeBinarySearchTree(const vector<int>& nums, TreeNode* parent, int low, int high)
{
    if (low > high)
    {
        return parent;
    }
    int mid = (low + high) / 2;
    int val = nums[mid];
    TreeNode* new_node = new TreeNode(val);
    if (parent == nullptr)
    {
        parent = new_node;
    }
    else
    {
        if (val <= parent->val)
        {
            parent->left = new_node;
        }
        else
        {
            parent->right = new_node;
        }
    }
    makeBinarySearchTree(nums, new_node, low, mid-1);
    makeBinarySearchTree(nums, new_node, mid+1, high);
    return parent;
}

class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // to do this, we want to take middle of array as starting point, and split left half and right half as children. 
        // so a recursive function that takes an array ref, and a starting index and high index, and a node, parent node
        // if low > high, return
        // it then makes a new node if one not already there and sets parent to it.
        // then sets left to the new low to mid - 1, and right to mid + 1 to high.
        TreeNode* head = makeBinarySearchTree(nums, nullptr, 0, nums.size() - 1);
        return head;
    }
};
