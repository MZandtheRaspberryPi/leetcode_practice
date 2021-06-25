// how would you implement a stack which, in addition to push and pop also has a function min which returns min element.
// all should operate in o(1) time.

// could use linked list implementation, but when adding check if data is less than min, and save.
#include<iostream>

template <typename T>
struct Node {
	
	Node(T data, Node* next): data(data), next(next) {
		
	}
	
	T data;
	Node* next;
};

template <typename T>
class Stack {
public:
	Node<T>* top = nullptr;
	T data;
	
	void push(T data) {
		if (this->top == nullptr) {
			this->top = new Node<T>{ data, nullptr };
			this->data = data;
		}
		else {
			Node<T>* newTop = new Node<T>{ data, this->top };
			this->top = newTop;
			this->data = newTop->data;
		}
	}

	T pop() {
		if (this->top == nullptr) {
			throw "Current stack is empty";
		}
		else {
			T data = this->data;
			this->data = this->top->next->data;
			this->top = this->top->next;
			return this->data;
		}
	}

	T peek() {
		return this->data;
	}
};

template <typename T>
class StackWithMin : public Stack<T> {

	Stack<T> minStack;
public:
	StackWithMin<T>() : Stack<T>() {

	}

	void push(T data) {
		
		if (Stack<T>::top == nullptr || data < this->minStack.peek()) {
			this->minStack.push(data);
		}
		else {
			this->minStack.push(this->minStack.peek());
		}

		Stack<T>::push(data);
	}

	T pop() {
		this->minStack.pop();
		return Stack<T>::pop();
	}

	T min() {
		return this->minStack.peek();
	}

};

int main() {
	StackWithMin<int> stack = StackWithMin<int>{};
	stack.push(2);
	std::cout << stack.peek() << std::endl;
	stack.push(3);
	stack.push(5);
	std::cout << stack.min() << std::endl;
	stack.push(1);
	std::cout << stack.min() << std::endl;
	stack.push(5);
	std::cout << stack.min() << std::endl;
	stack.pop();
	stack.pop();
	std::cout << stack.min() << std::endl;
}