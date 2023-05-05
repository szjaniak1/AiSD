#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>

static uint64_t number_of_comparisons = 0;
static uint64_t number_of_shifts = 0;
static size_t size = 0;

void printArray(const uint64_t arr[restrict]);
uint64_t* takeInput(void);
size_t partition(uint64_t arr[], const size_t p, const size_t r);
uint64_t randomized_select(uint64_t arr[], const size_t p, const size_t r, const size_t i);
void swap(uint64_t arr[], const size_t p, const size_t r);
int cmp(const void *a, const void *b);

int cmp(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

void swap(uint64_t arr[], const size_t p, const size_t r)
{
	const uint64_t temp = arr[p];
	arr[p] = arr[r];
	arr[r] = temp;
}

size_t partition(uint64_t arr[], const size_t p, const size_t r)
{
	size_t i = p + (size_t)rand() % (r - p + 1);
	swap(arr, r, i);
	uint64_t x = arr[r];
	i = p - 1;

	for (size_t j = p; j < r; j++)
	{
		if (arr[j] <= x)
		{
			i++;
			swap(arr, i, j);
		}
	}

	swap(arr, i + 1, r);
	return i + 1;
}

uint64_t randomized_select(uint64_t arr[], size_t p, size_t r, size_t i)
{
	if (p == r) return arr[p];

	size_t q = partition(arr, p, r);
	size_t k = q - p + 1;

	if (i == k) return arr[q];
	else if (i < k) return randomized_select(arr, p, q - 1, i);
	else return randomized_select(arr, q + 1, r, i - k);
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
	uint64_t *arr = malloc((size) * sizeof(uint64_t));

	for (size_t i = 0; i < size; i++)
	{
		scanf("%" SCNu64, &arr[i]);
	}
	return arr;
}

int main(void)
{
	scanf("%zu", &size);
	uint64_t *arr;
	time_t t;

	srand((unsigned) time(&t));
	arr = takeInput();

	printArray(arr);
	const uint64_t select = randomized_select(arr, 0, size - 1, 3);
	qsort(arr, size, sizeof(uint64_t), cmp);

	printf("select: %ld, total number of comparisons: %ld, total number of shifts: %ld\n", select, number_of_comparisons, number_of_shifts);

	printArray(arr);
	return 0;
}
