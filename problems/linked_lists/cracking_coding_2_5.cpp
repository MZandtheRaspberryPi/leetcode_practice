/*
you have two numbers represented by a linked list
each node contains a digit
digits stored in reverse order, so 1s digit is at head of list

write function that adds 2 numbers and returns sum as linked list

ex:
7 - 1 - 6 5 - 9 - 2, 617 plus 295 output 2 / 1 / 9 that is 912.

suppose digits stored in forward order, repeat above problem.

6 1 7 + 2 9 5 617+295, = 9 1 2, 912.

make result Node*.
make runner = result.

make int intermediate_sum = 0;
and digits counter = 0.
while head1 isnt nullptr or head2 isnt nullptr
if head 1
take data from linked list and add to intermediate_sum.
if head 2
same

make new node set data to intermediate_sum % 10.
set runner->next to that. if runner isnt nullptr, else that.
set intermediate_sum to intermediate_sum / 10.

return head.
time complexity O(N), storage complexity, O(1) for processing, but will store result in new linked list so O(N + 1) where N is max length of input list


if stored in forward order, singly or double link? assume single link.

make node* for runner1, runner2, prev, result head.
runner1 = prev1->next.
runner2 same.

recursive function where pass node1 node2 ref for carry.
if both nullptr, carry = 0. return.
else if node1 not nullptr subnode = next. same for two.
recurse for subnodes.
tmp = 0;
add runner1 data and runner2 data. add carry.
make new node. set to tmp % 10. set resultnode next to new node. add new node to vector.
set carry to tmp / 10. return.



will operate in O(N) time, but use O(N) space to store recursive calls, as well as make new nodes for result.

feedback, could have gone recursive on first one too.

on second, if one is shorter than other, we need to padd with zeros.


*/
#include <cmath>
#include <stdio.h>
#include <vector>

struct Node
{
  int data;
	Node* next;
};


Node* getBackwardLLFromInt(int number, std::vector<Node*>& nodes_created)
{
	Node* head = nullptr;
	Node* runner = nullptr;
	while (number > 0)
	{
		Node* new_node = new Node{};
		nodes_created.push_back(new_node);
		new_node->data = number % 10;
		number /= 10;
		if (runner == nullptr)
		{
			head = new_node;
			runner = head;
		}
		else
		{
			runner->next = new_node;
			runner = runner->next;
		}
	}
	return head;
}

void print(Node* head)
{
	Node* runner = head;
	while (runner != nullptr)
	{
		printf("%d\n", runner->data);
		runner = runner->next;
	}
	printf("\n");
	
}



Node* addLLNums(Node* head1, Node* head2, std::vector<Node*>& nodes_created)
{
	Node* result_head = nullptr;
	Node* result_runner = result_head;
	Node* runner1 = head1;
  Node* runner2 = head2;
	int intermediate_sum = 0;
	while (runner1 != nullptr || runner2 != nullptr || intermediate_sum > 0)
	{
		if (runner1 != nullptr)
		{
			intermediate_sum += runner1->data;
			runner1 = runner1->next;
		}
		
		if (runner2 != nullptr)
		{
			intermediate_sum += runner2->data;
			runner2 = runner2->next;
		}
		
		Node* new_node = new Node{};
		nodes_created.push_back(new_node);
		new_node->data = intermediate_sum % 10;
		intermediate_sum /= 10;
		
		if (result_runner == nullptr)
		{
			result_head = new_node;
			result_runner = new_node;
		}
		else
		{
			result_runner->next = new_node;
			result_runner = result_runner->next;
		}
	}
	return result_head;
}

