/*
Implement a function to check if a binary tree is a binary search tree.

Use DFS. recursive function, returns bool.

if root is nullptr return true.

if root->left is not nullptr, confirm it is less or equal to data. if not, return false.
if root->right is not nullptr, confirm it is greater than data. if not, return false.
success = visit left.
if not sucess return false.
success &= visit right.
return success.

time complexity in worst case is O(N).
storage is O(logn) to store recursive calls in the stack.

feedback missed that nodes to left of root all have to be smaller.
even if a branch right below. so this solution misses some cases.

either, use in order traversal, left, root, right, and add to array.
then go through array and check if sorted.

or keep track of previous and compare current to previous.

or, recurse through checking if node is between expected range.
min starts as int min. max starts as int max.
when go left update max to root. when go right update min to root.


*/

#include <cmath>
#include <vector>
#include <stdio.h>

const int int_max = std::pow(2, 31) - 1;
const int int_min = std::pow(2, 31) * -1;

struct Node {
  int data;
  Node *left;
  Node *right;
};

bool isBinarySearchTree(Node* root)
{
	if (root != nullptr)
	{
		bool success = true;
		if (root->left != nullptr)
		{
			success &= (root->data >= root->left->data);
			if (!success) return false;
			success &= isBinarySearchTree(root->left);
			if (!success) return false;
		}
		
		if (root->right != nullptr)
		{
			success &= (root->data < root->right->data);
			if (!success) return false;
			success &= isBinarySearchTree(root->right);
			if (!success) return false;
		}
		return success;		
	}
	else
	{
		return true;
	}
	
}

bool isBinSearchTreeOptimal(Node* root, int min, int max)
{
	if (root == nullptr) return true;
	
	if (root->data <= min || root->data > max) return false;
	
	if (!isBinSearchTreeOptimal(root->left, min, root->data) ||
	    !isBinSearchTreeOptimal(root->right, root->data, max))
		{
		return false;
	}

  return true;
}

int main() {

  std::vector<Node *> created_nodes;

  for (int i = 0; i < 10; i++) {
    Node *new_node = new Node{};
    new_node->data = i;
    created_nodes.push_back(new_node);
  }

  Node *root = created_nodes[0];
  root->left = created_nodes[1];
  root->right = created_nodes[2];
  root->left->left = created_nodes[3];
  root->left->right = created_nodes[4];
	
	bool is_bin_search_tree = isBinarySearchTree(root);
	printf("first config isBinarySearchTree %d\n", is_bin_search_tree);

  for (int i = 0; i < created_nodes.size(); i++) {
    delete created_nodes[i];
  }
	
	created_nodes.clear();
	
	for (int i = 0; i < 10; i++) {
    Node *new_node = new Node{};
    new_node->data = i;
    created_nodes.push_back(new_node);
  }

  root = created_nodes[4];
	root->left = created_nodes[3];
	root->right = created_nodes[5];
	root->left->left = created_nodes[2];
	root->left->left->left = created_nodes[1];
	root->left->right = created_nodes[6];
	
	is_bin_search_tree = isBinSearchTreeOptimal(root, int_min, int_max);
	printf("second config isBinarySearchTree %d\n", is_bin_search_tree);

  for (int i = 0; i < created_nodes.size(); i++) {
    delete created_nodes[i];
  }
	
	created_nodes.clear();
	
	for (int i = 0; i < 10; i++) {
    Node *new_node = new Node{};
    new_node->data = i;
    created_nodes.push_back(new_node);
  }
	
	root = created_nodes[4];
	root->left = created_nodes[3];
	root->right = created_nodes[5];
	root->left->left = created_nodes[2];
	root->left->left->left = created_nodes[1];


	is_bin_search_tree = isBinSearchTreeOptimal(root, int_min, int_max);
	printf("third config isBinarySearchTree %d\n", is_bin_search_tree);

  for (int i = 0; i < created_nodes.size(); i++) {
    delete created_nodes[i];
  }

}