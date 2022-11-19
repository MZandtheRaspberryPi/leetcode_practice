/*

Implement a MyQueue class that implements a queue using 2 stacks.

queue is FIFO. a stack is lifo. we could use 1 stacks as a buffer, pop from
stack to other until we get to bottom.

keep 1 stack in reverse order, so ones we want at the bottom.
when it comes time to grab, pop em all to the other stack, save bottom.
then pop em all back and return bottom.

to add, just put to top of stack that is occupied.

so adding, we have to put the new addition in the occupied stack.
adding is O(1) in time complexity.

popping, we pop everything from the occupied stack to the empty stack until we
have 1 left in occupied stack. we pop that out and return the value. popping is
O(N) in time complexity.

feedback from sol. we could optimise this by having an old stack and new stack.
push to new stack. then pop from old stack. when old stack empty, pop everything
from new stack to old stack, then order will be respected. so you dont need to
go through N each time you pop, only when old stack is empty.

*/

#include <stack>
#include <stdio.h>

class MyQueue {
public:
  MyQueue();
  int pop();
  void push(int data);

private:
  std::stack<int> &getBufferStack();
  std::stack<int> &getOccupiedStack();
  std::stack<int> stack_1_;
  std::stack<int> stack_2_;
};

MyQueue::MyQueue() {
  stack_1_ = std::stack<int>();
  stack_2_ = std::stack<int>();
}

std::stack<int> &MyQueue::getBufferStack() {
  if (stack_1_.empty()) {
    return stack_1_;
  } else {
    return stack_2_;
  }
}

std::stack<int> &MyQueue::getOccupiedStack() {
  if (stack_1_.size() > 0) {
    return stack_1_;
  } else {
    return stack_2_;
  }
}

int MyQueue::pop() {
  std::stack<int> &occupied_stack = getOccupiedStack();
  std::stack<int> &buffer_stack = getBufferStack();

  while (occupied_stack.size() > 1) {
    int tmp = occupied_stack.top();
    buffer_stack.push(tmp);
    occupied_stack.pop();
  }

  int tmp = occupied_stack.top();
  occupied_stack.pop();
  return tmp;
}

void MyQueue::push(int data) {
  std::stack<int> &occupied_stack = getOccupiedStack();
  occupied_stack.push(data);
}

int main() {
  MyQueue q = MyQueue();
  q.push(4);
  q.push(5);
  int tmp = q.pop();
  printf("push 4, 5, pop: %d\n", tmp);
  q.push(6);
  q.push(7);
  q.push(8);
  tmp = q.pop();
  printf("push 4, 5, pop, 6, 7, 8, pop: %d\n", tmp);
}
