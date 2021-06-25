// write a program to sort a stack in ascending order, with biggest items on the top 
// you may use additional stacks to hold items, but you may not copy elements into any other data structure like array
// the stack supporst following operations, push pop peek and is empty.

// so we could have two stacks in addition to stack to sort.  we could compare the current value to the top of our stackwith data, to the top of our second stack.
//  if it is less, we pop out elements from second stack into first until the next ele is greater than or equal to the one we want to add. we add the element,
// then push the other ones from stack 1 back into stack 2. then try next element.
// this means for each datapoint we want to add, if they're all ascending, to add one we'd have to move everything from one stack then back to the other, 2n.
// doing 2n operations for every element we add, means n^2.
// n * n 

#include<stdio.h>
#include<stack>

template <typename T>
std::stack<T> sortStack(std::stack<T> fullstack) {
	std::stack<T> stack1 = std::stack<T>{};
	std::stack<T> stack2 = std::stack<T>{};
	
	while (!fullstack.empty()) {
		if (stack2.empty()) {
			stack2.push(fullstack.top());
			fullstack.pop();
		}
		else if (fullstack.top() <= stack2.top()) {
			stack2.push(fullstack.top());
			fullstack.pop();
		}
		else {
			while (!stack2.empty()) {
				stack1.push(stack2.top());
				stack2.pop();
			}
			
			stack2.push(fullstack.top());
			fullstack.pop();
			
			while (!stack1.empty()) {
				stack2.push(stack1.top());
				stack1.pop();
			}
		}
	}
	
	return stack2;
}

// another approach that doesn't require 3 stacks
// rather than searching for min repeatedly, sort s1 by inserting each element from s1 in order into s2.
// so if have s1 5 > 10
// s2 1>3>8>12
// need to insert 5 in between 3 and 8. so, grab 5, put in temp variable.
// pop 1 3 from s2 to s1. insert 5, move 1 and 3 back over

template <typename T>
std::stack<T> sort(std::stack<T> s) {
	std::stack<T> r = std::stack<T>{};
	while (!s.empty()) {
		int tmp = s.top();
		s.pop();
		while (!r.empty() && r.top() > tmp) {
			s.push(r.top());
			r.pop();
		}
		r.push(tmp);
	}
	return r;
}

int main() {
	std::stack<int> stack = std::stack<int>{};
	for (int i = 4; i >= 0; i--) stack.push(i);
	stack = sortStack(stack);
	printf("%d\n", stack.top());

	std::stack<int> stack2 = std::stack<int>{};
	for (int i = 4; i >= 0; i--) stack2.push(i);
	stack2 = sort(stack2);
	printf("%d\n", stack.top());
}