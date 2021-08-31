// given a sorted (increasing order) array, write algo to create binary search tree
// w/ minimal height

// binary search tree is as go down tree imposes condition: 
// left nodes all contain key lesser than current
// right subtree only nodes w/ keys greater than current
// left and right subtree also binary search tree
// no dupe nodes

// provides ordering so we can do fast operations for search, max, min

#include<queue>

template<typename T>
struct Node {
	T val;
	Node* left = nullptr;
	Node* right = nullptr;

	~Node() {
		delete left;
		delete right;
	 }
};

template<typename T>
Node<T>* makeBinSearchTree(T* arr, T arrSize) {
	// note this method doesn't make a proper binary search tree
	// see the solution below for a proper function
	
	if (arr == nullptr || arrSize == 0) {
		return nullptr;
	}
	
	
	int nodeNum = 0;
	// create head
	Node<T>* head = new Node<T>{};
	head->val = *arr;
	nodeNum += 1;
	arr++;
	
	std::queue<Node<T>*> qCurr;
	std::queue<Node<T>*> qNext;
	std::queue<Node<T>*>* q1;
	std::queue<Node<T>*>* q2;
	qCurr.push(head);
	
	while (nodeNum <= arrSize) {
		
		// as for binary search tree, for all nodes left children less than or equal to current node
		if (qCurr.empty()) {
			q1 = &qNext;
			q2 = &qCurr;
		}
		else {
			q1 = &qCurr;
			q2 = &qNext;
		}
		
		while (!q1->empty()) {
			// getting next node to add children to
			Node<T>* currNode = q1->front();
			q1->pop();

			// adding left child
			Node<T>* left = new Node<T>{};
			left->val = *arr;
			arr++;
			nodeNum++;

			currNode->left = left;

			if (nodeNum >= arrSize) {
				break;
			}

			// adding right child
			Node<T>* right = new Node<T>{};
			right->val = *arr;
			arr++;
			nodeNum++;

			currNode->right = right;

			if (nodeNum >= arrSize) {
				break;
			}

			q2->push(left);
			q2->push(right);
		}
	}
	return head;
}

template<typename T>
void reverseArr(T* arr, T arrSize) {

	for (int i = arrSize - 1; i>= arrSize / 2; i--) {
		T iSwap = arrSize - 1 - i;
		// value we'll replace
		T tmp = arr[iSwap];
		arr[iSwap] = arr[i];
		arr[i] = tmp;
	}

}

Node<int>* createMinimalBST(int arr[], int start, int end) {
	if (end < start) {
		return nullptr;
	}

	int mid = (start + end) / 2;
	Node<int>* n = new Node<int>{};
	n->val = arr[mid];
	n->left = createMinimalBST(arr, start, mid - 1);
	n->right = createMinimalBST(arr, mid + 1, end);
	return n;
}

Node<int>* createMinimalBST(int arr[], int arrSize) {
	return createMinimalBST(arr, 0, arrSize - 1);
}

int main() {
	int node_count = 0;
	int sortedArr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int sortedArrSize = sizeof(sortedArr) / sizeof(sortedArr[0]);
	
	reverseArr(sortedArr, sortedArrSize);
	
	Node<int>* head = makeBinSearchTree(sortedArr, sortedArrSize);
	reverseArr(sortedArr, sortedArrSize);
	Node<int>* headOpt = createMinimalBST(sortedArr, sortedArrSize);

}