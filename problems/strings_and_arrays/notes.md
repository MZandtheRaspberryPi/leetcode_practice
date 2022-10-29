# hash tables
function to take a key and make an integer, hash it, maps to index in array. but this would need big array.
so often do a linked list at index hash(key), to avoid collisions. or implement with binary search tree. then can guarantee O(log(n)) lookup time, since can keep
tree balanced. also, can use less space, as dont need to allocate large array at start.

# dynamically sized array
will double when full. gives O(1) access on avg.

# string buffer
when concatenating a list of string, run time is O(x + 2x + .. + x) which reduces to O(xn^2). String buffer helps as it makes an array of strings
and only copies to a string when nescessary.

