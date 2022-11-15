/*
Write a program to sort a stack in ascending order (with biggest items on top)
you may use additional stacks to hold items, but may not copy elements
into addtl data structure like an array. stack supports following operations
push, pop, peek, is empty.

on push, could pop items off of existing stack into another stack until stack 0
or until less than. then pop back from other stack to existing stack. time
complexity O(N). 2N actually as pop out and then back.

on pop, just grab from stack O(1) in time complexity.

could maybe save a bit by doing two stacks, where bottom one is less than
upper one is greater than, then you have to go through less. but then on pop you
have to go through entire upper stack. So time complexity of push would be
better, still O(N) in a worst case but 1N. time complexity of pop would be
worse, O(N) mainly.

feedback:
they didnt want a stack that was sorted, they wanted a function to take a stack, and sort it.
for this, could use three stacks. original one, a buffer to hold stuff while we find the min, and a third stack for the final stack.
search through original, popping stuff into buffer to find min. then pop stuff back except that min, popping min into third stack.
repeat.
this would be O(N^2) in time, and O(N) in space, but 2N which is consequential.

another option
use two stacks, one for original, one for final.
take first entry from original, save in tmp. pop stuff off of final until that tmp is less than the top or its empty. put tmp in.
pop stuff back to final. repeat.
this would be O(N^2) in time, and O(N) in space, but 1N which is a slight improvement from prior method.


*/

#include <stack>
#include <stdio.h>

class SortedStack {
public:
  SortedStack();
  int pop();
  void push(int data);

private:
  void popFromOriginToDest(std::stack<int> &origin, std::stack<int> &dest,
                           int comparison_value, bool lessThanComparison);
  std::stack<int> min_stack_;
  std::stack<int> max_stack_;
};

SortedStack::SortedStack() {
  min_stack_ = std::stack<int>();
  max_stack_ = std::stack<int>();
}

void SortedStack::popFromOriginToDest(std::stack<int> &origin,
                                      std::stack<int> &dest,
                                      int comparison_value,
                                      bool lessThanComparison) {
  if (lessThanComparison) {
    while (origin.size() > 0 && comparison_value < origin.top()) {
      int tmp = origin.top();
      origin.pop();
      dest.push(tmp);
    }
  } else {
    while (origin.size() > 0 && comparison_value > origin.top()) {
      int tmp = origin.top();
      origin.pop();
      dest.push(tmp);
    }
  }
}

void SortedStack::push(int data) {

  if (min_stack_.size() == 0 && max_stack_.size() == 0) {
    min_stack_.push(data);
    return;
  } else if (min_stack_.size() == 0) {
    std::stack<int> &target_stack =
        data <= max_stack_.top() ? min_stack_ : max_stack_;
    std::stack<int> &buffer_stack = min_stack_;
    popFromOriginToDest(target_stack, buffer_stack, data, true);
    target_stack.push(data);
    return;

  } else if (max_stack_.size() == 0) {
    std::stack<int> &target_stack =
        data >= min_stack_.top() ? max_stack_ : min_stack_;
    std::stack<int> &buffer_stack = max_stack_;
    popFromOriginToDest(target_stack, buffer_stack, data, true);
    target_stack.push(data);
    return;
  }

  if (data > min_stack_.top()) {
    popFromOriginToDest(max_stack_, min_stack_, data, false);
    max_stack_.push(data);
  } else {
    popFromOriginToDest(min_stack_, max_stack_, data, true);
    min_stack_.push(data);
  }
}

int SortedStack::pop() {
  int count = 0;

  int ret_val;
  if (max_stack_.size() >= 1) {
    while (max_stack_.size() > 1) {
      int tmp = max_stack_.top();
      max_stack_.pop();
      min_stack_.push(tmp);
    }
    ret_val = max_stack_.top();
    max_stack_.pop();

  } else if (min_stack_.size() >= 1) {
    ret_val = min_stack_.top();
    min_stack_.pop();
  } else {
    ret_val = -1;
  }
  return ret_val;
}

void sort(std::stack<int>& unsorted_stack)
{
	std::stack<int> sorted_stack;
	while (unsorted_stack.size() > 0)
	{
		int tmp = unsorted_stack.top();
		unsorted_stack.pop();
		int count = 0;
		while (sorted_stack.size() > 0 && sorted_stack.top() < tmp)
		{
			count++;
			unsorted_stack.push(sorted_stack.top());
			sorted_stack.pop();
		}
		sorted_stack.push(tmp);
		while (count > 0)
		{
			count--;
			sorted_stack.push(unsorted_stack.top());
			unsorted_stack.pop();
		}
	}
	unsorted_stack = sorted_stack;
	
}

int main() {

  SortedStack ss = SortedStack();
  ss.push(5);
  ss.push(3);
  int tmp;
  tmp = ss.pop();
  printf("push 5 3 pop: %d\n", tmp);
  ss.push(8);
  ss.push(3);
  tmp = ss.pop();
  printf("push 5 3 pop push 8 3 pop: %d\n", tmp);
	
	std::stack<int> stack_to_sort;
	stack_to_sort.push(5);
	stack_to_sort.push(7);
	stack_to_sort.push(2);
	stack_to_sort.push(4);
	stack_to_sort.push(15);
	stack_to_sort.push(1);
	stack_to_sort.push(-5);
	sort(stack_to_sort);
	while (stack_to_sort.size() > 0)
	{
		int tmp = stack_to_sort.top();
		stack_to_sort.pop();
		printf("%d\n", tmp);
	}
	
}