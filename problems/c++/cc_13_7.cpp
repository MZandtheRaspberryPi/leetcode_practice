/*
Write a method that takes a pointer to a node structure as a parameter
and returns a complete copy of the passed in datastructure. the node data structure
contains two pointers to other Nodes.

can use malloc(size)
as well as memcpy(dst, src, size)

feedback from solution, was totally off here. forgot had to recurse in to really update copy.

so new plan:
we go to the input. we create a new copy of it. we go to left, and then to right, recursively and so on.
but we dont want to get stuck in infinite loop.
so each time we visit a node, we check if its in a map, unordered map for constant look up. if it is, we skip it.
if it isnt we do it and then visit its left and right.


*/

#include <iostream>
#include <unordered_map>

struct Node {
	Node* left;
	Node* right;
};

Node* deep_copy(Node* cur, std::unordered_map<Node*, Node*>& nodes_visited)
{
	if (cur == nullptr)
	{
		return nullptr;
	}
	
	if (nodes_visited.find(cur) == nodes_visited.end())
	{
		Node* new_node = new Node();
		nodes_visited[cur] = new_node; // map current before traversing links
		new_node->left = deep_copy(cur->left, nodes_visited);
		new_node->right = deep_copy(cur->right, nodes_visited);
		return new_node;
	}
	else
	{
		return nodes_visited[cur];
	}
}

int main()
{
	Node* node = new Node();
	std::unordered_map<Node*, Node*> nodes_visited;
	Node* new_node = deep_copy(node, nodes_visited);
	
	std::cout << node << std::endl;
	std::cout << new_node << std::endl;
	
	delete node;
	delete new_node;
	
}