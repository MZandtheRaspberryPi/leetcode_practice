/*
write a method to sort an array of strings so that all the anagrams are next to each other
*/

// end idea
// sort each string in array
// then sort the array using comparison function of std::string.compare() but return bool
// time compexity depends on sort algorithm used. O(Nlogn) likely
// storage compexity depends on sort algorithm used. O(N) for merge sort.

// alternative idea
// make hash table where each key is anagram, value is vector of permutations
// loop over vector, sort string, check if in hash table, if so add to perm vect, if not add key and add perm vect
// then at the end loop over hash table and stitch together end vector

// original idea
// make an array, letter_counts, of size arr[size], 26
// loop over array, and for each string loop for i + 0 to i + 25, and loop over string and add 1 to letter_counts[string_index][i]
// then, create new vector size of old one
// create an index for anagrams starting at arr.size() - 1
// create an index for non-anagrams starting at 0
// loop over letter_counts, and if its already equal to anagram_index continue
// else for each alphabet check every other alphabet and if its equal set that entry to anagram_index as well as this entry to anagram_index
// when looped over whole array, if our index in new vector is still non-anagram index, set vector of that index and then increment that by one.
// at the end make a new vector, loop over to it, and set entries equal to the index in the indexvector
// runtime is O(N^2)
// storage is O(N)

#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>

void merge(std::string &arr, int start, int middle, int end)
{
	std::string helper;
	helper.resize(arr.size());
	
	for (int i = start; i <= end; i++)
	{
	  helper[i] = arr[i];
	}
	
	int helper_left = start;
	int helper_right = end;
	int current = start;
	
	// iterate through helper. compare left and right half,
	// copying back smaller element from two halves to original arr.
	while (helper_left <= middle && helper_right <= end)
	{
		int left_val = helper[helper_left];
		int right_val = helper[helper_right];
		if (left_val <= right_val)
		{
		  arr[current] = helper[helper_left];
			helper_left++;
		}
		else
		{
		  arr[current] = helper[helper_right];
			helper_right++;
		}
		current++;
	}
	
  // copy rest of left side of array to target array
	int remaining = middle - helper_left;
	for (int i = 0; i <= remaining; i++)
	{
	  arr[current + i] = helper[helper_left + i];
	}
}


void merge_sort(std::string &arr, int start, int end)
{
  if (start < end)
  {
    int middle = (start + end) / 2;
		merge_sort(arr, start, middle);
		merge_sort(arr, middle + 1, end);
		merge(arr, start, middle, end);
  }
}

void sort_string_array(std::string &arr)
{
	merge_sort(arr, 0, arr.size() - 1);
	return;
}

bool compare_string(std::string string1, std::string string2)
{
	return string1.compare(string2) < 0;
}

int main()
{
	printf("%d\n", std::string("a").compare(std::string("cb")));
	std::vector<std::string> a{"aab", "aba", "tra", "baa", "cra", "a", "cd"};
	for (int i = 0; i < a.size(); i++)
	{
		sort_string_array(a[i]);
	}
	for (int i = 0; i < a.size(); i++)
	{
		printf("%s\n", a[i].c_str());
	}
	printf("\n");
	std::sort(a.begin(), a.end(), compare_string);
	for (int i = 0; i < a.size(); i++)
	{
		printf("%s\n", a[i].c_str());
	}
}