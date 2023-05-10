#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>

static uint32_t number_of_comparisons = 0;
static size_t size = 0;

void print_array(const uint32_t arr[restrict]);
uint32_t* take_input(void);
int cmp(const void *a, const void *b);
void find(const uint32_t arr[restrict], const uint32_t number_index);
uint8_t binary_search(const uint32_t arr[restrict], size_t l, size_t r, uint32_t x); 
double get_time(void);

double get_time(void)
{
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	return now.tv_sec + now.tv_nsec*1e-9;
}

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

void find(const uint32_t arr[restrict], const uint32_t number)
{	
	double time = get_time();
	uint8_t result = binary_search(arr, 0, size - 1, number);
	time = get_time() - time;
	if (result) printf("number %d is found in %d comparisons, in %lf seconds\n", number, number_of_comparisons, time);
	else printf("number %d is not found in %d comparisons and in %lf seconds\n", number, number_of_comparisons, time);	
}

int cmp(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

int main(void)
{
	time_t t;
	srand((unsigned) time(&t));

	scanf("%zu", &size);
	uint32_t *arr = take_input();
	const size_t begin_number_index = size / 20;
	const size_t end_number_index = size - begin_number_index;
	const size_t mid_number_index = size / 2;
	const size_t random_number_index = (size_t)rand() % size;
	const uint32_t out_number = (uint32_t)(2 * size + 2);
	
	qsort(arr, size, sizeof(uint32_t), cmp);
	if (size <= 50) print_array(arr);
	find(arr, arr[begin_number_index]);
	find(arr, arr[end_number_index]);
       	find(arr, arr[mid_number_index]);
	find(arr, arr[random_number_index]);
	find(arr, out_number);

	return 0;
}
