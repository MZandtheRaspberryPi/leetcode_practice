#include <stack>

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

TreeNode* findFirstNode(TreeNode* node, std::stack<TreeNode*>& nodes_to_visit)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    nodes_to_visit.push(node);
    TreeNode* next = findFirstNode(node->left, nodes_to_visit);
    if (next != nullptr) return next;
    nodes_to_visit.pop();
    return node;
}

class BSTIterator {
    // to get next, we either have to store all the nodes we have previously traversed
    // so we can unravel the stack, like recursion
    // or we go through tree each time and find the number we last did, and then return next
    // lets use storage
    // we will store logn calls, as we visit a node, we will check if the prior two in
    // stack are the left and right, and if so, dont put them in.
    // stack takes O(logn) storage
    // time complexity, O(1) on average, longer on init

public:
    BSTIterator(TreeNode* root) {
        // on init, move to the next node
        nodes_to_visit.push(nullptr);
        next_node = findFirstNode(root, nodes_to_visit);
    }
    
    int next() {
        TreeNode* node_to_return = next_node;
        // we could be visiing left, if so visit parent next
        // we could be visiting right, if so, skip parent
        // we could be visiting node, if so visit right
        if (node_to_return->right != nullptr)
        {
            next_node = findFirstNode(node_to_return->right, nodes_to_visit);
        }
        else
        {

            next_node = nodes_to_visit.top();
            nodes_to_visit.pop();
        }

        return node_to_return->val;
    }
    
    bool hasNext() {
        return next_node != nullptr;
        
    }
private:
  std::stack<TreeNode*> nodes_to_visit;
  TreeNode* next_node;
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
