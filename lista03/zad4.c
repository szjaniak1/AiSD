#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

static uint32_t number_of_comparisons = 0;
static size_t size = 0;

void print_array(const uint32_t arr[restrict]);
uint32_t* take_input(void);
int cmp(const void *a, const void *b);
void find(const uint32_t arr[restrict], const size_t number_index);
uint8_t binary_search(const uint32_t arr[restrict], size_t l, size_t r, uint32_t x); 

uint8_t binary_search(const uint32_t arr[restrict], size_t l, size_t r, uint32_t x)
{
	size_t m;
	number_of_comparisons = 0;
	while (l <= r)
	{
		m = l + (r - l) / 2;

		if (arr[m] == x) return 1;
		if (arr[m] < x) l = m + 1;
		else r = m - 1;
		number_of_comparisons++;
	}

	return 0;
}

void print_array(const uint32_t arr[restrict])
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%02d ", arr[i]);
	}
	printf("%c", '\n');
}

uint32_t* take_input(void)
{
	uint32_t *arr = malloc(size * sizeof(uint32_t));

	for (size_t i = 0; i < size; i++)
	{
		scanf("%d", &arr[i]);
	}
	return arr;
}

void find(const uint32_t arr[restrict], const size_t number_index)
{	
	uint32_t number = arr[number_index];	
	if (binary_search(arr, 0, size - 1, number)) printf("number %d is found in %d comparisons\n", number, number_of_comparisons);
	else printf("number %d is not found\n", number);	
}

int cmp(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

int main(void)
{
	scanf("%zu", &size);
	uint32_t *arr = take_input();
	const size_t begin_number_index = size / 20;
	const size_t end_number_index = size - begin_number_index;
	const size_t mid_number_index = size / 2;
	
	qsort(arr, size, sizeof(uint32_t), cmp);
	if (size <= 50) print_array(arr);
	find(arr, begin_number_index);
	find(arr, end_number_index);
       	find(arr, mid_number_index);	

	return 0;
}
