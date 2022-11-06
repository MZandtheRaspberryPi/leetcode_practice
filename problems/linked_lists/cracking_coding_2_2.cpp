/*
implement an algo to find the kth to last element in a linked list

use ptr, move through linked list and keep track of k last elements. stop and return.
time O(N), space O(k).

Or, use fast and slow ptr. keep count for each.
when fast ptr at end, move slow to end count - k.
time O(N), space O(1).

another option is the recusive solution, passing a counter by reference. this is less lines of code, but at cost of O(N) storage to store
recursive calls.

didnt ask if k = 1 was last element, or element before last element. chose element before last, but should have clarified.
*/

#include <stdio.h>

struct Node
{
	int data;
	Node* next;
	
};

Node* findKthToEnd(Node* head, int k)
{
	if (head == nullptr || head->next == nullptr)
	{
		return nullptr;
	}
	
	
	Node* fast, *slow;
	fast = slow = head;
	int slow_count = 1;
	int fast_count = 1;

	while (fast != nullptr && fast->next != nullptr)
	{
		fast = fast->next->next;
		slow = slow->next;
		fast_count += 2;
		slow_count += 1;
	}
	
	int slow_target = fast_count - k;

	while(slow_count < slow_target)
	{
		slow = slow->next;
		slow_count++;
	}
	return slow;
	
}

Node* findKthToEndRecursive(Node* runner, const int& k, int& counter)
{
	
	if (runner->next == nullptr)
	{
		return nullptr;
	}
	
	Node* ret = findKthToEndRecursive(runner->next, k, counter);
	counter++;
	
	if (counter == k)
	{
		return runner;
	}
	
	return ret;
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
	
	printLL(head);
	
	Node* kth_node = findKthToEnd(head, 2);
	printf("2nd node: %d\n", kth_node->data);
	
	int counter = 0;
	kth_node = findKthToEndRecursive(head, 2, counter);
	printf("2nd node: %d\n", kth_node->data);
	
		
	runner = head;
	while(runner != nullptr)
	{
		Node* node_to_del = runner;
		runner = runner->next;
		delete node_to_del;
	}
	
	
}