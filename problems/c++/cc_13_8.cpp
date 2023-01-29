/*
Write a smart pointer class. A smart pointer is a datatype, usually implemented with templates,
that simulates a pointer while also providing automatic garbage collection.

it counds the number of references to a SmartPointer<T*> object, and frees the objecct of type T*
when the reference count hits zero.

well we create a new template class, whose template is a T type.
constructor, copy constructor, copy assignment, give the next one out, and increment counter.
when destruct, remove 1 from counter and check if counter is zero. if zero call objects destructor.



*/

#include <iostream>

struct Node {
	int data;
	Node(int d) { data = d; }
	~Node() { std::cout << "node destructor called" << std::endl; }
};


template <class T>
class SmartPointer {
	public:
		SmartPointer(T* obj, int* count = nullptr) {
			if (count == nullptr)
			{
				counter = new int(1);
			}
			else
			{
				counter = count;
			}
			obj_ptr = obj;
		}
		
		SmartPointer(const SmartPointer& a)
		{
			this->obj_ptr = a.obj_ptr;
			this->counter = a.counter;
			*counter = *counter + 1;
			
		}
		SmartPointer& operator=(const SmartPointer& a)
		{
			remove();
			if (this != &a)
			{
				obj_ptr = a.obj_ptr;
				counter = a.counter;
				++(*counter);
			}
			return *this;
		}
		
		~SmartPointer()
		{
			remove();
		}
		
	  
	
  private:
	  void setCounter(int counter) { this->counter = counter; }
	  int* counter;
		void remove() {
			(*counter)--;
			if (*counter <= 0 )
			{
				delete obj_ptr;
				delete counter;
			}
		}
		T* obj_ptr;
		SmartPointer* orig_ptr;
};


int main()
{
	Node* n_ptr = new Node(1);
	
	SmartPointer smrt_ptr = SmartPointer(n_ptr);
	
	SmartPointer smrt_ptr2 = smrt_ptr;
	
	
}