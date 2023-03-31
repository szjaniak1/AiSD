#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int numberOfComparisons = 0;
static int numberOfShifts = 0;

bool isOk(int j, int *tab, int key)
{
	numberOfComparisons++;
	if (tab[j] > key)
	{
		return true;
	}
	return false;
}

bool shift(int j, int i, int *tab, int key)
{
	if (j + 1 == i)
	{
		return false;
	}
	tab[j + 1] = key;
	numberOfShifts++;
	return true;
}

void insertionSort(int *tab, int size)
{
	int i, j, key;

	for (i = 1; i < size; i++)
	{
		key = tab[i];
		j = i - 1;
		

		while (j >= 0 && isOk(j, tab, key))
		{
			tab[j + 1] = tab[j];
			j--;
			numberOfShifts++;
		}
		shift(j, i, tab, key);
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
	int size;
       	scanf("%d", &size);	
	int *arr = takeInput(size);

	insertionSort(arr, size);
	
	printf("%d %d\n", numberOfComparisons, numberOfShifts);
	
	return 0;
}
