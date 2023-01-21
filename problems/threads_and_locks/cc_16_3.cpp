/*

philosophers sitting table, one chopstick between each. need both to eat, pick
up left b/f right. deadlock could happen if all go for left at same time.

using threads and locks, implement sim of dining philosophers problem that
prevents deadlock.

so for a deadlock to happen, we need:
mutual exclusion
hold and wait
preclusion, one process cant forcibly get anothers resources
circular deps, p1 can request resource p2 holds while p2 request resource p1
holds

so can we eliminate circular dependencies.
can we perhaps check if the left philosopher is requesting a resource, and the
left chopstick is held. if so, wait it out.

we have a vector holding mutexes for each chopstick.
we have a mutex for that vector.

we have a thread for each philosopher. Each will eat a certain number of times.
each philosopher has an index indicating where they sit in the table. index 0
indicates philosopher sits between chopstick n - 1 and chopstick 0. index 1
indicates philosopher sits between chopstick 0 and chopstick 1.

each philsopher takes const ref to vectors. each philosopher will use a function
to check left chopstick state. this function will get a lock, check state, and
return a copy. if the chopstick is held, we will wait. and check again every m
milliseconds. if the chopstick is free, we will get a lock on the chopstick

g++ -std=c++0x -pthread cc_16_3.cpp -o tst.exe

feedback from solution, this may have gotten around the issue, but also may have not.
we dont release a left lock when we do get it, tho we check if it is currently available before we grab it.
instead of a deadlock, we could end up simply waiting in a sleep loop. to really avoid deadlock, we would need to release left if we
can't get right.

*/
#include <chrono>
#include <mutex>
#include <stdio.h>
#include <string>
#include <thread>
#include <vector>

#define SLP_MS 20

bool getChopstickLockIfAvailable(const int chopstick_to_check,
                                 std::vector<std::mutex> &chopstick_mutexes,
                                 std::mutex &chopstick_mutexes_mutex) {
  bool got_lock = chopstick_mutexes_mutex.try_lock();
  if (!got_lock) {
    return false;
  }

  got_lock = chopstick_mutexes[chopstick_to_check].try_lock();
  chopstick_mutexes_mutex.unlock();
  return got_lock;
}

bool releaseChopstickLockIfAvailable(const int chopstick_to_check,
                                     std::vector<std::mutex> &chopstick_mutexes,
                                     std::mutex &chopstick_mutexes_mutex) {
  bool got_lock = chopstick_mutexes_mutex.try_lock();
  if (!got_lock) {
    return false;
  }

  chopstick_mutexes[chopstick_to_check].unlock();
  chopstick_mutexes_mutex.unlock();
  return true;
}

int getLeftChopstick(const int philosopher_index,
                     std::vector<std::mutex> &chopstick_mutexes,
                     std::mutex &chopstick_mutexes_mutex) {
  bool got_lock = chopstick_mutexes_mutex.try_lock();
  if (!got_lock) {
    return -1;
  }

  int potential_left_chopstick = philosopher_index - 1;
  int left_chopstick = potential_left_chopstick >= 0
                           ? potential_left_chopstick
                           : chopstick_mutexes.size() - 1;
  chopstick_mutexes_mutex.unlock();
  return left_chopstick;
}

int getRightChopstick(const int philosopher_index,
                      std::vector<std::mutex> &chopstick_mutexes,
                      std::mutex &chopstick_mutexes_mutex) {
  bool got_lock = chopstick_mutexes_mutex.try_lock();
  if (!got_lock) {
    return -1;
  }

  int potential_right_chopstick = philosopher_index + 1;
  int right_chopstick = potential_right_chopstick >= chopstick_mutexes.size()
                            ? 0
                            : potential_right_chopstick;
  chopstick_mutexes_mutex.unlock();
  return right_chopstick;
}

