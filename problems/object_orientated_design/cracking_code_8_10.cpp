/*
Design and implement a hash table which uses chaining (linking lists) to handle collisions.

for this we could do a hash class that has a list of linked lists of values. and a put and get.
ie, items[i] is a linked list of all objects that collided at i.

seems ok, but if we have a simple hash function using str length, jim and bob map to same index, tho diff keys.
need to search linked list to find object with key, but linked list doesnt have key. hence, store both.

*/

#include<string>
#include<vector>

// holds Cell types
class LinkedList;
class Cell;

int hashCodeOfKey(std::string key, int length_of_unique_vals);

class Hash {
	public:
	  std::vector<Cell*> items;
		
		Hash()
		{
			items.resize(MAX_SIZE);
			// init it to empty cells
		}
		
		void put (std::string key, int value)
		{
			int x = hashCodeOfKey(key, items.size());
			if (items[x] == nullptr)
			{
				// make new linked list
			}
			
			// get linked list, look for items with the same key and replace if found
			
			// make new cell, add it to linked list
		
		}
		
		int get(std::string key)
		{
		  int x = hashCodeOfKey(key, items.size());
			// if null at that x, -1 or something
			// else get linekd list, and search for that key and return its value.
			// return -1 if error
		}
	
	private:
	  const int MAX_SIZE = 10;
	
};

int hashCodeOfKey(std::string key, int length_of_unique_vals)
{
	return key.size() % length_of_unique_vals;
	
}

// cell class holds key and value as private, and has equivalenance function. 

int main()
{
	
}

