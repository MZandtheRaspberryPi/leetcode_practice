# Linked Lists

lack of constant time access, recursion oft.

understand if singly linked or doubly linked

# deleting node from singly linked list
given node n, find previous node prev and set prev.next equal to n.next. 
check for null ptr, update head or tail ptr as nescessary.
and consider if node hsould be deallocated if c, c++.

# runner technique
used in many problems. iterate through linked list with 2 pointers at the same time, one ahead of other. could be one fast and slow.

if have 2 linked lists and want to alternate them. could move one fast 2 for each 1 slow. when fast at end, slow at middle. then can move p2 back to front.
and weave em in.

# recursion.
if having trouble, explore if recursion could work. remember takes at least O(N). but remember all recursive algos can be implemented iteratively.