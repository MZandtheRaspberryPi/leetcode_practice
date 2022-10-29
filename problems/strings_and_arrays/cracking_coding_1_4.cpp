/*
Write a method to replace all spaces in a string wtih '%20'. you may assume string
has sufficient space at the end of the string to hold the additional characters,
and that you are given true length of the string. if implementing in java, perform operation in place.

start at the back of the char array. two pointers to the back. then move one back till first non space char.
from here, loop till at front of array with ptr.
if char is a letter, put it into where back is. if char is a space, do the special logic.
then make slower ptr val = 0, then down then 2, then down, then %, then down.
then move again normally.

Will operate in O(N) of time, o(1) of storage.

feedback on this, didnt catch that we had to calculate and make new string ourselves. for this keep in mind for each space, we need 2 extra characters, not 3 extra.
as space is already there and gives us 1.
*/

#include <stdio.h>

void replaceSpaces(char* arr, int true_size_arr)
{
	int left_index = true_size_arr - 1;
	int right_index = left_index;
	
	while (arr[right_index] != '\0')
	{
		right_index++;
	}
	right_index--;
	
	while (left_index >= 0)
	{
		if (arr[left_index] == ' ')
		{
			arr[right_index] = '0';
			right_index--;
			arr[right_index] = '2';
			right_index--;
			arr[right_index] = '%';
		}
		else
		{
			arr[right_index] = arr[left_index];
		}
		
		left_index--;
		right_index--;
		
	}
	
	
}


int main()
{
	char arr[] = {'a', 'b', ' ', 'c', ' ', 'd', ' ', ' ', ' ', ' ', '\0'};
	
	replaceSpaces(arr, 6);
	
	for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		printf("%c", arr[i]);
	}
	
}