#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void print_array(const uint32_t arr[restrict], const size_t size);
uint32_t* take_input(const size_t size);
void swap(uint32_t arr, const size_t index1, const size_t index2);

void swap(uint32_t arr, const size_t index1, const size_t index2)
{
	uint32_t temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}

size_t partition(const uint32_t arr[restrict], const size_t low, const size_t high)
{
	size_t pivot = select_pivot(arr, low, high, 5);
	pivot = arr[pivot];

	size_t left_index = low - 1;
	size_t right_index = high + 1;

	while(true)
	{
		while(true)
		{
			left_index++;
			if (arr[left_index] >= pivot) break;
		}

		while(true)
		{
			right_index++;
			if(arr[right_index] <= pivot) break;
		}

		if (left_index >= right_index) return right_index;
		swap(arr, left_index, right_index);
	}
}

void quicksort_select(const uin32_t arr[restrict], const size_t low, const size_t high)
{
	size_t p;
	if (low < high)
	{
		p = partition(arr, low, high);
		quicksort_select(arr, low, p);
		quicksort_select(arr, p + 1, high);
	}
}

void print_array(const uint32_t arr[restrict], const size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%d ", arr[size]);
	}
}

uint32_t* take_input(const size_t size)
{
	uint32_t *arr = malloc(size * sizeof(uint32_t));
	for (size_t i = 0; i < size; i++)
	{
		scanf("%d", &arr[i]);
	}
	return arr;
}

int main(void)
{	
	uint32_t size;
	scanf("%d", &size);
	uint32_t *arr = take_input();
}
