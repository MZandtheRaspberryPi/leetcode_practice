/*
describe implement a stack with pop push min, and all run in O(1) time.

we need to keep track of the min as we add stuff and it changes. to save all the prior mins as well.
we could add another element to datastructure to keep min. then we take O(N) space.

or, we could keep a second stacks of mins, and then when we are popping check if value we are popping is the value in min stack.
if so, pop from second stack of mins too.


*/

#include <stdio.h>

struct Node
{
	int data;
	Node* next;
	
};

class StackWithMin
{
	public:
		~StackWithMin();
		int front();
		int pop();
		int push(int data);
		int min();
	private:
	  Node* head;
		Node* head_min;
};

StackWithMin::~StackWithMin()
{
	while (head != nullptr)
	{
		Node* node_to_del = head;
		head = head->next;
		delete node_to_del;
	}
	
	while (head_min != nullptr)
	{
		Node* node_to_del = head_min;
		head_min = head_min->next;
		delete node_to_del;
	}
}

int StackWithMin::front()
{
	if (head == nullptr)
	{
		return -1;
	}
	
	return head->data;
}

int StackWithMin::pop()
{
	if (head == nullptr)
	{
		return -1;
	}
	
	Node* current_top = head;
	head = head->next;
	if (head_min->data == current_top->data)
	{
		Node* current_min = head_min;
		head_min = head_min->next;
		delete current_min;
	}
	delete current_top;
	return 0;	
}

int StackWithMin::push(int data)
{
	// check if we need to update min
	if (head_min == nullptr)
	{
		head_min = new Node{};
		head_min->data = data;
	}
	else if (data < head_min->data)
	{
		Node* new_min = new Node{};
		new_min->data = data;
		new_min->next = head_min;
		head_min = new_min;
	}
	
	Node* new_node = new Node{};
	new_node->data = data;
	new_node->next = head;
	head = new_node;
	
	return 0;
	
}

int StackWithMin::min()
{
	// check if we need to update min
	if (head_min == nullptr)
	{
		return -1;
	}
	else
	{
		return head_min->data;
	}	
}



int main()
{
  StackWithMin min_stack = StackWithMin();
	min_stack.push(5);
	min_stack.push(2);
	printf("min after 5, 2, is: top: %d min: %d\n", min_stack.front(), min_stack.min());
	min_stack.push(6);
	printf("min after 5, 2, 6, is: top: %d min: %d\n", min_stack.front(), min_stack.min());
	min_stack.pop();
	printf("min after 5, 2, pop, is: top: %d min: %d\n", min_stack.front(), min_stack.min());
  

}