void eatFood(const int foods_to_eat, const int philosopher_index,
             std::vector<std::mutex> &chopstick_mutexes,
             std::mutex &chopstick_mutexes_mutex) {

  int counter = 0;
  while (counter < foods_to_eat) {
    int left_chopstick = -1;
    while (left_chopstick == -1) {
      left_chopstick = getLeftChopstick(philosopher_index, chopstick_mutexes,
                                        chopstick_mutexes_mutex);
      std::this_thread::sleep_for(std::chrono::milliseconds(SLP_MS));
    }
    int right_chopstick = -1;
    while (right_chopstick == -1) {
      right_chopstick = getRightChopstick(philosopher_index, chopstick_mutexes,
                                          chopstick_mutexes_mutex);
      std::this_thread::sleep_for(std::chrono::milliseconds(SLP_MS));
    }

    while (!(getChopstickLockIfAvailable(left_chopstick, chopstick_mutexes,
                                         chopstick_mutexes_mutex))) {

      std::this_thread::sleep_for(std::chrono::milliseconds(SLP_MS));
    }

    while (!(getChopstickLockIfAvailable(right_chopstick, chopstick_mutexes,
                                         chopstick_mutexes_mutex))) {

      std::this_thread::sleep_for(std::chrono::milliseconds(SLP_MS));
    }
    printf("philosopher %d ate\n", philosopher_index);
    counter++;
    while (!(releaseChopstickLockIfAvailable(left_chopstick, chopstick_mutexes,
                                             chopstick_mutexes_mutex))) {

      std::this_thread::sleep_for(std::chrono::milliseconds(SLP_MS));
    }

    while (!(releaseChopstickLockIfAvailable(right_chopstick, chopstick_mutexes,
                                             chopstick_mutexes_mutex))) {

      std::this_thread::sleep_for(std::chrono::milliseconds(SLP_MS));
    }
  }
}

class Philosopher
{
	public:
	  Philosopher(std::mutex* left_chopstick,
								std::mutex* right_chopstick,
								std::string name);
		bool pickUp();
		void putDown();
		void eat(int number_bites);
	private:
	  std::string name_;
	  std::mutex* left_chopstick_mtx_;
		std::mutex* right_chopstick_mtx_;
};

Philosopher::Philosopher(std::mutex* left_chopstick,
								std::mutex* right_chopstick,
								std::string name) : left_chopstick_mtx_(left_chopstick),
									right_chopstick_mtx_(right_chopstick),
									name_(name) {}

bool Philosopher::pickUp()
{
	left_chopstick_mtx_->lock();
	if (!right_chopstick_mtx_->try_lock())
	{
		left_chopstick_mtx_->unlock();
		return false;
	}
	return true;
}

void Philosopher::putDown()
{
	right_chopstick_mtx_->unlock();
	left_chopstick_mtx_->unlock();
}

void Philosopher::eat(int number_bites)
{
	int counter = 0;
	while (counter < number_bites)
	{
		if (pickUp())
		{
			counter++;
			putDown();
		}
	}
	
}

void runSim()
{
	const int foods_to_eat = 50;
  const int N = 4;
  std::vector<std::mutex> chopstick_mutexes(N);
  std::mutex mutex_of_mutexes;

  std::vector<std::thread> thread_vect(N);
	
	/*
  for (int i = 0; i < N; i++) {
    thread_vect[i] =
        std::thread(eatFood, foods_to_eat, i, std::ref(chopstick_mutexes),
                    std::ref(mutex_of_mutexes));
  }
	*/
	
	std::vector<Philosopher> philosophers;
	
	philosophers.push_back(Philosopher(&chopstick_mutexes[N-1], &chopstick_mutexes[0], "0"));
	for (int i = 1; i < N - 1; i++) {
    philosophers.push_back(Philosopher(&chopstick_mutexes[i-1], &chopstick_mutexes[i], std::to_string(i)));
  }
	philosophers.push_back(Philosopher(&chopstick_mutexes[N-2], &chopstick_mutexes[N-1], std::to_string(N-1)));

  for (int i = 0; i < N; i++) {
    thread_vect[i] =
        std::thread(Philosopher::eat, &philosophers[i], foods_to_eat);
  }


  for (std::thread &thread : thread_vect) {
    thread.join();
  }
	
}



int main() {
	for (int i = 0; i < 100000; i++)
	{
		runSim();
		printf("sim ran %d\n", i);
	}
}