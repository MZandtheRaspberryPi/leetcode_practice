#include <chrono>
#include <iostream>
#include <vector>

int fibonacci(int i) {
  if (i == 0) return 0;
	if (i==1) return 1;
	return fibonacci(i-1) + fibonacci(i - 2);
}



int fibonacciDynamicProgramming(int i) {
	static const int MAX_FIB = 5000;
	if (i > MAX_FIB) return -1;
	static std::vector<unsigned int> dyn_cache = std::vector<unsigned int>(MAX_FIB, 0);
	if (i == 0) return 0;
	if (i == 1) return 1;
  if (dyn_cache[i] != 0) return dyn_cache[i];
	dyn_cache[i] = fibonacciDynamicProgramming(i - 2) + fibonacciDynamicProgramming(i - 1);
	return dyn_cache[i];
}

int main()
{
	
	std::chrono::time_point start_time = std::chrono::system_clock::now();
	//int res = fibonacci(50); // 70 seconds
	int res = fibonacciDynamicProgramming(50);
	std::chrono::time_point end_time = std::chrono::system_clock::now();
	
	std::chrono::duration<double> diff = end_time - start_time;
	std::cout << "took " << diff.count() << "seconds" << std::endl;
}