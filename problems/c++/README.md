C++
classes and inheritance
```
#include <iostream>
using namespace std;

#define NAME_SIZE 50 // defines a macro

class Person {

  int id;
	char name[NAME_SIZE];
	
	public:
	  void aboutMe() {
		  cout << "I am a person.";
		}
};

class Student : public Person {
  void aboutMe() {
	  cout << "I am a student.";
	}
}

int main()
{
  Student * p = new Student();
	p->aboutMe(); // prints I am a student
	delete p; // make sure to delete allocated memory
	return 0;
}
```

Constructor of class auto called on creation. if none defined, default constructor.
```
Person(int a) {}
```

can init fields:
```
Person(int a) : id(a) {

}
```

the data member id is assigned b/f actual object created and before remainder of constructor code called. useful when constant fields,
assigned only once.

destructor cleans up on object deletion, called when destroyed. doesnt take arg, as dont explicitely call.
```
~Person() {
  delete name; // free memory allocation for name
}
```

Virtual functions
in earlier example, p was student. what if person?
```
Person * p = new Student();
p->aboutMe();
```
would print i am person. as function resolved at compile-time, static binding.

to ensure studnets implementation is called, define about me in person class to be virtual.

```
class Person {
  ...
	virtual void aboutMe() {...}
}

class Student : public Person {
  public:
	  void aboutMe() {...}
}
```

Another usage for virtual functions, dont want to implement method for parent class.
student, teacher inherit from person, so we can do common method addcourse.
but calling that on person wouldnt make sense.

so make addcourse be virtual function and leave implementation to subclass.

```
  virtual bool addCourse(string s) = 0;
```

by definign add course pure virtual function person is abstract class and we cannot instantiate it.

virtual destructor
if we define parent class destructor to be virtual, will call both it and child.

```
Person * p = new Student();
delete p;
```

default values. note all must be on right side of function dec.
```
int func(int a, int b = 3);

w = func(4);
z = func(4, 5);
```

operator overloading. lets us apply operators like + to objects.
```
BookShelf BookShelf::operator+(Packet & other) {...}
```

Pointers and references

pointer holds address of variable, can perform any operation can do directly
```
int * p = new int;
*p = 7;

int * q = p;
*p = 8;
cout << *p; // prints 8
```

note size of pointer depends on architecture. 32 bits on 32bit machine, 64 on 64 bit machine. need to pay attention,
as common in interviews to ask how much space datastructure takes.

references
reference is alias for pre-existing object, doesnt have memory of its own.
```
int a = 5;
int & b = a;
b = 7;
cout << a; // prints 7
```

cant create ref w/o specifying where in memory refers to. but can create free standing ref like below.
ref cant be null and cant be reassigned to naohter piece memory.
```
int & b = 12;
```

pointer arithmetic
often see addition on pointer. p++ will skip 4 bytes in below. will skip as many bytes as size of data structure.
```
int * p = new int[2];
p[0] = 0;
p[1] = 1;
p++;
cout << *p; // outputs 1
```

templates
reuse code to apply same class to diff data type. 
```
#include <iostream>

using namespace std;

template <class T>
class ShiftedList {
  T* array;
	int offset, size;
	
	public:
	  ShiftedList(int sz) : offset(0), size(sz) {
		  array = new T[size];
		}
    ~ShiftedList() {
		  delete [] array;
		}
		
		void shiftBy(int n) {
			offset = (offset + n) % size;
		}
	
		T getAt(int i) {
		  return array[convertIndex(i)];
		}
		
		void setAt(T item, int i) {
		  array[convertIndex(i)] = item;
		}
		
	private:
	  int convertIndex(int i) {
		  int index = (i - offset) % size;
			while (index < 0) index += size;
			return index;
		}
};

int main()
{
  int size = 4;
	ShiftedList<int> * list = new ShiftedList<int>(size);
	for (int i = 0; i < size; i++)
	{
	  list->setAt(i, i);
	}
	
	cout << list->getAt(0) << endl;
	cout << list->getAt(1) << endl;
	list->shiftBy(1);
	cout << list->getAt(0) << endl;
	cout << list->getAt(1) << endl; 
	delete list;
}

```
