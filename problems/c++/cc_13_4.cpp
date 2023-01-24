/*
What is the difference between deep copy and shallow copy.
Explain how you would use each.

A shallow copy is probably a pointer or a reference to the same object.

A deep copy would then be allocating new memory for a new object.

A shallow copy we could use to have a couple variables that update when the underlying is changed.
Perhaps we want to have a lock that can be accessed by various threads.

a deep copy would be when we are starting a new thread for example and want to pass a variable and access it
without syncronization.

feedback from solution, got this kind of wrong.

shallow copy, when copy members like ptrs, but dont create new memory. deep copy, allocate new memory, copy whole object and make new mem.
shallow copy, used very rarely, most often when want info about class but not alloc mem. in practice, always deep copy.


*/

#include <iostream>
#include <cstring>

struct Test
{
	char* ptr;
};

void shallow_copy(Test& src, Test& dst)
{
	dst.ptr = src.ptr;
}

void deep_copy(Test& src, Test& dst)
{
	std::cout << "str len: " << std::strlen(src.ptr) << std::endl;
	dst.ptr = (char*)malloc(std::strlen(src.ptr) + 1);
	std::memcpy(dst.ptr, src.ptr, std::strlen(src.ptr) + 1);
}

void print_char_ptr(char* src)
{
	int runner = 0;
	while (src[runner] != '\0')
	{
		std::cout << src[runner] << ", ";
		runner++;
	}
	std::cout << std::endl;
}

int main()
{
	Test tst;
	char* ptr = new char[10];
	ptr[9] = '\0';
	for (int i = 0; i < 9; i++)
	{
		ptr[i] = 'A' + i;
	}
	
	tst.ptr = ptr;
	
	Test tst2;
	shallow_copy(tst, tst2);
	std::cout << tst2.ptr << std::endl;
	
	deep_copy(tst, tst2);
	std::cout << tst2.ptr << std::endl;
	
	print_char_ptr(tst2.ptr);
	delete[] ptr;
	delete[] tst2.ptr;
	
	
	
}