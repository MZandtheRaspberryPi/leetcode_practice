/*
write a method to return all subsets of a set.

a set, is it unique? yes. a subset therefore, any combination of its elements.

So for each element, could be in the set, or not.
So we have 2 * 2 * 2 * 2, ect.
So that's 2^n

well, we start with first element in and not in.

so, for element 0, we return a set with {}, and {0}.
for element 1, we return a set with {1} {0, 1}, if its out we already returned
for element 2, we return a set with {2}, {0, 1, 2}, {1, 2}, {0, 2}. so for each set we have to add our number to it. and we also add a new empty set with our number.

so, we could take set as input. create new vector of sets. put empty set into it. iterate over set.
for each element in set, iterate over vector of sets. for each set, add this element to it. then add a new set with just this element.
So O(n) * 2 * n. O(N^2)? but not quite as we don't immediatel have N. it grows.

time complexity here is not correct. should really be 2^n.

Another way, recursively instead of iteratively:
function takes set and index. if index equals size, we are at end, add empty set and return it.
else,
get sets for set and index + 1, and then iterate over and add this element to each.
*/

#include <cstdint>
#include <iostream>
#include <set>
#include <vector>

typedef std::set<uint32_t> uset_t;
typedef std::vector<uset_t> listset_t;

void print_set(const uset_t& my_set)
{
	for (auto& val : my_set)
	{
		std::cout << val << ",";
	}
	std::cout << std::endl;
}

uint32_t get_from_set(const uset_t& my_set, size_t index)
{
	size_t counter = 0;
	for (auto& val : my_set)
	{
		if (counter == index)
		{
			return val;
		}
		counter++;
	}
	return 0;
}

listset_t get_all_subsets(const uset_t& my_set, size_t index)
{
	if (index == my_set.size())
	{
		listset_t all_subsets;
		uset_t empty_subset;
		all_subsets.push_back(empty_subset);
		return all_subsets;
	}
	else
	{
		// first get all other subsets
		// then add this ele to each other subset
		listset_t all_subsets = get_all_subsets(my_set, index + 1);
		auto my_val = get_from_set(my_set, index);
		uint32_t subset_size = all_subsets.size();
		for (uint32_t i = 0; i < subset_size; i++)
		{
			const uset_t& subset = all_subsets[i];
			uset_t new_subset = subset;
			new_subset.insert(my_val);
			all_subsets.push_back(new_subset);
		}
		return all_subsets;
	}
	
}



int main() {
	std::cout << "getting sets" << std::endl;
	uset_t my_set = {1, 3, 5, 8, 10, 15, 33, 78, 101};
	for (auto& val : my_set)
	{
		std::cout << val << ",";
	}
	std::cout << std::endl;
	listset_t all_subsets = get_all_subsets(my_set, 0);
	std::cout << "got sets" << std::endl;
	for (uset_t& subset: all_subsets)
	{
		print_set(subset);
	}
}