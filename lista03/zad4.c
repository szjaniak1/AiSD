#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <time.h>

#include "time.c"

static uint32_t number_of_comparisons = 0;
static size_t size = 0;

void print_array(const uint32_t arr[restrict]);
uint32_t* take_input(void);
int cmp(const void *a, const void *b);
void find(const uint32_t arr[restrict], const uint32_t number_index);
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

void find(const uint32_t arr[restrict], const uint32_t number)
{	
	int time = get_time();
	uint8_t result = binary_search(arr, 0, size - 1, number);
	time = get_time() - time;
	if (result) printf("%d;%d", number_of_comparisons, time);
	else printf("%d;%d", number_of_comparisons, time);	
}

int cmp(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

int main(int argc, char* argv[])
{
	time_t t;
	srand((unsigned) time(&t));

	scanf("%zu", &size);
	uint32_t *arr = take_input();
	const size_t index = atoi(argv[1]);

	find(arr, arr[index]);
	return 0;
}
