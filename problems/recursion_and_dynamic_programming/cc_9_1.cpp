/* 
a child is runnign up saircase with n steps and can run either 1, 2, or 3 steps at a time.

implement a method to count how many ways the child can run up the stairs.

if they could just do 1 step at a time, would be only 1 way.
if they could do 1 or 2 steps at a time, then we would have to do 1 for everything, then first for 2 and rest for one,
and through like that. and then first 2 for 2 and rest for one, and like that.

we could have a method taking a int ref to count, and const int ref n for size of stairs.
then we do:
recurse1step();
recurse2step();
recurse3step();

each time we recurse, add value to count, and check if over. if over, decrement count and return.
if under, we recurse again.

in time complexity, O(3^N), because we try all possible combinations of the three parameters.
in storage complexity, O(3^N) as well.

feedback from solution:
I did get write answer, but could do it with way less code. Think of a top down approach.
To get to the last step, could do single, double or triple hop. so might have gone one hop from n-1, two from n-2 or 3 from n-3.
hence we can sum up ways of reaching last three steps.

also, with my solution, implementing caching would be much harder, ie no good way to speed it up.

*/ 

#include <iostream>
#include <unordered_map>

const int STP_VAL_0 = 0;
const int STP_VAL_1 = 1;
const int STP_VAL_2 = 2;
const int STP_VAL_3 = 3;


void countStairOptions(const int& n, int& options_count, int& count, const int& step_value)
{
	count += step_value;
	
	if (count < n)
	{
		countStairOptions(n, options_count, count, STP_VAL_1);
		countStairOptions(n, options_count, count, STP_VAL_2);
		countStairOptions(n, options_count, count, STP_VAL_3);
	}
	else if (count > n)
	{
		count -= step_value;
		return;
	}
	else // (count == n)
	{
		options_count++;
		count -= step_value;
		return;
	}
	count -= step_value;
	return;
}

int countStairOptions(int n)
{
	int options_count = 0;
	int count = 0;
	countStairOptions(n, options_count, count, STP_VAL_0);
	return options_count;
}

int countWaysOptimal(int n)
{
	if (n < 0) return 0;
	else if (n == 0) return 1;
	else {
		return countWaysOptimal(n - 1) + countWaysOptimal(n-2) + countWaysOptimal(n-3);
		
	}
}

int countWaysOptimalWithCaching(int n)
{
	static std::unordered_map<int, int> map_cache;
	if (n < 0) return 0;
	else if (n == 0) return 1;
	else if (map_cache.find(n) != map_cache.end()) return map_cache[n];
	else {
		map_cache[n] = countWaysOptimalWithCaching(n - 3) + countWaysOptimalWithCaching(n - 2) + countWaysOptimalWithCaching(n - 1);
		return map_cache[n];
	}
	
}

int main()
{
	int res = countStairOptions(10);
	std::cout << "10: " << res << std::endl;
	res = countWaysOptimal(10);
	std::cout << "10: " << res << std::endl;
	res = countWaysOptimalWithCaching(10);
	std::cout << "10: " << res << std::endl;
}