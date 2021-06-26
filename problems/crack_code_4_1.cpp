// implement a function to check if binary tree is balanced.
// for this question, balanced is such that heights of two subtrees of any node never differ by more than one.
// take root as base, calculate height for left and right node. compare, if they're more than 1 different, return -1.
// else, do the same thing for the left node and the right node.

// not super efficient as in each node we recurse through the whole tree so if tree has n nodes, for each node we check n nodes
// hence, n^2 in time complexity, and due to recursion we store whole call stack in space complexity
#include<algorithm> // max
#include<cmath> // abs
#include<queue>
#include<stdio.h>

template <typename T>
struct Node{
	Node* left;
	Node* right;
	T data;
};

template <typename T>
int calcHeight(Node<T>* root) {
	if (root == nullptr) return 0;
	return std::max(calcHeight(root->left), calcHeight(root->right)) + 1;
}

template <typename T>
bool checkBalance(Node<T>* root) {
	if (root == nullptr) return true; // base case
	
	int heightDiff = calcHeight(root->left) - calcHeight(root->right);
	if (std::abs(heightDiff) > 1) {
		return false;
	}
	else {
		// recurse
		return checkBalance(root->left) && checkBalance(root->right);
	}

}

// an alternative proposal, we could do the check for tree equality in the calcHeight function
// if node isn't balanced, then return -1. then add a check for -1 first in the function and if you get it,
// return it to break out of function stack.
// for this, we only have to check whole tree once, so O(N) time complexity. O(logn) in space complexity

template <typename T>
int calcHeightOptimal(Node<T>* root) {
	if (root == nullptr) return 0;
	
	// check if left balanced
	int leftHeight = calcHeightOptimal(root->left);
	if (leftHeight == -1) return -1;
	
	int rightHeight = calcHeightOptimal(root->right);
	if (rightHeight == -1) return -1;
	
	// check if curr node balanced
	int heightDiff = leftHeight - rightHeight;
	if (std::abs(heightDiff) > 1) {
		return -1; // not balanced
	}
	else {
		// return height
		return std::max(leftHeight, rightHeight);
	}
}

template <typename T>
bool isBalancedOptimal(Node<T>* root) {
	if (checkHeight(root) == -1) {
		return false;
	}
	else {
		return true;
	}
}

// example in order algo, DFS
template <typename T>
void inOrderSearch(Node<T>* root) {
	if (root == nullptr) return;
	inOrderSearch(root->left);
	printf("%d\n", root->data);
	inOrderSearch(root->right);
}

template <typename T>
void preOrderSearch(Node<T>* root) {
	if (root == nullptr) return;
	printf("%d\n", root->data);
	preOrderSearch(root->left);
	preOrderSearch(root->right);
}

// example post order algo, DFS
template <typename T>
void postOrderSearch(Node<T>* root) {
	if (root == nullptr) return;
	postOrderSearch(root->left);
	postOrderSearch(root->right);
	printf("%d\n", root->data);
}


// example BFS algo
template <typename T>
void dfsSearch(Node<T>* root) {
	std::queue<Node<T>*> q = std::queue<Node<T>*>{};
	q.push(root);
	while (!q.empty()) {
		root = q.front();
		q.pop();
		printf("%d\n", root->data);
		if (root->left != nullptr) q.push(root->left);
		if (root->right != nullptr) q.push(root->right);
	}
}

int main(){
	Node<int>* node0 = new Node<int>{};
	node0->data = 0;
	Node<int>* node1 = new Node<int>{};
	node1->data = 1;
	Node<int>* node2 = new Node<int>{};
	node2->data = 2;
	Node<int>* node4 = new Node<int>{};
	node4->data = 4;
	Node<int>* node5 = new Node<int>{};
	node5->data = 5;
	
	node0->left = node1;
	node0->right = node2;
	node1->left = node4;
	node4->left = node5;
	
	printf("%d\n", checkBalance(node0));
	printf("%d\n", checkBalance(node0));
	printf("\n");
	
	inOrderSearch(node0);
	printf("\n");
	preOrderSearch(node0);
	printf("\n");
	postOrderSearch(node0);
	printf("\n");
	dfsSearch(node0);


	delete node4;
	delete node2;
	delete node1;
	delete node0;
	delete node5;


}