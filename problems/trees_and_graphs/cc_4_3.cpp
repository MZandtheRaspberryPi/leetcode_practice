/*

given sorted increasing order array write algo to create binary search tree with minimal height.

start in middle of arrya. move left and right pointers out each time.

set left_ptr to size/2. set right_ptr to set/2.
make a root node. set array[0] to data. put root into queue.
minus left_ptr. add right ptr.
for loop over array starting at 1, < size.
if queue has something in it, grab it. then make a new node, and set data to  data to left ptr and move left ptr left. then make a new node and set data to right ptr and move right ptr right.
then put left node and right node into the queue.



In time, this is O(N). In space, this is O(N) ish, depends how many leaves on each level.

feedback, this doesnt work as the tree gets bigger as you alternate left and right nodes and then hte order is messed up.
what we really want to do is take the middle of array as root, then the left node should take middle of left subarray as root.
this will ensure as the tree scales it works.


*/
#include <cmath>
#include <queue>
#include <stdio.h>
#include <vector>

struct TreeNode
{
	int data;
	TreeNode* left;
	TreeNode* right;
};

TreeNode* makeBinSearchTreeOptimal(const std::vector<int>& sorted_arr, int start, int end)
{
	if (end < start)
	{
		return nullptr;
	}
	int mid = (start + end) / 2;
	TreeNode* new_node = new TreeNode{};
	new_node->data = sorted_arr[mid];
	new_node->left = makeBinSearchTreeOptimal(sorted_arr, start, mid - 1);
	new_node->right = makeBinSearchTreeOptimal(sorted_arr, mid + 1, end);
	return new_node;
	
}

TreeNode* makeBinSearchTree(const std::vector<int>& sorted_arr)
{
	TreeNode* root = new TreeNode{};
	int left_ptr, right_ptr;
	left_ptr = right_ptr = sorted_arr.size() / 2;
	root->data = sorted_arr[left_ptr];
	left_ptr--;
	right_ptr++;
	std::queue<TreeNode*> node_q;
	node_q.push(root);
	while (left_ptr >= 0 || right_ptr < sorted_arr.size())
	{
		TreeNode* cur_root = node_q.front();
		node_q.pop();
		
		if (left_ptr >= 0)
		{
			TreeNode* new_left = new TreeNode{};
			cur_root->left = new_left;
			new_left->data = sorted_arr[left_ptr];
			left_ptr--;
			node_q.push(new_left);
		}
		
		if (right_ptr < sorted_arr.size())
		{
			TreeNode* new_right = new TreeNode{};
			cur_root->right = new_right;
			new_right->data = sorted_arr[right_ptr];
			right_ptr++;
			node_q.push(new_right);
		}
	}
	
	return root;
}

void printAndDeleteTree(TreeNode* root)
{
	std::queue<TreeNode*> node_q;
	node_q.push(root);
	int count = 1;
	while (node_q.size() > 0)
	{
		TreeNode* node = node_q.front();
		node_q.pop();
		
		if (node != nullptr)
		{
			printf("%d ", node->data);
			node_q.push(node->left);
			node_q.push(node->right);
			delete node;
			count++;
			
			double power_of_2_orig = log2(count);
			int power_of_2_int = static_cast<int>(power_of_2_orig);
			double power_of_2_double = static_cast<double>(power_of_2_int);
			if (power_of_2_double == power_of_2_orig)
			{
				printf("\n");
			}
		}
	}
}


int main()
{
	std::vector<int> sorted_arr;
	for (int i = 0; i < 50; i++)
	{
		sorted_arr.push_back(i);
	}
	
	TreeNode* root = makeBinSearchTreeOptimal(sorted_arr, 0, sorted_arr.size() - 1);
	printAndDeleteTree(root);
	
}