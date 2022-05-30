# Common Sorting Algorithms

Bubble sort
* runtime: O(n^2) avg and worst case
* Mem: O(1)
* Start at beg of array and swap first two elements if first greater than second. then go to next pair, and so on, continuously sweeping till sorted.

Selection sort
* runtime: O(n^2) avg and worst case
* mem: O(1)
* find smallest element using linear scan and move to front. then find second smallest and move it, linear scan.

Merge sort
* runtime O(n Log(n)) avg and worst case
* Mem: depends
* divide array in half, sort halves, merge together. each half has same sorting algo applied. eventually, merging two single element array. merge does lifting.
* copy elements from target array to help array, keeper track of left and right halves. iterate through helper, copzing smaller element from each half into the array. at end copy remaining elements into target array.

Quick sort
* runtime: O(n Log(n)) avg, O(n^2) worst case.
* mem: O(Log(n))
* Pick a random element and partition array. such that all numbers less than partitioning element come before all elements greater than it. can do it efficiently with series of swaps.
* if we repeatedlz partiion array and sub arrays around element, will eventually be sorted. but, as partitioned element not guaranteed to be median or near, could be slow. hence O(N^2) runtime in worst case.

Radix Sort
* Runtime O(n Log(n)) avg O(kn) worst case
* sorting algo for integers and other data types, as finite bits. iterate through each digit, grouping numbers by each digit.
* if array of ints, first sort first digit so 0s are grouped. then sort each groupings by next digit.
* unlike comparison sorting, radix sorting has worst cse of O(kn) where n number of elements and K is number of passes of sorting algo

# Searching algos
Binary search, get details right like minus and plus ones. also other data structures to extend like binary tree or hash table.
