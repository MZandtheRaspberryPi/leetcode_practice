// implement a MyQueue class which implements a queue using two stacks.

// queue is fifo

// so we could have a stack for the front, and a stack for the back.

// if we have one item, we add it to front stack and back stack
// if we have a second item, push it to back stack, then push first into back stack.
// if we have a third item, push first into first stack, then second into first stack, then third into back stack, then second into back stack, then first into back stack

// so each time we add an item, we pop everything and push it into other stack one by one, then we add new item to empty stack, then push everything back.

// in this way we'll keep the FIFO ordering

#include<stack>
#include<stdio.h>

template <typename T>
class MyQueue{
	std::stack<T> stack1 = std::stack<T>{};
	std::stack<T> stack2 = std::stack<T>{};
public:
	void enqueue(T data) {
		// this will be O(N) where N is the number of items in the queue efficient in timae complexity, and O(N) in storage complexity as well.
		if (stack2.empty()) {
			stack2.push(data);
		}
		else {
			// push everything from 2 to 1, then push the new data to 2, then add everything back to 2
			while (!stack2.empty()) {
				stack1.push(stack2.top());
				stack2.pop();
			}
			stack2.push(data);
			while (!stack1.empty()) {
				stack2.push(stack1.top());
				stack1.pop();
			}
		}
	}
	
	T dequeue() {
		T returnVal = stack2.top();
		stack2.pop();
		return returnVal;
	}

};

template <typename T>
class MyQueueOptimal {
	// the idea here is that with implementation above
	// if we do 2 pops/peeks back to back we are needlessly moving elements
	// so, let elements sit in s2 unless we absolutely must reverse elements
	// stacknewest new on top, oldest old on top. when dequeue, want oldes, so dequeue from oldest.
	// if oldest empty, transfer all from stack newest into this stack in reverse order.
	// to insert, push to stack newest, as has newest elements on top

	std::stack<T> stackNewest, stackOldest;
	// move elements from stack newest into stack oldest this is usually done so we can do operations on stack oldest
	void shiftStacks() {
		if (stackOldest.empty()) {
			while (!stackNewest.empty()) {
				stackOldest.push(stackNewest.top());
				stackNewest.pop();
			}
		}
	}
public: 
	MyQueueOptimal() {
		stackNewest = std::stack<T>{};
		stackOldest = std::stack<T>{};
	}

	int size() {
		return stackNewest.size() + stackOldest.size();
	}

	void add(T value) {
		// push onto stack newest which always has newest elements on top
		stackNewest.push(value);
	}

	T peek() {
		// sensure stackOldest has current elements
		shiftStacks();
		return stackOldest.top();
	}

	T remove() {
		// ensure stackOldest has current elements
		shiftStacks();
		T returnVal = stackOldest.top();
		stackOldest.pop();
		return returnVal;
	}
};


int main() {
	MyQueue<int> q = MyQueue<int>{};
	for (int i = 0; i <= 4; i++) q.enqueue(i);
	printf("%d\n", q.dequeue());
	printf("%d\n", q.dequeue());

	MyQueueOptimal<int> qo = MyQueueOptimal<int>{};
	for (int i = 0; i <= 4; i++) qo.add(i);
	printf("%d\n", qo.peek());

}