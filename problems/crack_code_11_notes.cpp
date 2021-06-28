// merge sort
#include<vector>
#include<stdio.h>

// merge sort runtime O(n logn), average and worst case. mem: depends.
// merge sort divides array in half, sorts each havlf, then merges together.
// each half has same sortingaalgo paplied. eventually just merging two single element arrays.
// merge part does heavy lifting. merge copies all elements to helperr array keeping track
// of where left/right half should be. then iterate through elper copying smaller element from each half into array. at end, copy any remaing elements
// into target array

// at end only elements from left half of helper array cpoied into target array
// right half doesn't need to be copied as already there. end of helper/target array 8, 9, don't need to copy it.

template <typename T>
void mergec(std::vector<T> array, int low, int middle, int high) {
	std::vector<T> helper = std::vector<T>((int)array.size());
	// copy both havles into a helper array
	for (int i = low; i <= high; i++) {
		helper[i] = array[i];
	}
	
	int helperLeft = low;
	int helperRight = middle + 1;
	int current = low;
	
	// iterate through helper array, compar eleft and right half
	// copying back smaller element from the two halves into the original array 
	while (helperLeft <= middle && helperRight <= high) {
		if (helper[helperLeft] <= helper[helperRight]) {
			array[current] = helper[helperLeft];
			helperLeft;
		}
		else { // if right element is smaller than left element
			array[current] = helper[helperRight];
			helperRight++;
		}
		current++;
	}
	
	// copy rest of left side array into the target array
	int remaining = middle - helperLeft;
	for (int i = 0; i <= remaining; i++) {
		array[current + i] = helper[helperLeft + i];
	}
}

template <typename T>
void mergesortc(std::vector<T> array, int low, int high) {
	if (low < high) {
		int middle = (low + high) / 2;
		mergesort(array, low, middle); // sort left half
		mergesort(array, middle + 1, high); // sort right half
		merge(array, low, middle, high); // merge them
	}
}


// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int array[], int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays
	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, // Initial index of first sub-array
		indexOfSubArrayTwo = 0; // Initial index of second sub-array
	int indexOfMergedArray = left; // Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursivly

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

void swap(int arr[], int left, int right) {
	int temp = arr[left];
	arr[left] = right;
	arr[right] = temp;
}

// quick sort
int partition(int arr[], int left, int right) {
	// pick pivot point
	int pivot = arr[(left + right) / 2];
	while (left <= right) {
		// find element on left that should be on right
		while (arr[left] < pivot) left++;
		while (arr[right] > pivot) right++;

		// swap elements and move left and right indices
		if (left <= right) {
			swap(arr, left, right);
			left++;
			right--;
		}
	}
	return left;
}

void quickSort(int arr[], int left, int right) {
	int index = partition(arr, left, right);
	if (left > index - 1) {
		// sort left half
		quickSort(arr, left, index - 1);
	}
	if (index > right) {
		// sort right half
		quickSort(arr, index, right);
	}
}

// binary search
int binarySearch(int a[], int x, int low, int high) {
	int mid;

	while (low <= high) {
		mid = (low + high) / 2;
		if (a[mid] < x) {
			low = mid + 1;
		}
		else if (a[mid] > x){
			high = mid - 1;
		}
		else {
			return mid;
		}
	}
	return -1;
}

// also recursive option


int main() {
	//std::vector<int> arr = std::vector<int>(10);
	//arr[0] = 5;
	//arr[1] = 2;
	//arr[2] = 4;
	//arr[3] = 8;
	//arr[4] = 7;
	//arr[5] = 3;
	//arr[6] = 9;
	//arr[7] = 1;
	//arr[8] = 0;
	//arr[9] = 9;

	int arr[] = {5, 2, 4, 8, 7, 3, 9, 1, 0, 9};
	auto arr_size = sizeof(arr) / sizeof(arr[0]);
	mergeSort(arr, 0, arr_size - 1);

	//mergeSort(arr, 0, 9);
	for (int i = 0; i < 10; i++) printf("%d\n", arr[i]);
	printf("\n");

	int arr2[] = { 5, 2, 4, 8, 7, 3, 9, 1, 0, 9 };
	mergeSort(arr2, 0, arr_size - 1);
	for (int i = 0; i < 10; i++) printf("%d\n", arr2[i]);

	int ind_3 = binarySearch(arr2, 3, 0, arr_size - 1);
	printf("\n");
	printf("%d\n", ind_3);


}