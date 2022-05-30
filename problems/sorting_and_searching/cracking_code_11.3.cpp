/*
given a sortrd array of n integers that has
been rotated an unkown number of times write
code to find an element in the array. assume
originally sorted in increasing order
*/

/*
binary search. either left subarray is normal or right subarray from middle is normal. so calculate middle, chrck if vak and if val return middle.
    if right less than left return -1, gone too far.
    then check if left array normal by chrcking if val at middle is greater than val at left. if so, use that left subarray to fetermine which subarray to check. if value is greater than smallest left and less than mifdle search left, else search right.
   else check if right subarray is normal by chrcking if middle val is less than right val. if so, use right to determine whete to search. if middle val is less than vakue, and value is less than right val, search right subarray. else, search left.
   if the left val is equal to middle, check the right val vs middle. if diff, search right. if the same, we gotta search both so hrck left and if return is -1 then check right and return right.
   return -1.

   will run in O(logn)) if unqiue values, if many duplicates gets close to o(n) as wr havr to search left and right halves.

5 1 2 3 4

*/


#include <stdio.h>
#include <vector>


int bin_search_rotation(std::vector<int> array, int value, int left, int right)
{
    int middle = (right - left) / 2 + left;
    if (array[middle] == value) {return middle;}
    if (right < left) {return -1;}
    // either left or right subhalf is sorted normally
    // left half sorted normally, use that to determine what half to search
    if (array[left] < array[middle])
    {
        if (array[middle] >= value && value >= array[left])
        {
            return bin_search_rotation(array, value, left, middle - 1);
        }
        else
        {
            return bin_search_rotation(array, value, middle + 1, right);
        }
    }
    // right is normally ordered
    else if (array[left] > array[middle])
    {
        if (array[middle] <= value && value <= array[right])
        {
            return bin_search_rotation(array, value, middle + 1, right);
        }
        else
        {
            return bin_search_rotation(array, value, left, middle - 1);
        }
    }
    else if (array[middle] == array[left])
    {
        if (array[middle] == array[right])
        {
            int return_val = bin_search_rotation(array, value, left, middle - 1);
            if (return_val == -1)
            {
                return_val = bin_search_rotation( array, value, middle + 1, right);
            }
            return return_val;
        }
        else
        {
            return bin_search_rotation(array, value, middle + 1, right);
        }
    }
    return -1;

}

int find_element_in_rotated_arr(std::vector<int> array, int value)
{
    return bin_search_rotation(array, value, 0, array.size() - 1);
}


// if 1 rotation, can check left and right pints vs middle to find what side rotation in
// if 2 rotations 
// 12345678
// 34567812
// 81234562

// IF 4 rotations
// 12345678
//34567812
// more than 2 rotations doesnt matter if sorted.

int main()
{
    std::vector<int> arr = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
    int index = find_element_in_rotated_arr(arr, 5);
    printf("found %d", index);
    std::vector<int> arr2 = {5, 1, 2, 3, 4};
    index = find_element_in_rotated_arr(arr2, 3);
    printf("found %d", index);
}
