/*

Imagine a literal stack of plates. if too high, fall.
real life, new stack when previous exceeds threshold.
implement datastructure, set of stacks, mimics this.

should be composed of several stacks, createa new one when previous exceeds cap.
push and pop should behave identicallz to single stack.

so for this, use an array and resize each time we add or remove a stack. it has
stacks in it. the one thing we gotta watch out for is the copy assignment for
the stacks. vector resize if it has to increment capacity will reallocate
storage, and hence call copy assigment.

so time complexity, still constant pop and push and front.
space, still o(n).


follow up, implement popAt(int index) which performs pop on specific sub stack.
so for this, do we want to leave some containers not full?
or do we want to implement so that if we have 2 full stacks and 1 half full
stack, and we pop from first stack, we waterfall stuff down to the first stack
so that it and second are still full and the third is empty?

*/

#include <stdio.h>
#include <vector>

struct Node {
  int data;
  Node *next;
};

class Stack {
public:
  Stack();
  ~Stack();
  Stack(const Stack &rhs);
  int pop();
  void push(int data);
  int getCurrentSize() const;
  Node *getHead() const;

private:
  Node *head = nullptr;
  int current_size_;
};

class StackWithMax {
public:
  StackWithMax(int max_stack_size);
  int pop();
  void push(int data);

private:
  int max_stack_size_;
  std::vector<Stack> stacks_;
};

Stack::Stack() { current_size_ = 0; }

Stack::~Stack() {
  while (head != nullptr) {
    Node *prev = head;
    head = head->next;
    delete prev;
  }
}

Node *Stack::getHead() const { return head; }

Stack::Stack(const Stack &rhs) {
  head = nullptr;
  Node *runner = nullptr;
  Node *rhs_head = rhs.getHead();
  current_size_ = rhs.getCurrentSize();
  while (rhs_head != nullptr) {
    Node *new_node = new Node{};
    new_node->data = rhs_head->data;

    if (head == nullptr) {
      head = new_node;
      runner = head;
    } else {
      runner->next = new_node;
      runner = runner->next;
    }

    rhs_head = rhs_head->next;
  }
}

int Stack::pop() {
  if (head == nullptr) {
    return -1;
  }
  current_size_--;
  Node *top = head;
  int tmp = top->data;
  head = head->next;
  delete top;
  return tmp;
}

void Stack::push(int data) {
  Node *new_node = new Node{};
  new_node->data = data;
  new_node->next = head;
  head = new_node;
  current_size_++;
}

int Stack::getCurrentSize() const { return current_size_; }

StackWithMax::StackWithMax(int max_stack_size)
    : max_stack_size_(max_stack_size) {
  stacks_.resize(1);
  Stack stack = Stack();
  stacks_[0] = stack;
}

int StackWithMax::pop() {
  for (int i = stacks_.size() - 1; i >= 0; i--) {
    Stack &stack = stacks_[i];
    if (stack.getCurrentSize() > 0) {
      return stack.pop();
    }
  }
  return -1;
}

void StackWithMax::push(int data) {
  for (int i = 0; i < stacks_.size(); i++) {
    int stack_size = stacks_[i].getCurrentSize();
    if (stack_size < max_stack_size_) {
      stacks_[i].push(data);
      return;
    }
  }
  // all our stacks are full
  int cur_size = stacks_.size();
  stacks_.resize(cur_size + 1);
  cur_size = stacks_.size();
  stacks_[cur_size - 1] = Stack();
  stacks_[cur_size - 1].push(data);
}

int main() {
  StackWithMax stack_max = StackWithMax(2);
  int tmp;
  stack_max.push(1);
  stack_max.push(2);

  tmp = stack_max.pop();
  printf("1, 2, pop is: %d\n", tmp);

  stack_max.push(2);
  stack_max.push(3);
  tmp = stack_max.pop();
  printf("1, 2, 3, pop is: %d\n", tmp);
  tmp = stack_max.pop();
  printf("1, 2, 3, pop, pop is: %d\n", tmp);
}