/*
write code to partition a linked list around a value x, such that all nodes less than x come
before all nodes greater than or equal to x

go through linked list, keep track of head and previous. if find a node with value less than x, set previous-> next to current->next.
set current_next -> head.
set head to current_next.

set previous to current.
set current to current->next.

time complexity O(N)
space complexity O(1)

another option, from solution:
can make two new lists, one for before and one for after.

keep track of before start,before end, after start, after end.
go through list and put nodes into these new lists.

then at the ned merge them together.

*/

#include <stdio.h>

struct Node
{
	int data;
	Node* next;
	
};

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


void partitionLinkedList(Node*& head, int x)
{
	Node* prev = head;
	Node* runner = head->next;
	
	while (runner != nullptr)
	{
		if (runner->data < x)
		{
			prev->next = runner->next;
			runner->next = head;
			head = runner;
			runner = prev->next;
		}
		else
		{
			prev = runner;
			runner = runner->next;
		}
		//printLL(head);
	}
}

int main()
{
	Node* head = new Node{};
	head->data = 0;
	Node* runner = head;
	for (int i = 1; i < 11; i++)
	{
		Node* new_node = new Node{};
		new_node->data = i % 4;
		runner->next = new_node;
		runner = runner->next;
	}
	
	printLL(head);
	partitionLinkedList(head, 1);
	printLL(head);
	
		
	runner = head;
	while(runner != nullptr)
	{
		Node* node_to_del = runner;
		runner = runner->next;
		delete node_to_del;
	}
	
	
}