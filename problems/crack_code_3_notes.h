
template <typename T>
struct Node {
	Node(T data, Node* next) : data{ data }, next{ next }{

	}
	
	T data;
	Node* next = nullptr;
};

template <typename T>
class Stack {
public:
	<T>Node* top;

	T pop() {
		if (top != nullptr) {
			T item = top->data;
			top = top->next;
			return item;
		}
		throw 20;
	}

	void push(T item) {
		Node t = Node{ item, top };
		top = t;
	}

	T peek() {
		return top->data;
	}


};

template <typename T>
class Queue {
	Node* first, last;

	void enqueue(T item) {
		if (first == nullptr) {
			last = new Node{ item, nullptr };
			first = last;
		}
		else {
			last->next = new Node{ item, nullptr };
			last = last->next;
		}
	}

	T dequeue() {
		if (first != nullptr) {
			T item = first->data;
			first = first->next;
			return item;
		}
		throw 22;
	}

};