// implement an algo to delete aa node in hte middle of a singly linked list given only access to that node
// ex: input node c from linked list a ->b->c->d->e
// nothing returned, but new list looks like a->b->d->e

#include<stdio.h>

struct Node{
	
	Node(int data): data(data) {
	}

	int data;
	Node* next = nullptr;
	
};

bool deleteFromLinkedList(Node* nodeD) {
	// don't have access to start, so copy from next node and delete this one
	if (nodeD == NULL || nodeD->next == NULL) {
		return false;
	}
	nodeD->data = nodeD->next->data;
	nodeD->next = nodeD->next->next;
	return true;
}

int main() {
	
	Node node0 = Node{0};
	Node node1 = Node{1};
	Node node2 = Node{2};
	Node node3 = Node{3};
	Node node4 = Node{4};
	
	node0.next = &node1;
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	
	Node* n = &node0;
	while (n->next != NULL) {
		printf("%d\n", n->data);
		n = n->next;
	}
	printf("%d\n", n->data);
	
	deleteFromLinkedList(&node3);
	
	n = &node0;
	while (n->next != NULL) {
		printf("%d\n", n->data);
		n = n->next;
	}
	printf("%d\n", n->data);

}