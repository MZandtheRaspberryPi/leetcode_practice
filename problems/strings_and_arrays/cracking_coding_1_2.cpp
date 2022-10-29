/*
implement a function void reverse(char* str) in c or c++ which reverses null termianted str

we can go through str, until we find null terminator.
then we create tmp char.
we loop to middle of str, then set tmp = str[i], set str[i] to str[arr_length - 1 - i], and then set str[arr_length - 1 -i] to tmp

memory: o(1)
time: o(n)

*/

#include <stdio.h>

void reverse(char* str)
{
	int arr_length = 0;
	while(str[arr_length] != '\0')
	{
		arr_length++;
	}
	
	char tmp;
	for (int i = 0; i < arr_length / 2; i++)
	{
		tmp = str[i];
		str[i] = str[arr_length - 1 - i];
		str[arr_length - 1 - i] = tmp;
	}

}

int main()
{
	const int ARR_SIZE = 10;
	char arr[ARR_SIZE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', '\0'};

	int i = 0;
	while (arr[i] != '\0')
	{
		printf("%c", arr[i]);
		i++;
	}
	
	printf("\n");
	
	reverse(arr);
	
	i = 0;
	while (arr[i] != '\0')
	{
		printf("%c", arr[i]);
		i++;
	}
	
	
	
}