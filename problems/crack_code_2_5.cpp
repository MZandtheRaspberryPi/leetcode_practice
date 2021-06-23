/* two numbers represented by linked list. each node contains 
single digit. digits store din reverse order, 1s digit is at head of list
wriet function that adds two numbers then returns sum as linked list.

ex: 7>1>6 + 5>9>2 that is 617+295 = 2>1>9 that is 912

next, suppose digits stored in forward order, repeat the above problem.
*/

#include<math.h>
#include<stdio.h>

class Node {
public:
	int data;
	Node* next = nullptr;
	Node* prev = nullptr;
};

Node* addListsReversed(Node* head1, Node* head2) {
	// any constraints on the two numbers passed? Integers, could they be close to upper limit for integers 2^-32, or 2^32 -1
	// if head1 is null, return head2, and vice versa
	// loop over first list, till next is null
	// for each data point multiply 10^i by it then add it to a running sum to get number, where i is the number of digits/what node you're on
	// then, do the same for second list
	// then, add the two together.
	// then go over the result while its not equal to zero, then for each iteration, get the remainder from 10, set that as the first element, divide by 10, continue
	// then return the pointer to the ensueing list
	// this will be O(N) in time complexity, and O(N) in storage complexity as we store the calculated result
	if (head1 == nullptr) {
		return head2;
	}
	if (head2 == nullptr) {
		return head1;
	}
	
	int num1 = 0;
	int digitCounter = 0;
	while (head1 != nullptr) {
		num1 += head1->data * (pow(10, digitCounter));
		digitCounter += 1;
		head1 = head1->next;
	}
	
	int num2 = 0;
	digitCounter = 0;
	while (head2 != nullptr) {
		num2 += head2->data * (pow(10, digitCounter));
		digitCounter += 1;
		head2 = head2->next;
	}
	
	int result = num1 + num2;
	Node* head = new Node{};
	int digit = result % 10;
	head->data = digit;
	result = result / 10;
	Node* previous = head;
	
	while (result > 0) {
		digit = result % 10;
		Node* next = new Node{};
		next->data = digit;
		previous->next = next;
		result = result / 10;
		previous = next;
	}
	return head;
}


Node* addListsReverseOptimal(Node* head1, Node* head2, int carry) {
	// 6>1>7 + 2>9>5 that is 617 plus 295 = 9>1>2 that is 912
	// go through each element in linked lists
	// check if l1 not null, if so add to carry
	// check if l2 not null, if so add to carry
	// and take that ones digit and set it to the element in a new node
	// if l1 not null or l2 not null or carry is greater than or equal to 10
	// go to next recursion
	// call same function recursively, passing the new carry, get next node
	// set current result's next equal to that return next
	// carry the remainder to the next recursion
	
	// we're done if both lists null AND carry value is 0
	if (head1 == nullptr && head2 == nullptr && carry == 0) {
		return nullptr;
	}

	Node* result = new Node{};
	int value = carry;

	if (head1 != nullptr) {
		value += head1->data;
	}

	if (head2 != nullptr) {
		value += head2->data;
	}

	result->data = value % 10; // ones digit of the number
	carry = value >= 10 ? 1 : 0;

	// recurse
	if (head1 != nullptr || head2 != nullptr || carry >= 1) {
		Node* more = addListsReverseOptimal(head1 != nullptr ? head1->next : nullptr,
											head2 != nullptr ? head2->next : nullptr,
											carry);
		result->next = more;
	}

	return result;
}

/*
Node* addListsForward(Node* head1, Node* head2) {
	// 7>1>6 + 5>9>2 that is 716+592 = 1>3>0>8 that is 1308

	// to translate each list to number
	// store an array
	// add digit to array
	// as count digits, multiply existing digits by 10 each loop
	// then sum all digits up to get number

	// similar for second number
	// add

	// figure out max power of 10 with while loop, checking greater than adding to count of power
	// starting at + 1 power of ten, divide result by power of ten to get greatest digit
	// set to new node's data
	// subtract data value * 10 to power of ten from result
	// go to power of ten - 1, repeat till result is 0
	// return head of list
}
*/

struct PartialSum {
	Node* sum = nullptr;
	int carry = 0;
};

