#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int numberOfComparisons = 0;
static int numberOfShifts = 0;
static int size = 0;

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
	}
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

	quickSort(arr, 0, size - 1);

	printf("%d %d\n", numberOfComparisons, numberOfShifts);

	return 0;
}
