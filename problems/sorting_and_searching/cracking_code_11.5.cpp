/*
given sorted array of strings which is interspersed with empty strings, write a method to find the location of a given string.

binary search variant? if middle is empty then search outwarda left first, then right till non empty. this will be efficient deoending on how many spaces present. if many o(n).


"" "a" "" "" "c"

*/

#include <stdio.h>
#include <vector>
#include <string>


const std::string EMPTY{""};
int searchR(std::vector<std::string> arr, std::string search_str, int low, int high);


int search(std::vector<std::string> arr, std::string search_str)
{
    if (search_str == EMPTY)
    {
        return -1;
    }
    return searchR(arr, search_str, 0, arr.size() - 1);
}

int find_nearest_non_empty_str(std::vector<std::string> arr, int start_point)
{
    int index = 0;
    int return_val = -1;
    bool found = false;
    while (!found && index < arr.size())
    {
        index++;
        if (start_point - index >= 0 &&
            arr[start_point - index] != EMPTY)
        {
            found = true;
            return_val = start_point - index;
        }

        if (start_point + index <= arr.size() - 1 &&
            arr[start_point + index] != EMPTY)
        {
            found = true;
            return_val = start_point + index;
        }
    }
    return return_val;
}

int searchR(std::vector<std::string> arr, std::string search_str, int low, int high)
{
    int mid = (low + high) / 2;
    int transformed_mid = mid;
    // check if mid is an empty string and find nearest non-empty string
    if (arr[mid] == EMPTY)
    {
        transformed_mid = find_nearest_non_empty_str(arr, mid);
        if (transformed_mid == -1)
        return transformed_mid;
    }
    if (arr[transformed_mid] == search_str)
    {
        return transformed_mid;
    }

    while (arr[low] == EMPTY &&
           low < transformed_mid)
    {
        low++;
    }

    while (arr[high] == EMPTY &&
           high > transformed_mid)
    {
        high--;
    }

    if (arr[transformed_mid].compare(search_str) < 0)
    {
        return searchR(arr, search_str, mid + 1, high);
    }
    else
    {
        return searchR(arr, search_str, low, mid - 1);
    }
}

int main()
{
    std::vector<std::string> arr;
    std::string tmp;
    tmp = "";
    arr.push_back(tmp);
    tmp = "aaple";
    arr.push_back(tmp);
    tmp = "";
    arr.push_back(tmp);
    arr.push_back("banana");
    arr.push_back("");
    arr.push_back("");
    arr.push_back("love");
    for (int i = 0; i < arr.size(); i++)
    {
        printf("'%s' ", arr[i].c_str());
    }
    printf("\n");
    int res = search(arr, "love");
    printf("found: %d\n", res);

    arr.clear();
    for (int i = 0; i < 10; i++)
    {
      arr.push_back("");
      arr.push_back("");
      arr.push_back("goodfellow");
    }

    arr.push_back("opple");
    for (int i = 0; i < 3; i++)
    {
       arr.push_back("zone\n");
    }
    for (int i = 0; i < arr.size(); i++)
    {
        printf("'%s' ", arr[i].c_str());
    }
    res = search(arr, "opple");
    printf("found: %d\n", res);
}
