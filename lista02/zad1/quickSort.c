#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
		if (*(tab + j) <= pivot)
		{
			i++;
			swap(tab + i, tab + j);
		}
	}

	swap(tab + i + 1, tab + high);
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

void printArray(int *tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%02d ", *(tab + i));
	}
	printf("%c", '\n');
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
	int size;
       	scanf("%d", &size);	
	int *arr = takeInput(size);;
	printArray(arr, size);
	quickSort(arr, 0, size - 1);
	printArray(arr, size);

	return 0;
}
