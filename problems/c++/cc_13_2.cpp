/*
compare and contrast a hash table and an stl map. how is hash table implemented?

if the number of inputs is small, which datastructure options can be used instead of
a hash table?

a stl map uses balanced trees internally to store data.

a hash table typically allocates a big array and then uses a function to transform keys into indices in that array.
it may use a linked list at each index to avoid collissions.

if the number of inputs is small, we may want to avoid allocating that big array. instead we could consider a map, 
implemented using balanced trees.

feedback
in c++, a stl map is actually associative container, and ordered. typically implemented w/ balanced trees.
so O(logn) lookup time. a hash table, usually array with linked lists to avoid collisions, constant lookup time 
but we need a good hash function.

hash table is constant lookup then.

*/