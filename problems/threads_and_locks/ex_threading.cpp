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
