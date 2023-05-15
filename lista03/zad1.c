#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

static uint64_t number_of_comparisons = 0;
static uint64_t number_of_swaps = 0;
static size_t size = 0;

void printArray(const uint64_t arr[restrict]);
uint64_t* takeInput(void);
size_t select_pivot(uint64_t arr[], const size_t left, const size_t right, const size_t part_size);
size_t select_partition(uint64_t arr[], const size_t left, const size_t right, const size_t pivot_index, const size_t n);
size_t partition5(uint64_t arr[], const size_t p, const size_t r);
size_t rand_partition(uint64_t arr[], const size_t p, const size_t r);
uint64_t randomized_select(uint64_t arr[], const size_t p, const size_t r, const size_t i);
uint64_t qselect(uint64_t arr[], const size_t left, const size_t right, const size_t n, const size_t part_size);
void swap(uint64_t arr[], const size_t p, const size_t r);
int cmp(const void *a, const void *b);

int cmp(const void *a, const void *b)
{
	return *(int*)(a) > *(int*)(b);
}

void swap(uint64_t arr[], const size_t p, const size_t r)
{
	const uint64_t temp = arr[p];
	arr[p] = arr[r];
	arr[r] = temp;
	number_of_swaps++;
}

size_t rand_partition(uint64_t arr[], const size_t p, const size_t r)
{
	size_t i = p + (size_t)rand() % (r - p + 1);
	swap(arr, r, i);
	uint64_t x = arr[r];
	i = p - 1;

	for (size_t j = p; j < r; j++)
	{
		if (arr[j] <= x)
		{
			number_of_comparisons++;
			i++;
			swap(arr, i, j);
		}
	}

	swap(arr, i + 1, r);
	return i + 1;
}

size_t select_partition(uint64_t arr[], const size_t left, const size_t right, const size_t pivot_index, const size_t n)
{
	uint64_t pivot_value = arr[pivot_index];
	swap(arr, pivot_index, right);
	size_t store_index = left;

	for (size_t i = left; i < right; i++)
	{
		if (arr[i] < pivot_value)
		{
			swap(arr, store_index, i);
			store_index++;
		}
	}

	size_t store_index_eq = store_index;
	for (size_t i = store_index; i < right; i++)
	{
		if (arr[i] == pivot_value)
		{
			swap(arr, store_index_eq, i);
			store_index_eq++;
		}
	}

	swap(arr, right, store_index_eq);

	if (n < store_index) return store_index;
	if (n <= store_index_eq) return n;
	return store_index_eq;
}

size_t partition5(uint64_t arr[], const size_t left, const size_t right)
{
	size_t j;
	size_t i = left + 1;

	while (i <= right)
	{
		j = i;
		while (j > left && arr[j - 1] > arr[j])
		{
			number_of_comparisons++;
			swap(arr, j - 1, j);
			j--;
		}
		i++;
	}

	return (left + right) / 2;
}

uint64_t randomized_select(uint64_t arr[], const size_t p, const size_t r, const size_t i)
{
	if (p == r) return arr[p];

	size_t index = rand_partition(arr, p, r);
	size_t k = index - p + 1;

	if (size <= 50) printf("left range: %zu, right range: %zu, partition: %zu, found number: %02ld\n", p, r, i, arr[index]);

	if (i == k) return arr[index];
	if (i < k) return randomized_select(arr, p, index - 1, i);
	return randomized_select(arr, index + 1, r, i - k);
}

size_t select_pivot(uint64_t arr[], const size_t left, const size_t right, const size_t part_size)
{
	if (right - left < part_size) return partition5(arr, left, right);

	for (size_t i = left; i < right; i += part_size)
	{
		size_t sub_right = i + part_size - 1;
		if (sub_right > right) sub_right = right;

		size_t median5 = partition5(arr, i, sub_right);
		swap(arr, median5, left + ((i - left) / part_size));
	}

	size_t mid = ((right - left) / (part_size*2)) + left + 1;
	return qselect(arr, left, left + ((right - left) / part_size), mid, part_size);
}

uint64_t qselect(uint64_t arr[], const size_t left, const size_t right, const size_t n, const size_t part_size)
{
	if (left == right) return left;

	size_t pivot_index = select_pivot(arr, left, right, part_size);
	pivot_index = select_partition(arr, left, right, pivot_index, n);

	if (n == pivot_index) return n;
	if (n < pivot_index) return qselect(arr, left, pivot_index - 1, n, part_size);
	return qselect(arr, pivot_index + 1, right, n, part_size);	
}

void printArray(const uint64_t arr[restrict])
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%02ld ", arr[i]);
	}
	printf("%c", '\n');
}

uint64_t* takeInput(void)
{
	uint64_t *arr = malloc(size * sizeof(uint64_t));

	for (size_t i = 0; i < size; i++)
	{
		scanf("%" SCNu64, &arr[i]);
	}
	return arr;
}

int main(int argc, char* argv[])
{
	scanf("%zu", &size);
	uint64_t *arr;
	time_t t;
	uint32_t stat = atoi(argv[2]);

	srand((unsigned) time(&t));
	arr = takeInput();
	
	const uint8_t operation = atoi(argv[1]);
	// 1 - rand select
	// 2 - select (part5)
	// 3 - select with custom part size	
	uint64_t index;
	switch (operation)
	{
		case 1:
			index = randomized_select(arr, 0, size - 1, stat);
			break;
		case 2:
			const size_t size = atoi(argv[3]);
			index = qselect(arr, 0, size - 1, stat, size);
			break;
	}

	printf("%ld;%ld", number_of_comparisons, number_of_swaps);
	return 0;
}