void addLLDigits(Node* runner1, Node* runner2, std::vector<Node*>& nodes_created, int& carry, Node* result_head)
{
	if (runner1 == nullptr && runner2 == nullptr)
	{
		carry = 0;
		return;
	}
	
	Node* sub_node_1, * sub_node_2;
	sub_node_1 = sub_node_2 = nullptr;
	if (runner1 != nullptr)
	{
		sub_node_1 = runner1->next;
	}
	
	if (runner2 != nullptr)
	{
		sub_node_2 = runner2->next;
	}
	
	// recurse
	addLLDigits(sub_node_1, sub_node_2, nodes_created, carry, result_head);
	
	int tmp = 0;
	if (runner1 != nullptr)
	{
		tmp += runner1->data;
	}
	
	if (runner2 != nullptr)
	{
		tmp += runner2->data;
	}
	
	tmp += carry;
	
	Node* new_node = new Node{};
	nodes_created.push_back(new_node);
	
	new_node->data = tmp % 10;
	carry = tmp / 10;
	
	new_node->next = result_head->next;
	result_head->next = new_node;
}

int countLL(Node* head)
{
	int len = 0;
	while (head != nullptr)
	{
		len++;
		head = head->next;
	}
	return len;
}

Node* padLL(Node* head, int len, std::vector<Node*>& nodes_created)
{
	int actual_len = 1;
	Node* runner = head;
	while (runner->next != nullptr)
	{
		runner = runner->next;
		actual_len++;
	}
	
	while (actual_len < len)
	{
		Node* new_node = new Node{};
		nodes_created.push_back(new_node);
		new_node->data = 0;
		new_node->next = head;
		head = new_node;
		actual_len++;
	}
	
	return head;
	
}


Node* addForwardLLNums(Node* head1, Node* head2, std::vector<Node*>& nodes_created)
{
	Node* result_head = new Node{};
	nodes_created.push_back(result_head);
	
	int len1 = countLL(head1);
	int len2 = countLL(head2);
	
	int max_len = len1 > len2 ? len1 : len2;
	head1 = padLL(head1, max_len, nodes_created);
	head2 = padLL(head2, max_len, nodes_created);
	
	len1 = countLL(head1);
	len2 = countLL(head2);
	
	int carry = 0;
	
	addLLDigits(head1, head2, nodes_created, carry, result_head);
	
	// check for overflow
	if (carry > 0)
	{
		result_head->data = carry;
		return result_head;
	}
	else
	{
		return result_head->next;
	}
}

Node* getFLLFromInt(int number, std::vector<Node*>& nodes_created)
{
	Node* head = nullptr;
	Node* runner = nullptr;
	int digit_ctr = 1;
	int result = number / pow(10, digit_ctr);
	while (result > 0)
	{
		digit_ctr++;
		result = number / pow(10, digit_ctr);
	}
	
	// 643,945 would have 6 returned. 1,000,000.
	while (digit_ctr > 0)
	{
		Node* new_node = new Node{};
		nodes_created.push_back(new_node);
		new_node->data = number / pow(10, digit_ctr - 1);
		number = number - (new_node->data * pow(10, digit_ctr - 1));
		digit_ctr--;
		
		if (head == nullptr)
		{
			head = new_node;
			runner = new_node;
		}
		else
		{
			runner->next = new_node;
			runner = new_node;
		}
	}
	
	return head;
	
}




int main()
{
	std::vector<Node*> nodes_created;
	
	int num1 = 617;
	int num2 = 95;
	
	Node* head1 = getBackwardLLFromInt(num1, nodes_created);
	Node* head2 = getBackwardLLFromInt(num2, nodes_created);
	
	print(head1);
	print(head2);
	
	Node* result_head = addLLNums(head1, head2, nodes_created);
	print(result_head);
	
	head1 = getFLLFromInt(num1, nodes_created);
	head2 = getFLLFromInt(num2, nodes_created);
	
	print(head1);
	print(head2);
	
	result_head = addForwardLLNums(head1, head2, nodes_created);
	print(result_head);
	
	
	for (int i = 0; i < nodes_created.size(); i++)
	{
		delete nodes_created[i];
	}
	
	
	
}
