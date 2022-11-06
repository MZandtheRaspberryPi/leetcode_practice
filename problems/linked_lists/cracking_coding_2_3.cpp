/*
implement an algo to delete node in middle of linked list, singly, given only access
to that node. so, a / b / c/ d/ e , input c
nothing returned, but new list looks like 
a / b / d / e

for this, have to copy data from next node to current node, and then delete that next node.

if the node is the last node, cant do it as singly linked list.




*/

#include <stdio.h>

struct Node
{
	int data;
	Node* next;
	
};

int deleteNode(Node* node_to_del)
{
	if (node_to_del->next == nullptr)
	{
		return 1;
	}
	
	node_to_del->data = node_to_del->next->data;
	Node* delete_this_node = node_to_del->next;
	node_to_del->next = node_to_del->next->next;
	delete delete_this_node;
	return 0;
	
}



void printLL(Node* head)
{
	Node* runner = head;
	while (runner != nullptr)
	{
		printf("%d\n", runner->data);
		runner = runner->next;
	}
	printf("\n");
}


int main()
{
	Node* head = new Node{};
	head->data = 0;
	Node* runner = head;
	for (int i = 1; i < 11; i++)
	{
		Node* new_node = new Node{};
		new_node->data = i;
		runner->next = new_node;
		runner = runner->next;
	}
	
	runner = head;
	for (int i = 0; i < 3; i++)
	{
		runner = runner->next;
	}
	
	printLL(head);
	
	printf("runner: %d\n", runner->data);
	int success = deleteNode(runner);
	printLL(head);
	
		
	runner = head;
	while(runner != nullptr)
	{
		Node* node_to_del = runner;
		runner = runner->next;
		delete node_to_del;
	}
	
	
}