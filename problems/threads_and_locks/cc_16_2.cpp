/*
How would you measure the time spent in a context switch?
before you enter start a thread and increment a counter each unit of time, like every 100 milliseconds.
have a shared variable to exit the thread.
then when you exit context get a lock and exit the thread.

feedback from solution. I was way off here.

context switch refers to an operating system, time spent switching between 2 processes.
IE, bringing waiting process into execution and sending executing process into waiting/terminated state.
in multitasking, this happens when os must bring state info of waiting processes into memory and save state info
of running process.

tricky bits: how do we know when swapping occurs. cant record timestamp of every instruction.
also, scheduling algo of os governs swapping, many kerlen level threads doing context switches. can be interupts, controlling context switches partially.

so, make env so that after p1 executes, task scheduler immediately selects p2 to run. make data channel, like pipe, between
p1 and p2 and have 2 processes play game of ping-pong with data token.

1. p2 blocks awaiting data from p1
2. p1 marks the start time
3. p1 sends token to p2
4. p1 attemts to read response token from p2, induces context switch
5. p2 is scheduled and receives token
6. p2 sends response token to p1
7. p2 attemts read a response token from p1, induces context switch
8. p1 scheduled and reiceives token
9. p1 marks end time.

Td time to deliver token, Tr, time to read token.
time p1 records is T
T = 2*(Td+Tc+Tr)

P1 can compute T. must determien value of Td + Tr.
measure time it takes p1 to send and receive token for itself. wont induce context switch since
p1 running on cpu at time it sent token and wont block to receive it.

play game number of iterations, reduce variability from unexpected kernel interupts, select smallest observed context switch time

its an approximation. we assume p2 selected to run once data token becomes available, but dependent on os task scheudler.


*/

#include <chrono>
#include <mutex>
#include <cstdio>
#include <thread>

class Timer
{
	public:
	  void startTimer();
		void stopTimer();
		int getTimeMilliseconds();
		static Timer* getTimer();
	private:
	  Timer() = default;
		Timer(const Timer& a);
		operator=(const Timer& a);
	  void count();
		
	  std::thread timer_thread_;
		std::mutex stop_thread_mutex_;
		bool stop_thread_;
		int counter_;
		const int milliseconds_to_sleep_ = 20;
		
};

Timer* Timer::getTimer()
{
	static Timer timer_ptr;
	return &timer_ptr;
}

void Timer::startTimer()
{
	counter_ = 0;
	stop_thread_ = false;
	timer_thread_ = std::thread(&count, this);
}

void Timer::count()
{
	while (true)
	{
		if (stop_thread_)
		{
			break;
		}
		{
		std::lock_guard lock(stop_thread_mutex_);
		counter_++;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_to_sleep_));
	}
}

void Timer::stopTimer()
{
		std::lock_guard lock(stop_thread_mutex_);
		stop_thread_ = true;
		timer_thread_.join();
}


int Timer::getTimeMilliseconds()
{
	return counter_ * milliseconds_to_sleep_;
}

void doCaseSwitch(int scenario)
{
	switch (scenario)
	{
	  case 4:
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(400));
			break;
		}
		case 3:
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
			break;
		}
		case 2:
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
			break;
		}
		default:
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			break;
		}
	}
}

int main()
{
	Timer* timer = Timer::getTimer();
	timer->startTimer();
	doCaseSwitch(4);
	timer->stopTimer();
	printf("time: %d milliseconds\n", timer->getTimeMilliseconds());
	
	timer->startTimer();
	doCaseSwitch(8);
	timer->stopTimer();
	printf("time: %d milliseconds\n", timer->getTimeMilliseconds());
}