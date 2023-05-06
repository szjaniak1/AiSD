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
size_t pivot(uint64_t arr[], const size_t p, const size_t r);
size_t partition(uint64_t arr[], const size_t p, const size_t r, const size_t index, const size_t n);
size_t partition5(uint64_t arr[], const size_t p, const size_t r);
size_t rand_partition(uint64_t arr[], const size_t p, const size_t r);
uint64_t randomized_select(uint64_t arr[], const size_t p, const size_t r, const size_t i);
uint64_t quick_select(uint64_t arr[], const size_t p, const size_t r, const size_t i);
void swap(uint64_t arr[], const size_t p, const size_t r);
int cmp(const void *a, const void *b);
void reload_counters(void);

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

size_t partition(uint64_t arr[], const size_t p, const size_t r, const size_t index, const size_t n)
{
	uint64_t pivot_value = arr[index];
	swap(arr, index, r);
	size_t store_index = p;

	for (size_t i = p; i <= r - 1; i++)
	{
		if (arr[i] < pivot_value)
		{
			swap(arr, store_index, i);
			store_index++;
		}
	}

	size_t store_index_eq = store_index;
	for (size_t i = store_index; i <= r - 1; i++)
	{
		if (arr[i] == pivot_value)
		{
			swap(arr, store_index_eq, i);
			store_index_eq++;
		}
	}

	swap(arr, r, store_index_eq);

	if (n < store_index) return store_index;
	if (n <= store_index_eq) return n;
	return store_index_eq;
}

size_t partition5(uint64_t arr[], const size_t p, const size_t r)
{
	size_t j;
	size_t i = p + 1;

	while (i <= r)
	{
		j = i;
		while (j > p && arr[j - 1] > arr[j])
		{
			swap(arr, j - 1, j);
			j--;
		}
		i++;
	}

	return (p + r) / 2;
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

size_t pivot(uint64_t arr[], const size_t p, const size_t r)
{
	if (r - p < 5) return partition5(arr, p, r);

	for (size_t i = p; i <= r; i += 5)
	{
		size_t sub_r = i + 4;
		if (sub_r > r) sub_r = r;

		size_t median5 = partition5(arr, i, sub_r);
		swap(arr, median5, p + ((i - p) / 5));
	}

	size_t mid = ((r - p) / 10) + p + 1;
	return quick_select(arr, p, p + ((r - p) / 5), mid);
}

uint64_t quick_select(uint64_t arr[], const size_t p, const size_t r, const size_t i)
{
	if (p == r) return arr[p];

	size_t index = pivot(arr, p, r);
	index = partition(arr, p, r, index, i);

	if (size <= 50) printf("left range: %zu, right range: %zu, partition: %zu, found number: %02ld\n", p, r, i, arr[index]);

	if (i == index) return arr[index];
	if (i < index) return quick_select(arr, p, index - 1, i);
	return quick_select(arr, index + 1, r, i);	
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

void reload_counters(void)
{
	number_of_swaps = 0;
	number_of_comparisons = 0;
}

int main(void)
{
	scanf("%zu", &size);
	uint64_t *arr;
	uint64_t *temp_arr = malloc(size * sizeof(uint64_t));
	time_t t;
	uint64_t number_to_find = 5;

	srand((unsigned) time(&t));
	arr = takeInput();
	memcpy(temp_arr, arr, sizeof(uint64_t) * size);

	if (size <= 50) printArray(arr);
	const uint64_t rselect = randomized_select(arr, 0, size - 1, number_to_find);
	
	printf("rselect: %ld, total number of comparisons: %ld, total number of swaps: %ld\n", rselect, number_of_comparisons, number_of_swaps);
	qsort(arr, size, sizeof(uint64_t), cmp);
	reload_counters();

	const uint64_t qselect = quick_select(temp_arr, 0, size - 1, number_to_find);

	printf("qselect: %ld, total number of comparisons: %ld, total number of swaps: %ld\n", qselect, number_of_comparisons, number_of_swaps);

	if (size <= 50) printArray(arr);

	return 0;
}
