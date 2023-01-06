/*
design an algo, and write code, to find first common ancestor of two nodes in binary tree.

avoid storing addtl nodes in datastructure. note, not nescessarily a binary search tree.


function takes root, node1 node2.

DFS to find one of the nodes, but checking children.
If root nullptr return nullptr.

visit root->left.

if root->left == node1 || root->right == node1.
checkIfNodeInTree(root, node2)
checkIfNodeInTree(root, node2)
if that or that, return root.

if root->left == node2 || root->right == node2.
checkIfNodeInTree(root, node1)
checkIfNodeInTree(root, node1)
if that or that return root

visit root->right.
--

 when . check if the node2 is under node 1 with dfs, then return nullptr if not, or return prev if so.


feedback:
i did a lot of traversals i didnt need to. also, you dont nescessarily have to find the nodes and then return parents.
Instead, you could traverse tree looking for point when the two diverge, ie one is in a right subtree and one is in a left subtree.
But even with this, you are doing more checks than need be. when we check the subtrees at each node, we dont need to.
still runs in O(N), but for first node we check O(2N) (left and right subtrees) for second node we check O(2N/2), third node, O(2N/4), ect...

an alternative is to make a function that recurses through the tree and returns
p if roots subtree includes p (and not q)
q if roots subtree includes q (and not p)
nullptr if neither p nor q in roots subtree
else, returns common ancestor of p and q

when common ancestor of left and right both return non null values, then common ancestor found.

watch out for the case where p is a child of q or q is a child of p. we may get confused as we dont distinguish between that and p is in tree and q not






*/
#include <stdio.h>
#include <vector>

struct Node
{
	int data;
	Node* left;
	Node* right;
};

bool isNodeInTree(Node* root, Node* node)
{
	if (root == nullptr)
	{
		return false;
	}
	
	bool is_in_left = isNodeInTree(root->left, node);
	
	if (is_in_left)
	{
		return true;
	}
	
	if (root == node)
	{
		return true;
	}
	
	bool is_in_right = isNodeInTree(root->right, node);
	
	if (is_in_right)
	{
		return true;
	}
	
	return false;
}

Node* findNearestAncestor(Node* root, Node* node1, Node* node2)
{
	 if (root == nullptr)
	 {
		 return nullptr;
	 }
	 
	 Node* node_to_look_for = nullptr;
	 if (root->left == node1 || root->right == node1)
	 {
		 node_to_look_for = node2;
	 }
	 
	 if (root->left == node2 || root->right == node2)
	 {
		 node_to_look_for = node1;
	 }
	 
	 bool is_in_left_tree = isNodeInTree(root->left, node_to_look_for);
	 if (is_in_left_tree)
	 {
		 return root;
	 }
	 
	 bool is_in_right_tree = isNodeInTree(root->right, node_to_look_for);
	 
	 if (is_in_right_tree)
	 {
		 return root;
	 }

	 Node* left_common_ancestor = findNearestAncestor(root->left, node1, node2);
	 if (left_common_ancestor != nullptr)
	 {
		 return left_common_ancestor;
	 }
	 Node* right_common_ancestor = findNearestAncestor(root->right, node1, node2);
	 if (right_common_ancestor != nullptr)
	 {
		 return right_common_ancestor;
	 }
	 
	 return nullptr;
}
Node* findNearestAncestorOptimalHelper(Node* root, Node* node1, Node* node2)
{
	if (root == nullptr)
	{
		return nullptr;
	}
	
	if (root == node1 && root == node2)
	{
    return root;
	}
	
	Node* x = findNearestAncestorOptimalHelper(root->left, node1, node2);
	if (x != nullptr && x != node1 && x != node2)
	{
		// found common ancestor, return
		return x;
	}
	
	Node* y = findNearestAncestorOptimalHelper(root->right, node1, node2);
	if (y != nullptr && y != node1 && y != node2)
	{
	  return y;
	}
	
	if (x != nullptr && y != nullptr)
	{
		return root; // this is the common ancestor
	}
	else if (root == node1 || root == node2)
	{
		return root;
	}
	else
	{
		// if either x or y is non nullptr, return nullptr value
		return x == nullptr ? y : x;
	}
	
}
Node* findNearestAncestorOptimal(Node* root, Node* node1, Node* node2)
{
	// check edge case where p or q not in tree, return nullptr if so
	if (!isNodeInTree(root, node1) || !isNodeInTree(root, node2))
	{
		return nullptr;
	}
	
	return findNearestAncestorOptimalHelper(root, node1, node2);
}

int main()
{
	
	std::vector<Node*> vect;
	
	for (int i = 0; i < 10; i++)
	{
		Node* new_node = new Node{};
		new_node->data = i;
		vect.push_back(new_node);
	}
	
	Node* root = vect[4];
	
	root->left = vect[2];
	root->right = vect[7];
	
	root->left->left = vect[1];
	root->left->right = vect[3];
	
	root->right->left = vect[6];
	root->right->right = vect[9];
	
	Node* common_ancestor = findNearestAncestor(root, vect[1], vect[3]);
	if (common_ancestor == nullptr)
	{
	  printf("common ancestor is nullptr\n");
	}
	else
	{
		printf("common ancestor is %d\n", common_ancestor->data);
	}
	
	common_ancestor = findNearestAncestorOptimal(root, vect[1], vect[3]);
		if (common_ancestor == nullptr)
	{
	  printf("common ancestor is nullptr\n");
	}
	else
	{
		printf("common ancestor is %d\n", common_ancestor->data);
	}
	
	for (Node* node : vect)
	{
		delete node;
	}
	
}