// given a circular linked list, implement an algorithm that returns the node at the beginning of hte loop
// circular linked list, corrupt, which nodes next pointer points to an earlier node, so as to make a loop in linked list
// A>B>C>D>E>C (same as earlier C) output C

// go through linked list, put data into array.
// for each element, take it as the starting point for a loop
// check the array and see if starting at that element, there is a value like it in array. If not, add it and reset the continueous streak
// if there is, then set flag to start if not already, and save that value as a start. check that next element in array matches current. if not, add it, set flag to false.
// set the new starting point. 

// loop through list. take each value and insert into array if not there. then, take that value as the current starting point for a circular check.
// go to next value. If its not in array, take that as the current starting point. If it is in array, and equals starting point return that. If it is in array 
// and is new, add it to the array and go to the next.
// this will run in n^2 time as for each entry in linked list we check if its in array. Space complexity would be a little less than O(n), as we store unique elements in array.

// other idea is loop through list, hash table to store values and counts. when one value hits count 2, exit and return that value. Would that work in all circumstances?
// that would have O(n) run time and space complexity of N?
// hash table, store pointer and counts? better solution as then we look at nexts only. yes.

// another approach is to use fast runner /slow runner approach
// fast run 2, slow runs 1
// if non looped part size k, when slow enters loop after k steps, fast taken  2k steps, 2k -k steps into loop

// k might be larger than loop length, should say mod(k, loop_size), denote as K

// at each subseq step, fast runner slow runner get one step farther/closer. when a moves q steps away from b, also moves q steps closer to b.

// so we know
// slow runner 0 steps into loop
// fastrunner k steps into the loop
// slow runner is k steps behind fast runner
// fast runner is loop size - k steps behind slow runner
// fast runner catches up to slow runner at a rate of 1 step per unit of time 

// fast runner is loop size - k behind , and catches up at rate of 1 step per time unit, they meet after
// loop size - k steps. at this point, they'll be k steps before head of loop. collision point.

// collision point is k nodesb/f loop start. k = mod(k, loop size), or k = K + M * loop size for any int M).
// if node n is 2 steps into 5 node loop, can be 7, 12, or 397 steps in. so collissionspot and linked list heads are k nodes from teh start of the loop.

// if keep pointer at collission spot, and move other to linekd list head, k nodes from loop start. moving at same speed cause
// em to collide again, after k steps, at loop start. so return that node.

#include<map>
#include<stdio.h>
using namespace std;

struct Node{
	int data;
	Node* next = nullptr;
};

Node* findLoopStart(Node* node) {
	map<Node*, int> pointerMap;
	
	while (node != nullptr) {
		if (pointerMap.find(node) != pointerMap.end()) {
			return node;
		}
		pointerMap[node] = 1;
		node = node->next;
	}
}

Node* findLoopStartOptimal(Node* node) {
	Node* slow = node;
	Node* fast = node;

	/* find meeting point, loop size - k steps into linked list, where k is nodes before start of loop*/
	while (fast != nullptr && fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {
			// collission
			break;
		}

	}

	// error check, no meeting point, therefore no loop
	if (fast == nullptr || fast->next == nullptr) {
		return nullptr;
	}

	/* move slow to head. keep fast at meeting point. each are k steps from loop start.
	if move at same pace, must meet at loop start*/
	slow = node;
	while (slow != fast) {
		slow = slow->next;
		fast = fast->next;
	}

	// both now point to start of the loop
	return fast;
}



int main(){
	Node* node00 = new Node{};
	node00->data = 7;
	Node* node01 = new Node{};
	node01->data = 1;
	node00->next = node01;
	Node* node02 = new Node{};
	node02->data = 6;
	node01->next = node02;
	node02->next = node00;
	
	Node* badHead = findLoopStart(node00);
	printf("%d\n", badHead->data);

	badHead = findLoopStartOptimal(node00);
	printf("%d\n", badHead->data);

	delete node00;
	delete node01;
	delete node02;
}