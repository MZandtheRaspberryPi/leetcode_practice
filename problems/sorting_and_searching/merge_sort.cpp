#include <stdio.h>

#define ARR_SIZE 20

void merge_sort(int* arr, int low, int high);
void merge(int* arr, int low, int middle, int high);


void merge_sort(int* arr, int low, int high)
{
  if (low < high)
  {
    int middle = (low + high) / 2;

    merge_sort(arr, low, middle);
    merge_sort(arr, middle + 1, high);
    merge(arr, low, middle, high);
  }
}


void merge(int* arr, int low, int middle, int high)
{
  int helper[ARR_SIZE];

  for (int i = low; i <= high; i++)
  {
    helper[i] = arr[i];
  }

  int helper_left = low;
  int helper_right = middle + 1;
  int current = low;

  while (helper_left <= middle && helper_right <= high)

  {
     if (helper[helper_left] <= helper[helper_right])
     {
        arr[current] = helper[helper_left];
        helper_left++;
     }
     else
     {
        arr[current] = helper[helper_right];
        helper_right ++;
     }
     current++;
  }

  int remaining = middle - helper_left;
  for (int i = helper_left; i <= middle; i ++)
  {
    arr[current] = helper[i];
    current++;
  }

}

int main()
{
  int arr[ARR_SIZE];
  for (int i = 19; i >= 0; i--)
  {
    arr[ARR_SIZE - 1 - i] = i;
    printf("%d ", arr[ARR_SIZE - 1 - i]);
  }
  printf("\n");

  merge_sort(arr, 0, ARR_SIZE - 1);
  for (int i = 0; i < ARR_SIZE; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");

}
