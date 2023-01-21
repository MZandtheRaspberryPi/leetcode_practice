# Threading in C++

C++ 11 gave us <thread> header with the `std::thread` class. C++14 gave us reader-writer locks. C++17 gave us parallel algorithms in the STL standard template library.
```
#include <chrono>
#include <cstdio>
#include <string>
#include <thread>

void speakWord(std::string str)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
  printf("%s\n", str.c_str());
}

int main()
{

  std::thread thread_a(speakWord, "hi from a");
  std::thread thread_b(speakWord, "hi from b");
  printf("Threads started\n");
  thread_a.join();
  thread_b.join();
}

```

C++20, atomic smart ptrs, std::future extensions, latches and barriers, coroutines, transactional memory, task blocks

Parallelism, same program many times, at once, but with different data. Many http requests for example. Concurrency, shared memory location.

We can use thread pools to manage thread objects and recreate them and so on. Certain amount of threads, when one done go back to pool for new instructions.

Parallelism, can mark functions as synchronous or parallel. if parallel, use up more cpu resources, faster. but better have no dependencies on
other functions as dont know which is first. 

overhead to multithreading, but can handle more use cases.

```

std::vector<std::thread> threads;
for (...)
{
  std::thread thread(blah, "blah);
	threads.push_back(thread);
}

for (std::thread& thread : threads)
{
	thread.join();
}

```

## examples 
email server, let many users get their email by allocating fixed resources to serve em.


## Synchronization and Locks
Threads share memory, if both read/modify var at same time race condition.

Got mutex in c++ 11.

```
#include <chrono>
#include <cstdio>
#include <mutex>
#include <string>
#include <thread>

std::mutex mutex_a;
int a = 0;

void printA(std::string thread_name)
{
  mutex_a.lock();
  printf("%s: ", thread_name.c_str());
	std::this_thread::sleep_for(std::chrono::seconds(1));
  printf("%d\n", a);
	mutex_a.unlock();
}

int main()
{
  std::thread thread_a(printA, "thread a");
	std::thread thread_b(printA, "thread b");
	thread_a.join();
	thread_b.join();

}

or 

 const std::lock_guard<std::mutex> lock(mutex_a);
```

## deadlocks and deadlock prevention
deadlock is when thread waiting for object lock that another thread holds, and second thread waiting for obj lock that first thread holds. they wait forever.

for a deadlock to occur, must have all 4 of following conditions:
1. Mutual Exclusion: only one process can access resource at a given time (limited access to resource).
2. Hold and wait: processes already holding resources can request additional resources.
3. No preemption: one process cannot forcibly remove another processes resources
4. circular wait: two or more processes can form circular chain where each process is waiting on another resource in the chain.
to prevent deadlock, remove any of the above conditions. but tricky as some are difficult to satisfy. removing 1 is difficult as many resources
can only be used by 1 process at a time, like printers. Most deadlock prevention algos remove condition 4, circular wait.