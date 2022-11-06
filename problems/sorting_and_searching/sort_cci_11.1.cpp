/*
You are given two sorted arrays, A and B, where A has large enough buffer at the end to hold B.
Write method to merge B into A in sorted order.

*/


#include <vector>
#include <stdio.h>

void sort(std::vector<int>& a, int a_size, std::vector<int>& b)
{
  // iterate through B, from end to start, for each entry in B, iterate over A from end to start and find where a is smaller than b. at that point
  // shift all of a back by length b - (length b - b index) and put b in.
  // time complexity O(AB) worst case where A is length of A and B is length of B, if same length then O(N^2)

  int a_index = a.size() - b.size() - 1;
  int a_buffer_index = a.size() - 1;
  int b_index = b.size() - 1;


  while (b_index > -1)
  {
	while (b[b_index] < a[a_index])
	{
	  a[a_buffer_index] = a[a_index];
	  a_buffer_index--;
	  a_index--;
	}
	
	a[a_buffer_index] = b[b_index];
	a_buffer_index--;
	b_index--;
  }

}

int main()
{
  std::vector<int> a{0, 2, 3, 4};
  std::vector<int> b{1, 3, 6, 7};
  a.resize(a.size() + b.size());

  sort(a, 4, b);
  for (int i = 0; i < a.size(); i++)
  {
	printf("%d\n", a[i]);  
  }
  
  std::vector<int> c{0, 5, 7, 10};
  std::vector<int> d{1, 1, 2, 15, 16, 17, 20, 25};
  c.resize(c.size() + d.size());

  sort(c, 4, d);
  for (int i = 0; i < c.size(); i++)
  {
	printf("%d\n", c[i]);
  }
  
  printf("fin.");

}

