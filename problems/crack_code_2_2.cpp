// implement an alogirthm to find the kth to last element of a singly linked list

#include<stdio.h>

class Node {
public:
	Node(int data) : data(data) {

	}

	int data;
	Node* next;

};

int findKLastElement(Node* head, int k) {
	// we could loop through linked list, keep track of how many elements in an int
	// when we get to end, we subtract k from that int
	// then we loop again subtracting 1 each time we loop
	// when the int hits zero thats the one we want so we grab it and return it
	// this would be O(N) in time complexity
	// this would be O(1) in storage complexity
	int i = 0;
	Node* n = head;
	while (n->next != NULL) {
		i++;
		n = n->next;
	}
	i -= k;
	n = head;
	while (n->next != NULL) {
		i--;
		if (i < 0) {
			break;
		}
		n = n->next;
	}
	return n->data;
}

int main() {
	
	Node node0 = Node{0};
	Node node1 = Node{1};
	Node node2 = Node{2};
	Node node3 = Node{3};
	Node node4 = Node{ 4 };
	Node node5 = Node{ 5 };
	Node node6 = Node{ 6 };
	Node node7 = Node{ 7 };
	node0.next = &node1;
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = &node7;

	Node* n = &node0;
	while (n->next != NULL) {
		printf("%d\n", n->data);
		n = n->next;
	}
	printf("%d\n", n->data);
	printf("2nd from last: %d", findKLastElement(&node0, 2));

}