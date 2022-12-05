#include <algorithm>
#import <iostream>
#import <vector>

using namespace std;

// absolute sorting
// get an array, we want to sort it so smalle0r absolute values come first
// in caes where the abs same, then neg first

/*

Go through the array, and for each item in the array, check all the other items and find the min of absolute.
tmp variable to store the value, and another to store the index.
compare the absolute value of my item, to the absolute of others
and if less than, i would swap my two values in the array
if equal to, i would check the signs, and if my other is negative, then swap them.
else continue.


time: O(N^2)


or use built in sorting algo
time O(nlogn)
storage O(N)

feedback, had indexing error, didnt get running. tho right answer. also, didnt see const on thingy.



*/

bool smallerThan(int a, int b)
{
   if (abs(a) < abs(b))
   {
     return true;
   }
  else if (abs(a) == abs(b))
  {
    return a < b;
  }
  else
  {
    return false;
  }

}

vector<int> absSort(const vector<int>& arr)
{
  vector<int> result = arr;
  for (int i = 0; i < result.size(); i++)
  {
    int tmp_index = i;
    for (int j = i + 1; j < result.size(); j++)
    {
      if (smallerThan(result[j], result[tmp_index]))
      {
        tmp_index = j;
      }
    }
    if (tmp_index != -1)
    {
      int tmp = result[tmp_index];
      result[tmp_index] = result[i];
      result[i] = tmp;
    }
  }
	return result;
}

int main()
{
	return 0;
}
