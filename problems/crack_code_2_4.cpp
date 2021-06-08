// write code to partition a linked list around a value x, suc that all nodes
// less than x come before all nodes greater than or equal to x

#include<stdio.h>
#include<vector>
using namespace std;

struct Node {
	Node(int data): data(data) {
	}
	
	int data;
	Node* next = nullptr;
	
	vector<Node*> moveToStart(Node* start, Node* previous){
		// function to move to start and return next element to check
		vector<Node*> returnVect(3, nullptr);
		// new start
		returnVect[0] = this;
		// next to check
		returnVect[1] = this->next;
		// previous
		returnVect[2] = previous;
		previous->next = this->next;
		this->next = start;
		return returnVect;
	}
	
	vector<Node*> moveToEnd(Node* end, Node* previous){
		// function to move to end and return next element to check
		vector<Node*> returnVect(3, nullptr);
		// new end
		returnVect[0] = this;
		// next to check
		if (previous != nullptr) {
			previous->next = this->next;
			// next to check
			returnVect[1] = previous->next;
			// previous
			returnVect[2] = previous;
		}
		else {
			returnVect[1] = this->next;
		}
		this->next = nullptr;
		end->next = this;
		return returnVect;
	
	}

};


Node* partitionLinkedList(Node* head, int x) {
	if (head == NULL || head->next == NULL) {
		return head;
	}
	// could loop through list once to find the end of the list
	// then loop through again and put anything below x at the start
	// and anything above x at the end
	// this will be O(N) in time complexity, and O(1) in space complexity
	Node* end = head;
	Node* n = head;
	// below won't have last node counted
	int listLength = 0;
	while (end->next != NULL) {
		listLength++;
		end = end->next;
	}
	
	Node* previous = nullptr;
	vector<Node*> returnVect(3, nullptr);
	
	while (n->next != nullptr && listLength != 0) {
		listLength--;
		Node* nCopy = n;
		if (n->data > x) {
			returnVect = n->moveToEnd(end, previous);
			end = returnVect[0];
			n = returnVect[1];
			previous = returnVect[2];
			// if we're here, we just put the start to the end
			// so reset the starting bit
			if (previous == nullptr) {
				head = n;
			}
			continue;
		}
		else if (n->data < x) {
			returnVect = n->moveToStart(head, previous);
			head = returnVect[0];
			n = returnVect[1];
			previous = returnVect[2];
			continue;
		}
		else {
			previous = n;
			n = n->next;
		}
	}

	if (n->data < x) {
		returnVect = n->moveToStart(head, previous);
		head = returnVect[0];
	}
	
	return head;
}

class ListNode {
public:
	int data;
	ListNode* next;

	void setNext(ListNode* next) {
		this->next = next;
	}

	ListNode* getNext() {
		return this->next;
	}
};


ListNode* partitionLinkedListOpt(ListNode* head, int x) {
	// create two different link lists, one for elemenets less than x, one greater than or equal to x
	// iterate through list insert element into b/f list or after list. 
	// when reach end and completed splitting, merge the two lists
	ListNode* beforeStart = nullptr;
	ListNode* beforeEnd = nullptr;
	ListNode* afterStart = nullptr;
	ListNode* afterEnd = nullptr;
	
	while (head != nullptr) {
		ListNode* next = head->next;
		head->next = nullptr;
		if (head->data < x) {
			// insert node into end of before list
			if (beforeStart == nullptr) {
				beforeStart = head;
				beforeEnd = beforeStart;
			} else {
				// update the value of the current end to be the next one
				beforeEnd->next = head;
				// then move the pointer to point to the new end
				beforeEnd = head;
			}
			
		} else {
			// insert node into end of after list
			if (afterStart == nullptr) {
				afterStart = head;
				afterEnd = afterStart;
			} else {
				// update the value of the current end to be the next one
				afterEnd->next = head;
				// then move the pointer to point to the new end
				afterEnd = head;
			}
		}
		head = next;
	}
	
	if (beforeStart == nullptr) {
		return afterStart;
	}
	
	// merge before and after list
	beforeEnd->next = afterStart;
	return beforeStart;
}

ListNode* partitionLinkedListOpt2(ListNode* head, int x) {
	// create a before list
	// create an after list
	// loop through given list, remember what's next
	// as we'll be changing it in place
	// and add to start of before list or start of after list
	// from there, if before list is nullptr, return after list
	// else, loop over before list and find the end, then set that to be start of after list
	// return pointer to before list
	ListNode* beforeStart = nullptr;
	ListNode* afterStart = nullptr;
	ListNode* next = nullptr;
	while (head->next != nullptr) {
		next = head->next;

		if (head->data < x) {
			head->next = beforeStart;
			beforeStart = head;
		}
		else {
			head->next = afterStart;
			afterStart = head;
		}

		head = next;	
	}

	if (beforeStart == nullptr) {
		return afterStart;
	}

	head = beforeStart;
	while (beforeStart->next != nullptr) {
		beforeStart = beforeStart->next;
	}
	beforeStart->next = afterStart;

	return head;


}

int main() {
	Node node0 = Node{2};
	Node node1 = Node{1};
	Node node2 = Node{3};
	Node node3 = Node{0};
	Node node4 = Node{5};
	
	node0.next = &node1;
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	
	Node* n = &node0;
	while (n->next != nullptr) {
		printf("%d\n", n->data);
		n = n->next;
	}
	printf("%d\n", n->data);
	printf("2 val is %d\n", node2.data);
	vector<Node*> returnVect(2, nullptr);
	returnVect = node2.moveToEnd(&node4, &node1);
	printf("moved 2 to end\n");
	n = &node0;
	while (n->next != nullptr) {
		printf("%d\n", n->data);
		n = n->next;
	}
	printf("%d\n", n->data);
	printf("re-arranging\n");
	
	n = partitionLinkedList(&node0, 1);
	
	while (n->next != nullptr) {
		printf("%d\n", n->data);
		n = n->next;
	}
	printf("%d\n", n->data);

	// resetting list
	printf("list for opt run:\n");
	ListNode node5 = ListNode{};
	ListNode node6 = ListNode{};
	ListNode node7 = ListNode{};
	ListNode node8 = ListNode{};
	ListNode node9 = ListNode{};
	node5.data = 4;
	node6.data = 5;
	node7.data = 0;
	node8.data = 1;
	node9.data = 0;

	node5.next = &node6;
	node6.next = &node7;
	node7.next = &node8;
	node8.next = &node9;

	ListNode* n2 = &node5;


	while (n2->next != nullptr) {
		printf("%d\n", n2->data);
		n2 = n2->next;
	}
	printf("%d\n", n2->data);


	n2 = partitionLinkedListOpt(&node5, 1);
	printf("Output:\n");

	while (n2->next != nullptr) {
		printf("%d\n", n2->data);
		n2 = n2->next;
	}
	printf("%d\n", n2->data);
}