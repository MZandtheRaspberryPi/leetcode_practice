/*
write code to remove duplicates from unsorted linked list.
how to do it if temp buffer not allowed?

if use buffer, use a map.
set prev to current, and set runner to current->next.
and iterate through list till runner is nullptr.
if entry isnt in map, add it and set value to 1. set previous to runner. else if in map, set prev next to runner next. dont touch previous.
set runner to runner->next.
O(N) time complexity, gotta go through whole list
worst case space complexity, if ever item unique, is O(N)

if cant use a temporary buffer, could sort linked list, and then go through and delete if previous same as current.
This would be O(nlogn) time, to sort, and then some space complexity for storage algo, likely O(N).

a simpler approach would be to use two runners. one to keep track of place, and one to search all other entries for that value.
time O(N^2), space O(1).


*/

#include <map>
#include <stdio.h>

struct Node
{
	int data;
	Node* next;
	
};

bool isEntryInMap(const std::map<int, int>& map_to_check, const int& val)
{
	return map_to_check.find(val) != map_to_check.end();
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

void deleteDuplicates(Node* head)
{
	if (head == nullptr)
	{
		return;
	}
	
	std::map<int, int> entry_count;
	Node* prev = head;
	Node* runner = head->next;
	entry_count[prev->data] = 1;
	
	while (runner != nullptr)
	{
		if (isEntryInMap(entry_count, runner->data))
		{
			prev->next = runner->next;
			Node* node_to_del = runner;
			runner = runner->next;
			delete node_to_del;
		}
		else
		{
			entry_count[runner->data] = 1;
			prev = runner;
			runner = runner->next;
		}
	}
}

void deleteDuplicatesNoBuffer(Node* head)
{
	if (head == nullptr)
	{
		return;
	}
	Node* searcher;
	Node* searcher_prev;
	
	Node* runner = head;
	
	while (runner != nullptr)
	{
		searcher = runner->next;
		searcher_prev = runner;
		
		while (searcher != nullptr)
		{
			if (searcher->data == runner->data)
			{
				searcher_prev->next = searcher->next;
				Node* node_to_del = searcher;
				searcher = searcher->next;
				delete node_to_del;
			}
			else
			{
				searcher_prev = searcher;
				searcher = searcher->next;
			}
		}
		
		runner = runner->next;
	}
	
	
}

int main()
{
	
	int arr[] = {4, 5, 7, 1, 2, 4, 9, 10, 15, 20, 5, 10};
	int arr_size = sizeof(arr)/sizeof(arr[0]);
	
	Node* head = new Node{};
	head->data = arr[0];
	Node* runner = head;
	for (int i = 1; i < arr_size; i++)
	{
		Node* next = new Node{};
		next->data = arr[i];
		runner->next = next;
		runner = runner->next;
	}
	
	printLL(head);
	//deleteDuplicates(head);
	deleteDuplicatesNoBuffer(head);
	printLL(head);
	
	runner = head;
	while (runner != nullptr)
	{
		Node* prev = runner;
		runner = runner->next;
		delete prev;
	}	
}