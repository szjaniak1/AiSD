#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void insertionSort(int *tab, int size)
{
	int i, j, key;

	for (i = 1; i < size; i++)
	{
		key = tab[i];
		j = i - 1;

		while (j >= 0 && tab[j] > key)
		{
			tab[j + 1] = tab[j];
			j--;
		}
		tab[j + 1] = key;
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

int* takeInput(int argc, char *argv[])
{	
	int *tab = malloc((argc - 2) * sizeof(int));
	for (int i = 2; i < argc; i++)
	{
		*(tab + i - 2) = atoi(argv[i]);
	}
	return tab;
}

int main(int argc, char *argv[])
{
	int *arr = takeInput(argc, argv);;
	int size = atoi(argv[1]);
	
	printArray(arr, size);
	insertionSort(arr, size);
	printArray(arr, size);

	return 0;
}
