/*
sort array, nlogn. then go through and for each entry, find complement with limit - entry.
binary search for that in array, and if find, then set 2 indices and return.
if not, continue.
if at end, return arr.
time n logn, dominated by sort.

or, if can use storage,
create a map. go through array.
for each entry in the array, check if its complement is in the map. if it is, set and return array.
if not, add itself to the map.

if get to end, return.
time would be O(N)
storage would be O(N).

*/

#include <iostream>
#include <map>
#include <vector>

using namespace std;

bool isEntryInMap(const map<int, int>& map_to_search, const int& val)
{
  return map_to_search.find(val) != map_to_search.end();
}

vector<int> getIndicesOfItemWeights( const vector<int>& arr, int limit)
{
  vector<int> solution;
  map<int, int> known_entries_map;
  for (int i = 0; i < arr.size(); i++)
  {
    int val = arr[i];
    int complement = limit - val;
    if (isEntryInMap(known_entries_map, complement))
    {
      int complement_index = known_entries_map[complement];
      int val_index = i;
      int first_index;
      int second_index;
      if (complement_index > val_index)
      {
        
        first_index = complement_index;
        second_index = val_index;
      }
      else
      {
        second_index = complement_index;
        first_index = val_index;
      }
      solution.push_back(first_index);
      solution.push_back(second_index);
      return solution;
    }
    else
    {
      known_entries_map[val] = i;
    }
  }
  return solution;
}

int main() {
  return 0;
}