int length(Node* head) {
	int len = 0;
	while (head != nullptr) {
		len += 1;
		head = head->next;
	}
	return len;
}

// add zero padding to linked list, before head
Node* padList(Node* l, int padding) {
	Node* head = l;
	for (int i = 0; i < padding; i++) {
		Node* n = new Node{};
		n->data = 0;
		head->prev = head;
		head = n;
	}
	return head;
}

// helper function to insert node in front of a linked list
Node* insertBefore(Node* list, int data) {
	Node* node = new Node{};
	node->data = data;
	if (list != nullptr) {
		list->prev = node;
		node->next = list;
	}
	return node;
}

PartialSum* addListsHelper(Node* head1, Node* head2) {
	if (head1 == nullptr && head2 == nullptr) {
		PartialSum* sum = new PartialSum{};
		return sum;
	}
	// add smaller digits recursively
	PartialSum* sum = addListsHelper(head1->next, head2->next);
	// add carry to current data
	int val = sum->carry + head1->data + head2->data;
	// insert sum of current digits
	Node* full_result = insertBefore(sum->sum, val % 10);

	// return sum so far, and the carry value
	sum->sum = full_result;
	sum->carry = val / 10;
	return sum;
}

// with reversed digits, successive reuslts added to tail, ie, passed forward. recursive call
// passed the carry, returned result which was appended to tail.
// in this case, results added to the head, passed backward. recursive call return result, as well as carry
// hence wrapper class to return
Node* addListsForwardOptimal(Node* head1, Node* head2) {
	// 7>1>6 + 5>9>2 that is 716+592 = 1>3>0>8 that is 1308
	int len1 = length(head1);
	int len2 = length(head2);

	// pad the shorter list w/ zeros
	// if add 1>2>3>4 and 5>6>7, need to know 5 should be matched with the 2, not the 1.
	if (len1 < len2) {
		head1 = padList(head1, len2 - len1);
	}
	else {
		head2 = padList(head2, len1 - len2);
	}

	// add lists
	PartialSum* sum = addListsHelper(head1, head2);

	// if there was a carry value left over
	// insert at the front of list
	// otherwise, just return linked list
	if (sum->carry == 0) {
		return sum->sum;
	}
	else {
		Node* result = insertBefore(sum->sum, sum->carry);
		return result;
	}
}

/*
Node* addListsForwardOptimalSelf(Node* head1, Node* head2) {
	// 7>1>6 + 5>9>2 that is 716+592 = 1>3>0>8 that is 1308

	// to translate each list to number
	// store an array
	// add digit to array
	// as count digits, multiply existing digits by 10 each loop
	// then sum all digits up to get number

	// similar for second number
	// add

	// figure out max power of 10 with while loop, checking greater than adding to count of power
	// starting at + 1 power of ten, divide result by power of ten to get greatest digit
	// set to new node's data
	// subtract data value * 10 to power of ten from result
	// go to power of ten - 1, repeat till result is 0
	// return head of list



}
*/


int main() {
	// 7>1>6 + 5>9>2 that is 617+295 = 2>1>9 that is 912
	Node* node00 = new Node{};
	node00->data = 7;
	Node* node01 = new Node{};
	node01->data = 1;
	node00->next = node01;
	Node* node02 = new Node{};
	node02->data = 6;
	node01->next = node02;

	Node* node10 = new Node{};
	node10->data = 5;
	Node* node11 = new Node{};
	node11->data = 9;
	node10->next = node11;
	Node* node12 = new Node{};
	node12->data = 2;
	node11->next = node12;

	Node* head = addListsReversed(node00, node10);
	Node* previous = nullptr;

	while (head != nullptr) {
		printf("%d\n", head->data);
		previous = head;
		head = head->next;
		delete previous;
	}

	head = addListsReverseOptimal(node00, node10, 0);
	previous = nullptr;

	while (head != nullptr) {
		printf("%d\n", head->data);
		previous = head;
		head = head->next;
	}

	head = addListsForwardOptimal(node00, node10);
	previous = nullptr;

	while (head != nullptr) {
		printf("%d\n", head->data);
		previous = head;
		head = head->next;
		delete previous;
	}


	delete node00;
	delete node01;
	delete node02;
	delete node10;
	delete node11;
	delete node12;
	delete head;
}