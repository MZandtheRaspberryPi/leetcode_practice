/*
write a smart pointer class. smart pointer is a data type, templates, simulates pointer,
while providing automatic garbage collection. counts references. frees object when ref count hits zero.

We have a class that wraps whatever underlying data.

On init it starts counting by initting a uint pointer and setting it to one.

Copy assignment operator
this copies data into existing mem.
for this, we will need to copy underlying.
copy counter pointer, increment counter pointer.

Copy constructer operator
for this, we create new mem.



Destructor.


*/

#include <iostream>


template <class T>
class SmartPointer {
public:
	SmartPointer(T* underlying, unsigned int* counter = nullptr){
		this->underlying_data = underlying;
		if (counter == nullptr)
		{
			this->counter = new unsigned int (1);
		}
		else
		{
			this->counter = counter;
		}
	}
	
	~SmartPointer() {
		unsigned int& count = *(this->counter);
		count--;
		if (count == 0)
		{
			delete this->underlying_data;
			delete this->counter;
		}
	}
	
	// copy assignment operator
	SmartPointer<T> & operator=(const SmartPointer<T>& a) {
		
		if (*counter > 0) {
			remove();
		}
		
		if (this != &a)
		{
			underlying_data = a.underlying_data;
			counter = a.counter;
			++(*counter);
		}
		return *this;
	}
	
	SmartPointer(const SmartPointer& a) {
		this->underlying_data = a.underlying_data;
		this->counter = a.counter;
		unsigned int& count = *(this->counter);
		count++;
	}
	
	T get() {
		T data = *(this->underlying_data);
		return data;
	}
	
	protected:
		void remove() {
			--(*counter);
			if (*counter == 0) {
				delete counter;
				delete underlying_data;
				counter = nullptr;
				underlying_data = nullptr;
			}
		}
	
	private:
		T* underlying_data;
		unsigned int* counter;
	
};


int main()
{
	SmartPointer<int>* int_smt_ptr = new SmartPointer<int>(new int(3));
	
	SmartPointer<int> int_smt_ptr_2 = *int_smt_ptr;
	delete int_smt_ptr;
	int data = int_smt_ptr_2.get();
	std::cout << data << std::endl;
}