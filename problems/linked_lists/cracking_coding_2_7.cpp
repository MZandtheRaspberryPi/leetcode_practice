/*
Identify if a linked list is a palindrome. singly or doubly? doubly easier, move one to back, then move in one by one. stop when they meet or pass.

if not, create new linked list.
move fast ptr and slow ptr. when fast at end, slow in middle.

insert elements into start of new linked list, so that the head eventually is the last and it is reversed. then go back and compare them.



 make head last one, and go to middle.
then go back to start and compare the two lists.

feedback from solution. options are to reverse the linnked list, compare first half to second.

other option, iterative approach. use a stack. find length. push stuff into stack till get to middle (handle odd and even lengths)
and then start popping off of stack and comparing.

other option, recursive.
recurse till get to middle. for this use length - 2 pass this each time recurse. when 0 or 1 in middle.
then return node reference to next, and compare current with the ref, and so on. return 2 values using struct, or bool ref.



*/
#include <stdio.h>
#include <vector>

struct Node
{
  char data;
	Node* next;
};



void print(Node* head)
{
	Node* runner = head;
	while (runner != nullptr)
	{
		printf("%c\n", runner->data);
		runner = runner->next;
	}
	printf("\n");
	
}

bool isPalindrome(Node* head)
{
	// a b b a
	if (head == nullptr)
	{
		return false;
	}
	
	Node* new_head = nullptr;
	Node* fast = head;
	Node* slow = head;
	while (fast != nullptr && fast->next != nullptr)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	
	// slow is at middle now
	
	Node* prev = slow;
	Node* tmp = slow->next;
	new_head = slow;
	new_head->next = nullptr;
	while (tmp != nullptr)
	{
		prev = new_head;
		new_head = tmp;
		tmp = tmp->next;
		new_head->next = prev;
	}
	
	// now new_head is start of new linked list with last entry the head and reversed
	
	slow = head;
	while (new_head != nullptr && slow != nullptr)
	{
		if (new_head->data != slow->data)
		{
			return false;
		}
		new_head = new_head->next;
		slow = slow->next;
	}
	
	return true;
	
}


int main()
{
	char arr[] = {'a', 'b', 'c', 'd', 'b', 'a'};
	std::vector<Node*> nodes_created;
	Node* head = nullptr;
	Node* runner = nullptr;
	for (char c : arr)
	{
		Node* new_node = new Node{};
		new_node->data = c;
		nodes_created.push_back(new_node);
		if (head == nullptr)
		{
			head = new_node;
			runner = new_node;
		}
		else
		{
			runner->next = new_node;
			runner = runner->next;
		}
		
	}

	print(head);
	bool palindrome = isPalindrome(head);
	printf("is palindrome: %d", palindrome);

	
	for (int i = 0; i < nodes_created.size(); i++)
	{
		delete nodes_created[i];
	}
	
	
	
}
