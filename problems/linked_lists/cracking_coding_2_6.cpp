/*
given a circular linked list, implement
algo which returns the node at beginning of loop
ex:
a b c d e c
output c.

fast runner, slow runner. non loop portion is k steps.

when slow runner enters looped portion after k steps. fast runner taken 2k steps, so is 2k - k steps, k steps, into looped portion
since k might be much larger than loop length, mod(k, loop_size). denote as K.

at each step get one step closer. so at this point
slow is 0 steps into loopfast is K steps into loop
slow is K steps behind fast.
fast is LOOP_SIZE - K steps behind slow runner
Fast catches up to slow at a rate of 1 step per unit of time.

fast is loop_size - K behind slow, fast runner catches up at a rate of 1 step per unit time.
meet after loop_size - k steps. there, will be k steps before head of loop. collission point.
collision spot and linked list head are k nodes from the start of the loop.
so if move one to linked list head, will each be k nodes from loop start. moving at same speed will make em collide at collission spot.

*/
#include <stdio.h>
#include <vector>

struct Node
{
  int data;
	Node* next;
};



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

Node* findLoopBeginning(Node* head)
{
	Node* slow = head->next;
	Node* fast = head->next->next;
	
	while (slow != fast)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	
	// we're at collission spot
	slow = head;
	while (slow != fast)
	{
		slow = slow->next;
		fast = fast->next;
	}
	
	return slow;
	
}


int main()
{
	std::vector<Node*> nodes_created;
	
	Node* head = new Node{};
	head->data = 0;
	nodes_created.push_back(head);
	Node* runner = head;
	
	for (int i = 1; i < 9; i++)
	{
		Node* new_node = new Node{};
		new_node->data = i;
		nodes_created.push_back(new_node);
		runner->next = new_node;
		runner = runner->next;
		
	}
	
	runner->next = nodes_created[3];
	
	Node* begin = findLoopBeginning(head);
	printf("loop beginning: %d\n", begin->data);
	
	for (int i = 0; i < nodes_created.size(); i++)
	{
		delete nodes_created[i];
	}
	
	
	
}
