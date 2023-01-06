/*
given binary tree in which each node contains value. desgin algo to print all paths which sum to given value.

note path can start or end anywhere in the tree.

perhaps keep track of each time you end a path somewhere. or alternatively, do DFS and keep a running sum. also keep a vector
of nodes we've visited. each time can traverse over to print when the sum lines up.

this would operate in O(N) time, O(M) space, where M is the longest path.

We could save some time by not going right if its greater than our sum, or would blow up our sum over the limit.

Note this answer assumed every path started at root, which isnt the case. If we could start anywhere, then what we should do is 
take the node we are on as the end of a path, and look upwards till we reach the sum, then keep going. as we could have negative numbers...
this means keeping track of the level we are on, for the lookup.

time complexity for this, if a node is at level r, we do r amount of work in looking up step.
guess at O(n logn)) since there are n nodes doing an avg of logn amount of work on each step.




*/

#include <stdio.h>
#include <vector>

struct Node
{
	int data;
	Node* left;
	Node* right;
};

void printVisitedNodes(const std::vector<Node*>& visited_nodes)
{
	for (Node* node : visited_nodes)
	{
		printf("%d\n", node->data);
	}
	printf("\n\n");
	
}

void printPaths(Node* node, std::vector<Node*>& visited_nodes, int& sum, const int target_sum)
{
	if (node == nullptr)
	{
		return;
	}
	
	sum += node->data;
	visited_nodes.push_back(node);
	if (sum > target_sum)
	{
		sum -= node->data;
		visited_nodes.pop_back();
		return;
	}
	else if (sum == target_sum)
	{
		printVisitedNodes(visited_nodes);
		visited_nodes.pop_back();
		sum -= node->data;
		return;
	}
	
	printPaths(node->left, visited_nodes, sum, target_sum);
	printPaths(node->right, visited_nodes, sum, target_sum);
	sum -= node->data;
	visited_nodes.pop_back();
}

void print(std::vector<Node*> nodes, int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		printf("%d\n", nodes[i]->data);
	}
	
	printf("\n\n");
}

void printPathsOptimal(Node* node, std::vector<Node*>& path, const int target_sum, int& level)
{
	if (node == nullptr)
	{
		return;
	}
	
	path.push_back(node);
	// look for paths that end on this node
	int tmp = 0;
	for (int i = level; i >= 0; i--)
	{
		tmp += path[i]->data;
		if (tmp == target_sum)
		{
			print(path, i, level);
		}
	}
	
	level++;
	printPathsOptimal(node->left, path, target_sum, level);
	printPathsOptimal(node->right, path, target_sum, level);
	path.pop_back();
	level--;
	
}

int main()
{
	std::vector<Node*> created_nodes;
	for (int i = 0; i < 10; i ++)
	{
		Node* new_node = new Node();
		new_node->data = i;
		created_nodes.push_back(new_node);
	}
	
	Node* root = created_nodes[4];
	root->left = created_nodes[2];
	root->left->left = created_nodes[1];
	root->right = created_nodes[7];
	root->left->right = created_nodes[3];
	
	root->right->left = created_nodes[6];
	root->right->right = created_nodes[8];
	std::vector<Node*> visited_nodes;
	int sum = 0;
	printf("6\n----\n");
	printPaths(root, visited_nodes, sum, 6);
	printf("17\n----\n");
	printPaths(root, visited_nodes, sum, 17);
	printf("2\n----\n");
	printPaths(root, visited_nodes, sum, 2);
	
	
	int level = 0;
		printf("6\n----\n");
	printPathsOptimal(root, visited_nodes, 6, level);
	printf("17\n----\n");
	printPathsOptimal(root, visited_nodes, 17, level);
	printf("2\n----\n");
	printPathsOptimal(root, visited_nodes, 2, level);
	
	for (Node* node : created_nodes)
	{
		delete node;
	}
	
}