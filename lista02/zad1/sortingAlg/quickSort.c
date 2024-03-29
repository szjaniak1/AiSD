#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int numberOfComparisons = 0;
static int numberOfShifts = 0;
static int size = 0;

void printArray(int *tab, int size);

bool isOk(int num1, int num2)
{	
	numberOfComparisons++;
	if (num1 <= num2)
	{
		return true;
	}
	return false;
}

void swap(int *n1, int *n2)
{
	int t = *n1;
	*n1 = *n2;
	*n2 = t;
}

int partition(int *tab, int low, int high)
{
	int pivot = *(tab + high);
	int i = (low - 1);

	for (int j = low; j < high; j++)
	{
		if (isOk(*(tab + j), pivot))
		{
			i++;
			swap(tab + i, tab + j);
			numberOfShifts++;
		}
	}

	swap(tab + i + 1, tab + high);
	numberOfShifts++;
	return (i + 1);
}

void quickSort(int *tab, int low, int high)
{
	if (low < high)
	{
		int pi = partition(tab, low, high);

		quickSort(tab, low, pi - 1);
		quickSort(tab, pi + 1, high);
		
		if (size < 40)
		{
			printArray(tab, size);
		}
	}
}

void printArray(int *tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%02d ", *(tab + i));
	}
	printf("%c", '\n');
}

bool isSorted(int *tab, int size)
{
	for (int i = 1; i < size; i++)
	{
		if (*(tab + i - 1) > *(tab + i))
		{
			return false;
		}
	}
	return true;
}

int* takeInput(int argc)
{	
	int arg;
	int *tab = malloc((argc) * sizeof(int));
	for (int i = 0; i < argc; i++)
	{	
		scanf("%d", &arg);
		*(tab + i) = arg;
	}
	return tab;
}

int main()
{
       	scanf("%d", &size);	
	int *arr = takeInput(size);;

	if (size < 40)
	{
		printArray(arr, size);
	}

	quickSort(arr, 0, size - 1);

	printf("\ntotal number of comparisons: %d, total number of shifts: %d\n", numberOfComparisons, numberOfShifts);

	if (isSorted(arr, size))
	{
		printf("array is sorted!");
	}
	else
	{
		printf("array is NOT sorted!");
	}

	return 0;
}
