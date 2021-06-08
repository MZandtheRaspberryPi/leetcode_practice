// write code to remove duplicates from an unsorted linked list
// follw up: how would solve if temporary buffer not allowed?

#include<stdio.h>
#include<map>
#include<vector>
using namespace std;

class Node {
public:
	Node(int d) : data(d) {

	}

	void appendTail(int d) {
		Node* end = new Node{ d };
		Node* n = this;
		while (n->next != NULL) {
			n = n->next;
		}
		n->next = end;
	}

	Node* next = nullptr;
	int data;
};

void removeDupes2Pass(Node* head) {
	//  could go through list, use hash table to keep track of count of unique data values
	// then go through list once more and remove if key in map and count is greater than 1
	// to remove set next of previous node to the node after this one
	// set data to nullptr, de allocate current node in memory
	// else if in dict but its val in dict is 1 then 
	// this would be O(N) in time complexity, and O(N) in storage
	map<int, int> m;
	Node* n = head;
	m[head->data] = 1;
	while (n->next != NULL) {
		n = n->next;
		if (m.find(n->data) != m.end()) {
			m[n->data] += 1;
		}
		else {
			m[n->data] = 1;
		}
	}
	n = head;
	m[head->data] -= 1;
	Node* n_next;
	while (n->next != NULL) {
		// remove node
		n_next = n->next;
		if (m[n_next->data] > 1) {
			m[n_next->data] -= 1;
			n->next = n_next->next;
			delete n_next;
		}
		else {
			n = n->next;
		}
	}

}

void removeDupes(Node* head) {
	// similar to above, but does only one pass through as linked list
	map<int, int> m;
	Node* n = head;
	m[head->data] = 1;
	while (n->next != NULL) {
		Node* n_next = n->next;
		if (m.find(n_next->data) != m.end()) {
			n->next = n_next->next;
			delete n_next;
			continue;
		}
		else {
			m[n->next->data] = 1;
		}
		n = n->next;
	}
	n = head;
	m[head->data] -= 1;
	Node* n_next;
	while (n->next != NULL) {
		// remove node
		n_next = n->next;
		if (m[n_next->data] > 1) {
			m[n_next->data] -= 1;
			n->next = n_next->next;
			delete n_next;
		}
		else {
			n = n->next;
		}
	}
}

void removeAllInstances(Node* starting, int val) {
	Node * next_n;
	if (starting->next != NULL) {
		next_n = starting->next;
		if (next_n->data == val) {
			starting->next = next_n->next;
			delete next_n;
			if (starting->next == NULL) {
				return;
			}
			removeAllInstances(starting, val);
		}
		removeAllInstances(starting->next, val);
	}
}

void removeDupesNoStorage(Node* head) {
	// we could go through list, and for each data look through the entire list to see if it appears again, if it does, delete next appearence, and keep looking
	// this would have time complexity of O(N^2) and space complexity of O(N) as recursive calls into stack. we could go to space complexity O(1) if we didn't do
	// recursion
	Node* n = head;
	while (n->next != NULL) {
		n = n->next;
		removeAllInstances(n, n->data);
	}
}

void removeDupesNoStorageOptimal(Node* head) {
	// use two pointers, one to keep track of where we are currently, and another to go through rest of linked list and delete
	// repeats of current data
	// will use O(N^2) time complexity, and O(1) space complexity
	if (head == NULL) return;
	Node* current = head;
	while (current->next != NULL) {
		Node* runner = current;
		while (runner->next != NULL) {
			if (runner->next->data == current->data) {
				runner->next = runner->next->next;
				continue;
			}
			else {
				runner = runner->next;
			}
		}
		if (current->next != NULL) {
			current = current->next;
		}
	}
}

int main() {
	Node* head = new Node{ 0 };
	Node* n = head;
	
	vector<int> rep_vect = {0, 1, 1, 4, 4, 5, 6, 7, 7, 1, 5, 6, 10, 15};
	for (int i = 1; i < rep_vect.size(); i++) {
		n->appendTail(rep_vect[i]);
		n = n->next;
	}

	n = head;

	for (int i = 0; i < rep_vect.size(); i++) {
		printf("%d\n", n->data);
		n = n->next;
	}

	removeDupes(head);
	n = head;
	while (n->next != NULL) {
		printf("%d\n", n->data);
		n = n->next;
	}
	
	n = head;
	for (int i = 1; i < rep_vect.size(); i++) {
		n->appendTail(rep_vect[i]);
		n = n->next;
	}
	printf("\n");
	n = head;
	while (n->next != NULL) {
		printf("%d\n", n->data);
		n = n->next;
	}
	
	removeDupesNoStorage(head);
	printf("\n");
	n = head;
	while (n->next != NULL) {
		printf("%d\n", n->data);
		n = n->next;
	}

	printf("\nOptimal\n");
	n = head;
	for (int i = 1; i < rep_vect.size(); i++) {
		n->appendTail(rep_vect[i]);
		n = n->next;
	}
	n = head;
	while (n->next != NULL) {
		printf("%d\n", n->data);
		n = n->next;
	}
	printf("\n");
	n = head;
	removeDupesNoStorageOptimal(head);
	printf("\n");
	n = head;
	while (n->next != NULL) {
		printf("%d\n", n->data);
		n = n->next;
	}
	
};