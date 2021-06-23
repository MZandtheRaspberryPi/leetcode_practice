// describe how you could use a single array to implement three stacks
// the array could be an array of nodes. three nodes. nodes have function to push, LIFO wise. where if null ptr next, t grabs its data. makes a new
// node w/ the data from itself. puts that as its next, sets its own data to new. if not nullptr next, recursively update each.
// recursion should go into next node passing head->next and its current data. it should go through like so till next is nullptr. make a new node w/ data and set that to its current data.
// then set data for current equal to that passed to it and next equal to node just made.

// solution. above was wrong. Can either allocate fixed space to each stack, so each gets 1/3 of size of array.
// or, we could do dynamic alloc, but this raises complexiity.

// fixed space. first stack gets {1/n, 2/n), second {2/n, 3/n), third{3/n, n) where { inclusive, ( exclusive.
#include<iostream>


int buffer[100 * 3] = { 0 };

int stackPointer[] = { -1, -1, -1 };

// returns index of top of stack "stackNum", in absolute terms
int absTopOfStack(int stackNum) {
	return stackNum * 100 + stackPointer[stackNum];
}

void push(int stackNum, int value) {
	// check if we have space
	if (stackPointer[stackNum] + 1 >= 100) { // last element
		throw "Stack out of space error, more than 100...";
	}
	// increment stack pointer and update top value
	stackPointer[stackNum]++;
	buffer[absTopOfStack(stackNum)] = value;
}

int pop(int stackNum) {
	if (stackPointer[stackNum] == -1) {
		throw "Trying to pop an empty stack.";
	}
	int value = buffer[absTopOfStack(stackNum)]; // get top
	buffer[absTopOfStack(stackNum)] = 0; // clear index
	stackPointer[stackNum]--; // decrement pointer
	return value;
}

int peek(int stackNum) {
	int index = absTopOfStack(stackNum);
	return buffer[index];
}

bool isEmpty(int stackNum) {
	return stackPointer[stackNum] == -1;
}

int main() {
	push(1, 0);
	push(1, 1);
	push(1, 2);
	push(0, 1);
	push(2, 3);
	
	std::cout << peek(2) << std::endl;
	std::cout << pop(1) << std::endl;
	std::cout << peek(1) << std::endl;

}