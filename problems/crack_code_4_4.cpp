// given a binary search tree, implement algo to create linked list of all nodes at each depth
// if you have tree with depth D youll have d linked lists

// create vector to hold linked lists for all depths
// make first linked list, just head of root
// while Q is not empty
// pop q, if nullptr continue
// else add left and right of curr to q.
// if q->val < q.back(), then stop linked list and add to vector. this means we're on a new depth layer. set head to nullptr.
// else if head is nullptr set curr to head 
// else, set head next to curr, set head to curr.
// breadth first search, so want to use a queue. add left and right of curr to queue.
// for linked list, when left of cur is less than 

// visit first node, make into own linked list

#include<vector>
#include<queue>

template<typename T>
struct Node {
	T val;
	Node<T>* left;
	Node<T>* right;

	~Node() {
		delete left;
		delete right;
	}

};

template<typename T>
Node<T>* createBinSearchTree(T* arr, int start, int end) {
	if (end < start) {
		return nullptr;
	}

	int midpoint = (end + start) / 2;
	Node<T>* n = new Node<T>{};
	n->val = arr[midpoint];
	n->left = createBinSearchTree(arr, start, midpoint - 1);
	n->right = createBinSearchTree(arr, midpoint + 1, end);
	
	return n;
	
}

template<typename T>
Node<T>* createBinSearchTree(T* arr, int arrSize) {
	return createBinSearchTree(arr, 0, arrSize - 1);
}

template<typename T>
struct LinkedNode {
	LinkedNode* next = nullptr;
	T val;
	
	LinkedNode(T val): val(val) {
	}

	~LinkedNode() {
		delete next;
	}
};

template<typename T>
std::vector<LinkedNode<T>*> createLL(Node<T>* root) {
	std::vector<LinkedNode<T>*> listVect;
	LinkedNode<T>* origHead = new LinkedNode<T>{root->val};
	std::queue<Node<T>*> q;
	
	LinkedNode<T>* prev = origHead;
	
	q.push(root->left);
	q.push(root->right);
	
	LinkedNode<T>* currLinked;
	
	while (!q.empty()) {
		Node<T>* curr = q.front();
		q.pop();
		
		if (curr == nullptr) {
			continue;
		}
		
		q.push(curr->left);
		q.push(curr->right);
		
		currLinked = new LinkedNode<T>{curr->val};
		
		// we moved to a new depth
		if (curr->val < prev->val) {
			listVect.push_back(origHead);
			origHead = currLinked;
			prev = currLinked;
		}
		else {
			prev->next = currLinked;
			prev = currLinked;
		}
	}
	listVect.push_back(origHead);
	
	return listVect;
}

int main() {
	
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int arrSize = sizeof(arr)/sizeof(arr[0]);
	Node<int>* head = createBinSearchTree(arr, arrSize);
	
	std::vector<LinkedNode<int>*> depthVect = createLL(head);
}