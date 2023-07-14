#include <iostream>
void heapifyDown(int arr[], int size, int parent);
int* extractMax(int arr[], int size);

int main() {
    int arr[3] = { 9, 8, 7 };
	extractMax(arr, 3);
	for (int i : arr)
	{
		std::cout << arr[i] << " ";
	}
    return 0;
}

int* extractMax(int arr[], int size)
{
	int newArr[size - 1];
	arr[0] = arr[size - 1];
	for (int i = 0; i < size - 1; i++)
	{
		newArr[i] = arr[i];
	}
	heapifyDown(newArr, size - 1, 0);
	//delete[] arr;
	arr = newArr;
	return arr;
}
//heapifyDown inspired by sudo-code from exam review discussion
void heapifyDown(int arr[], int size, int parent)
{
	int left = (2 * parent) + 1;
	int right = (2 * parent) + 2;
	int maxIndex = parent;

	if (right < size && arr[right] > arr[maxIndex])
	{
		maxIndex = right;
	}
	if (left < size && arr[left] > arr[maxIndex])
	{
		maxIndex = left;
	}
	if (maxIndex != parent)
	{
		int temp = arr[maxIndex];
		arr[maxIndex] = arr[parent];
		arr[parent] = temp;
		heapifyDown(arr, size, maxIndex);
	}
}