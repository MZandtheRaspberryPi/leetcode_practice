/* imagine stack of place. stack too high it'll fall.
create stack that mimicks this. set of stacks should make several stacks. should behave like new stack once previous exceeds capacity.
push/pop should be identical.
*/

// follow up implement a function popAt(int index) which performas a pop operation on a specific sub stack

#include<iostream>
#include<vector>

template <typename T>
struct Node {
	
	Node(T data, Node* next): data(data), next(next) {
	}
	
	Node<T>* next;
	T data;

	~Node() {
		delete next;
	}
};


template <typename T>
class Stack {
	Node<T>* top = nullptr;
public:
	void push(T data) {
		if (this->top == nullptr) {
			this->top = new Node<T>{ data, nullptr };
		}
		else {
			Node<T>* nextNode = new Node<T>{ data , this->top };
			this->top = nextNode;
		}
	}
	
	T pop() {
		if (this->top == nullptr) {
			throw "Top is nullptr, nothing to pop";
		}
		else {
			T preData = this->top->data;
			this->top = this->top->next;
			return preData;
		}
	}

	T peek() {
		if (this->top == nullptr) {
			throw "Nothing to see here, top is nullptr";
		}
		else {
			return this->top->data;
		}
	}

};

template <typename T>
class StackofStacks {
	int stackLimit = 5;
	int currentStack = 0;
	std::vector<Stack<T>> dishRack = std::vector<Stack<T>>(1, Stack<T>{});
	std::vector<int> dishCountPerRack = std::vector<int>(1, 0);
public:
	void push(T data) {
		if (this->dishCountPerRack[this->currentStack] == this->stackLimit) {
			this->currentStack++;
			this->dishRack.push_back(Stack<T>{});
			this->dishCountPerRack.push_back(0);
			this->push(data);
		}
		else {
			this->dishCountPerRack[this->currentStack] ++;
			this->dishRack[this->currentStack].push(data);
		}
	}

	T pop() {
		if (this->dishCountPerRack[this->currentStack] == 1) {
			T returnData = this->dishRack[this->currentStack].pop();
			this->currentStack--;
			this->dishRack.erase(this->dishRack.end() - 1);
			this->dishCountPerRack.erase(this->dishCountPerRack.end() - 1);
			return returnData;
		}
		else {
			this->dishCountPerRack[this->currentStack]--;
			return this->dishRack[this->currentStack].pop();
		}
	}

	T peek() {
		return this->dishRack[this->currentStack].peek();
	}
	


};

int main() {
	Stack<int> stack = Stack<int>{};
	stack.push(1);
	std::cout << stack.pop() << std::endl;
	stack.push(2);
	stack.push(5);
	std::cout << stack.peek() << std::endl;

	StackofStacks<int> stackofstacks{};
	stackofstacks.push(1);
	stackofstacks.push(2);
	stackofstacks.push(3);
	stackofstacks.push(4);
	stackofstacks.push(5);
	std::cout << stackofstacks.peek() << std::endl;
	stackofstacks.push(6);
	stackofstacks.push(7);
	std::cout << stackofstacks.peek() << std::endl;
	std::cout << stackofstacks.pop() << std::endl;
	std::cout << stackofstacks.pop() << std::endl;
	std::cout << stackofstacks.pop() << std::endl;

}