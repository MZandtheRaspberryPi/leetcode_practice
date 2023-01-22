/*
suppose we got following code
class Foo {
	public:
	  Foo();
		void first();
		void second();
		void third();
}

the same instance of Foo will be passed to three different threads. threadA will call first,
threadB second, threadC third. Design a mechanism to ensure that first is called before
second and second is called before third.

we could add additional data to the class, to signal when first is called, when second is called, and when third is called.
a bool for each.

then we could have a lock to check these bools, and in each function try and get the lock, and if we dont get it then sleep a bit.
if we do get it check the value, and then release the lock. if value is true, then do function, if not, sleep.

feedback from solution, this would work, but didnt realize they were hinting you cant unlock one threads mutex from another thread.
in c++ this will return false or block the thread until the owernship is released (by owner thread unlocking).

so, could use semaphores which boost has, or potentially c++ 20.

*/

#include <chrono>
#include <mutex>
#include <stdio.h>
#include <thread>

#define SLP_MS 5

class Foo {
	public:
	  Foo();
		void first();
		void second();
		void third();
	private:
	  void wait(int wait_ms);
	  std::mutex checkerMtx;
	  bool firstDone;
		bool secondDone;
		bool thirdDone;
};

Foo::Foo()
{
	firstDone = secondDone = thirdDone = false;
}

void Foo::wait(int wait_ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(wait_ms));
}


void Foo::first()
{
	printf("first done\n");
	firstDone = true;
}

void Foo::second()
{
	bool firstFinished = false;
	while (!firstFinished)
	{
		while (!checkerMtx.try_lock())
		{
			wait(SLP_MS);
		}
		
		firstFinished = firstDone;
		checkerMtx.unlock();
		wait(SLP_MS);
	}
	printf("second done\n");
	secondDone = true;
}

void Foo::third()
{
	bool secondFinished = false;
	while (!secondFinished)
	{
		while (!checkerMtx.try_lock())
		{
			wait(SLP_MS);
		}
		
		secondFinished = secondDone;
		checkerMtx.unlock();
		wait(SLP_MS);
	}
	printf("third done\n");
	thirdDone = true;
}

int main()
{
	Foo foo = Foo();
	std::thread thread_3(Foo::third, &foo);
	std::thread thread_2(Foo::second, &foo);
	std::thread thread_1(Foo::first, &foo);
	thread_3.join();
	thread_2.join();
	thread_1.join();
}
