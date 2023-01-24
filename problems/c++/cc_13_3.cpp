/*
How do virtual functions work in c++?

In the context of inheritance, virtual functions are useful to ensure that a method from a parent class will get overridden
by the same named method of the child class. they are usually resolved at compile time in a process called static binding....FALSE

For example: the below class student's method sayHi will override the students sayHi method.

One can also use a virtual destructor in the parent class to ensure that its destructor will be called in addition to the
child class's destructor.

feedback from solution. not quite right.
virtual function depends on v table, virtual table.
when function in class declared virtual, vtable constructed and secret vptr added to class.
vtable stores addresses of virtual function to class. when overridden stores addresses. will point to most derived.

dynamic binding using vtable performed.

non-virtual functions resolved compile time, static binding. virtual functions resolved runtime dynamic binding.
*/

#include <iostream>

class Person
{
	public:
	  virtual void sayHi()
		{
			std::cout << "hi from person" << std::endl;
		}
		virtual ~Person()
		{
			std::cout << "person destructing" << std::endl;
		}
	
};

class Student : public Person
{
	public:
	  void sayHi()
		{
				std::cout << "hi from student" << std::endl;
		}
		~Student()
		{
			std::cout << "student destructing" << std::endl;
		}
	
};

int main()
{
	Person* p = new Student();
	p->sayHi();
	delete p;
	return 0;
	
}