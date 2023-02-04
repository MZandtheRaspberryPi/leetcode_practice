/*
Imagine a robot sitting on upper left corner of an x by y grid.

robot can only move in 2 directions. right and down. how many possible paths
for robot to go (0,0) to (x,y).

follow up
imagine some paths off limits. such robot cant step on em. design algo to find path for robot from
top left to bottom right.

if we take a top down approach, and split the problem into subproblems. we could get to the bottom right from above it, or 
from the left of it. so we can sum up the number of ways to get to those two squares.

so our algo will check current x and current y, starting with the end.
if x == 0 && y == 0, return 1
if x < 0 || y < 0 return 0
if x > 0 count += check x --.
if y > 0 count += check y --.
return count


x x x
x x x
x x x

lets say we had to avoid some paths. well, if we can mark indices of paths we cant follow. For instance, we store a matrix of x, y, size
and we store bool there to indicate if allowed or not. So then we can do constant lookup, but in exchange for X*Y storage complexity.


feedback from solution.
We can use the n choose r, binomial expression. As each left/up choice, if 2x2 map, there are
4 total steps to take. We have to do 2 left and 2 up.

number of ways of selecting x items from n total items.
n!/(r!(n-r)!

in our problem, if X is left and Y is up.
(X+Y)!/(X!((X+Y) - X)!)
(X + Y)! / X!Y!

also, second part, didnt realize they now wanted a path, not number of possible paths.

For this, similar approach, but you can check if you've already been somewhere to speed up the checking. cache em.


*/

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

int checkRobotPaths(int x, int y)
{
	
	if (x == 0 && y == 0)
	{
		return 1;
	}
	else if (x < 0 || y < 0)
	{
		return 0;
	}
	else
	{
		return checkRobotPaths(x - 1, y) + checkRobotPaths(x, y-1);
	}
}

// what about with caching? we could try and store the result at prior squares, with a pair perhaps.
// have a vector to cache stuff and check if -1, or 0 or 1.


int checkRobotPathsWithCaching(int x, int y)
{
	
	static std::vector<std::vector<int>> cached_points;
	if (cached_points.size() <= x)
	{
		cached_points.resize(x + 1);
	}
	if (cached_points[0].size() <= y)
	{
		for (int i = 0; i < cached_points.size(); i++)
		{
			cached_points[i] = std::vector<int>(y + 1, -1);
		}
	}

	if (((x >= 0 && y >= 0)) && cached_points[x][y] != -1 )
	{
		return cached_points[x][y];
	}
	
	if (x == 0 && y == 0)
	{
		return 1;
	}
	else if (x < 0 || y < 0)
	{
		return 0;
	}
	else
	{
		int left_path = checkRobotPaths(x - 1, y);
		int up_path = checkRobotPaths(x, y-1);
		
		cached_points[x][y] = (left_path > 0) || (up_path > 0);
		
		return left_path + up_path;
	}
	
}

long factorial(int x)
{
	long result = 1;
	for (long i = 1; i <= x; i++)
	{
		result *= i;
	}
	return result;
}

int checkRobotPathsOptimal(int x, int y)
{
	return (factorial(x+y)/(factorial(x) * factorial(y)));
	
}

int checkRobotPathsWithForbidden(int x, int y, bool** forbidden_paths)
{
	if (x < 0 || y < 0)
	{
		return 0;
	}
	else if (forbidden_paths[x][y])
	{
		return 0;
	}
	else if (x == 0 && y == 0)
	{
		return 1;
	}
	else
	{
		return checkRobotPathsWithForbidden(x - 1, y, forbidden_paths) + checkRobotPathsWithForbidden(x, y-1, forbidden_paths);
	}
}

int main()
{
	int res = checkRobotPaths(2, 2);
	std::cout << "res 2,2: " << res << std::endl;
	res = checkRobotPaths(1, 1);
	std::cout << "res 1,1: " << res << std::endl;
	
	res = checkRobotPathsWithCaching(1, 1);
	std::cout << "res 1,1: " << res << std::endl;
	res = checkRobotPathsWithCaching(2, 2);
	std::cout << "res 2,2: " << res << std::endl;
	res = checkRobotPathsWithCaching(3, 3);
	std::cout << "res 3,3: " << res << std::endl;
	
	res = checkRobotPathsOptimal(1, 1);
	std::cout << "res 1,1: " << res << std::endl;
	res = checkRobotPathsOptimal(2, 2);
	std::cout << "res 2,2: " << res << std::endl;
	res = checkRobotPathsOptimal(3, 3);
	std::cout << "res 3,3: " << res << std::endl;
	
	int num_rows = 3;
	int num_cols = 3;
	// x will be row, y col
	void* rows_ptr = malloc(num_rows * sizeof(void*));
	bool** forbidden_paths = (bool **) rows_ptr;
	for (int i = 0; i < num_rows; i++)
	{
		forbidden_paths[i] = (bool *)malloc(num_cols * sizeof(bool));
		for (int j = 0; j < num_cols; j++)
		{
			forbidden_paths[i][j] = false;
		}
	}
	
	forbidden_paths[1][1] = true;
	
	res = checkRobotPathsWithForbidden(2, 2, forbidden_paths);
	std::cout << "res 2,2: " << res << std::endl;
	for (int i = 0; i < num_rows; i++)
	{
		free(forbidden_paths[i]);
	}
	free(rows_ptr);
	
	
}