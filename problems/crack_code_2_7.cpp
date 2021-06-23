// implement a function to check if a linked list is a palindrome.

// store all of list, reverse, check if equal to prior. not very elegant.

// move pointer all the way to end, keep count of how long, check if equal to head. move head 1, move runner to length - 1, continue. Storage constant. for each entry, gotta traverse whole list. n^2.
// exit condition when head next is runner, or runner == head.

// or, store whole thing as vector and then loop over vector. so storage would be N. time  complexity would be N to store, N to check, order N total.

// test cases
// 5 > 4 > 3 > 4 > 5
// 1 > 2 > 3 > 4 > 5

// optimal, could also reverse linked list and compare reversed to original. if same, identicla. only need to do first half.
// front half is reverse of second half, how do? reverse front half. use a stack.

// iterate through first half of elements, pushing into stack. if know size, but handle if odd.
// if don't know size, can iterate through w/ fast runner/slow runner technique.
// at each step, we push data from slow runner onto stack. when runner hits end, slow is at middle. then all elements from front of linked list in stack
// but reversed order

// now iterate through rest of linked list. compare node to top of stack. if compelte iteration w/o finding diff, then linked list palendrome.

#include<iostream>
#include<stack>

struct Node {
	int data;
	Node* next;
};

bool isPalindrome(Node* head) {
	Node* runner = head;
	int listLen = 1;
	// moving runner to the end
	while (runner->next != nullptr) {
		listLen += 1;
		runner = runner->next;
	}

	while (head != runner && head->next != runner) {
		// not a palindrome if letter pairs don't match
		if (head->data != runner->data) {
			return false;
		}

		// if they do match move runner to the spot before it was just at.
		runner = head;
		listLen -= 1;
		for (int i = 1; i < listLen; i++) {
			runner = runner->next;
		}
		head = head->next;
	}

	return true;
}

bool isPaldindromeOptimal(Node* head) {
	Node* fast = head;
	Node* slow = head;
	std::stack<int> stack = std::stack<int>();

	/*push elements from first half of linked list to stack
	when fast runner reaches end of linked list, we're in middle*/
	while (fast != nullptr && fast->next != nullptr) {
		stack.push(slow->data);
		slow = slow->next;
		fast = fast->next->next;
	}

	// has odd num of elements, so skip middle element
	if (fast != nullptr) {
		slow = slow->next;
	}
	while (slow != nullptr) {
		int top = stack.top();
		stack.pop();

		// if values diff, not a palindrome
		if (top != slow->data) {
			return false;
		}
		slow = slow->next;
	}
	return true;
}

// can do a recursive solution to this as well.
// 0 ( 1 (2 (3) 2) 1) 0
// also pass in length - 2 each recursion, when 1 or 0 we know we're in middle. if in middle return head->next.
// else check if data is equal to returned value, if yes return head - > next
// to return bool and pointer, new class. if in c++ could return double pointer

struct Result{
	Result(Node* node, bool result) : result{ result }, node{ node } {
	}
	bool result;
	Node* node = nullptr;
};

Result isPalindromeRecurse(Node* head, int length) {
	if (head == nullptr || length == 0) {
		return Result{ nullptr, true };
	}
	else if (length == 1) {
		return Result{ head->next, true };
	}
	else if (length == 2) {
		return Result{ head->next->next, head->data == head->next->data };
	}

	Result res = isPalindromeRecurse(head->next, length - 2);
	if (!res.result || res.node == nullptr) {
		return res;
	}
	else {
		res.result = head->data == res.node->data;
		res.node = res.node->next;
		return res;
	}
}

int listSize(Node* head) {
	if (head == nullptr) {
		return 0;
	}
	int size = 1;
	while (head->next != nullptr) {
		size++;
		head = head->next;
	}
	return size;
}

bool isPalindromeRecOpt(Node* head) {
	Result p = isPalindromeRecurse(head, listSize(head));
	return p.result;
}


int main() {
	Node* node00 = new Node{};
	node00->data = 2;
	Node* node01 = new Node{};
	node01->data = 1;
	node00->next = node01;
	Node* node02 = new Node{};
	node02->data = 2;
	node01->next = node02;

	bool result = isPalindrome(node00);
	std::cout << result << '\n';

	result = isPaldindromeOptimal(node00);
	std::cout << result << '\n';

	result = isPalindromeRecOpt(node00);
	std::cout << result << '\n';
	
	node00->data = 1;
	node01->data = 2;
	node02->data = 3;
	result = isPalindrome(node00);
	std::cout << result << '\n';


}