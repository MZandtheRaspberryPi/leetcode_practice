/*

Write a method that takes a pointer to a node structure as a parameter and
returns a complete copy of passed data structure. node data structure contains two pointers to other nodes.

we could have a recursive method that takes a ref to prev_node node to set. then it takes a tmp shallow copy of next node.
it then creates a new one. sets new one next to the old one next. then recurses.

time complexity O(N) where N is the number of nodes in play.
space complexity O(logn), not includng the storage for new nodes. As we store recursively in stack the calls.

feedback from solution, didnt take into account repeated nodes. we need to store visited nodes. we could in an
external structure like a map.

*/

#include <iostream>
#include <vector>
#include <unordered_map>

struct Node {
	Node* left;
	Node* right;
	
};

Node* deep_copy_helper(Node* node_to_copy, std::unordered_map<Node*, Node*>& node_map)
{
	if (node_to_copy == nullptr) return nullptr;
	
	std::unordered_map<Node*, Node*>::iterator it = node_map.find(node_to_copy);
	if (it != node_map.end())
	{
		return node_map[node_to_copy];
	}
	
	Node* new_node = new Node{};
	node_map[node_to_copy] = new_node;
	
	new_node->left = deep_copy_helper(node_to_copy->left, node_map);
	new_node->right = deep_copy_helper(node_to_copy->right, node_map);
	return new_node;
}

Node* deep_copy(Node* node_to_copy)
{

	std::unordered_map<Node*, Node*> node_map;
	return deep_copy_helper(node_to_copy, node_map);
}


int main() {
	
	std::vector<Node*> created_nodes(10);
	for (int i = 0; i < 10; i++)
	{
		Node* new_node = new Node{};
		created_nodes[i] = new_node;
	}
	
	Node* head = created_nodes[4];
	head->left = created_nodes[2];
	head->left->right = created_nodes[1];
	head->right = created_nodes[7];
	head->right->left = created_nodes[6];
	
	Node* new_head = deep_copy(head);
	
	std::cout << head << " " << head->left << " " << head->right << std::endl;
	std::cout << new_head << " " << new_head->left << " " << new_head->right << std::endl;
	
	delete new_head->left->right;
	delete new_head->left;
	delete new_head->right->left;
	delete new_head->right;
	delete new_head;
	
	
	for (int i = 0; i < 10; i++)
	{
		delete created_nodes[i];
	}
	
}