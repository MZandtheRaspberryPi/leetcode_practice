/*
in the classic problem of the towers of hanoi.

you have 3 towers and n disks of different sizes
which you can slide onto any tower. puzzle starts
with disks sorted in ascending order of size from top to bottom.
each disk sits on top of an even larger one.

constraints:
only one disk can be moved at a time
a disk is slid off the top of one tower onto the next tower
a disk can only be placed on top of another larger disk.

write a program to move the disks from the first tower to the last using stacks.

so can take from a smaller tower and add to big tower.


kind of a rotating buffer system.
want to get to bottom of second and put on third. so got to empty 2.

hold top of 1 on three, put 1 to second, then can put three to second on top, then 1 to 3, then use 1 as buffer and put back on 3?

simplify
N = 1

1

-

-

/
move 1 to 3.

N = 2

1
2

-

-
move 1 to 2 and then 1 to three and then 2 to three.
second acts as buffer.

N = 3.
Move top 2 to 2, using 3rd as buffer.
then move 3 to 3. then move 2 to three using 1 as buffer.

N = 4

move top 3 to 2 using 3 as buffer
move 4 to 3
move 1 2 to 1 using three as buffer
move 3 to 2
move 1 to 2 buffer
move 2 to 3
move 1 to 3

recursive algo

moveDisks(int n, Tower origin, Tower destination, Tower buffer)
{
	// base case
	if ( n <= 0) return;
	
	// move top n - 1 disks from tower 1 to tower 2, using tower 3 as buffer
	moveDisks(n - 1, Tower1, Tower2, Tower3)
	
	// move top from tower 1 to tower3
	movetop(Tower1, Tower3)
	
	// move top n-1 disks from tower 2 to tower 3, using tower 1 as buffer.
	
}

-

-


*/

#include <stack>
#include <stdio.h>

void setUpTowersHanoi(std::stack<int>* tower_array, int num_towers, int num_disks)
{
	for (int i = num_towers; i > 0; i--)
	{
		tower_array[i - 1] = std::stack<int>();
	}
	
	for (int i = num_disks; i > 0; i--)
	{
		tower_array[0].push(i);
	}
	
}

void printTowers(std::stack<int>* tower_array, int num_towers)
{
	int tmp;
	for (int i = 0; i < num_towers; i++)
	{
		printf("working on tower %d\n", i);
		while (tower_array[i].size() > 0)
		{
			tmp = tower_array[i].top();
			tower_array[i].pop();
			printf("%d\n", tmp);
		}
	}
}

void moveTop(std::stack<int>* tower_array, int origin, int dest)
{
	int tmp = tower_array[origin].top();
	printf("moving %d from %d to %d\n", tmp, origin, dest);
	tower_array[origin].pop();
	tower_array[dest].push(tmp);
}

void moveDisks(std::stack<int>* tower_array, int n, int origin, int destination, int buffer)
{
	if (n > 0)
	{
		moveDisks(tower_array, n - 1, origin, buffer, destination);
		moveTop(tower_array, origin, destination);
		
		moveDisks(tower_array, n - 1, buffer, destination, origin);
	}
}

int main() {
	
	const int N = 15;
	const int NUM_TOWERS = 3;
	std::stack<int> TOWER_ARR[NUM_TOWERS];
	setUpTowersHanoi(TOWER_ARR, NUM_TOWERS, N);
	printf("setup towers\n");
	//printTowers(TOWER_ARR, NUM_TOWERS);
	
	moveDisks(TOWER_ARR, N, 0, 2, 1);
	printf("\n\n");
	printTowers(TOWER_ARR, NUM_TOWERS);
	

}