#import <iostream>
#import <vector>

using namespace std;

vector<int> moveZerosToEnd(const vector<int>& arr)
{
	// your code goes here
  
  // go through the array, count zeros
  // the first zero, i have to move all the numbers back one,
  // where we loop through the array,
  // and each time we find zero, we increment a counter
  // move all the numbers to the end back one spot.
  // time complexity, O(N^2)
    // if we have an array of all zeros.
    // we go to the first zero
    // we have shift all back 
    // (n - 1) (n - 2) (n - 3)
    
  // space complexity O(1)
  
  
  // we make a new vector the same size of the old one, we initialize it to be all zeros.
  // we go through the array and copy over into the new vector if its a not a zero.
  // O(N)
  // O(N)
  
  // another option
  // we ve a read pointer and a write pointer. 
  // both start at 0.
  // as we read array, if value we read is not a zero,
  // set it to write and increment write.
  // this works as we've already delt with earlier writes, so its fine to overwrite them.
  // at the end, fill in zeros.
  
  // time complexity O(N)
  // space complexity O(1)
  
  std::vector<int> arr2 = arr;
  
  int write_index = 0;
  for (int read_index = 0; read_index < arr2.size(); read_index++)
  {
    if (arr2[read_index] != 0)
    {
      arr2[write_index] = arr2[read_index];
      write_index++;
    }
  }
  
  for (int i = write_index; i < arr2.size(); i++)
  {
    arr2[i] = 0;
  }
  return arr2;
}

int main() 
{
	return 0;
}
