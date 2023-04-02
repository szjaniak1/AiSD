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
	if(num1 <= num2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isOk2(int j, int *tab, int key)
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

void insertionSort(int *tab, int start, int end)
{
	int i, j, key;
	for (i = start; i < end; i++)
	{
		key = tab[i];
		j = i - 1;

		while (j >= 0 && isOk2(j, tab, key))
		{
			tab[j + 1] = tab[j];
			j--;
			numberOfShifts++;

			if (size < 40)
			{
				printArray(tab, size);
			}
		}

		if (shift(j, i, tab, key) && size < 40)
		{
			printArray(tab, size);
		}
	}
}

void merge(int *arr, int left, int mid, int right)
{
	int i, j, k;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int L[n1], R[n2];

	for (i = 0; i < n1; i++)
	{
		L[i] = *(arr + left + i);
	}
	for (j = 0; j < n2; j++)
	{
		R[j] = *(arr + mid + 1 + j);
	}

	i = 0; j = 0; k = left;

	while (i < n1 && j < n2)
	{
		if (isOk(L[i], R[j]))
		{
			*(arr + k) = L[i];
			numberOfShifts++;
			i++;
		}
		else
		{
			*(arr + k) = R[j];
			numberOfShifts++;
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		*(arr + k) = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		*(arr + k) = R[j];
		k++;
		j++;
	}
}
				

void mergeSort(int *tab, int left, int right)
{
	if (right - left <= 8)
	{
		insertionSort(tab, left, right);
	}
	else if (left < right)
	{
		int mid = left + (right - left) / 2;
		
		mergeSort(tab, left, mid);
		mergeSort(tab, mid + 1, right);
		
		merge(tab, left, mid, right);
		
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
	for (int i = 0; i < size; i++)
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
	int *arr = takeInput(size);
	
	if (size < 40)
	{
		printArray(arr, size);
	}

	mergeSort(arr, 0, size - 1);

	printf("\ntotal number of comparisons: %d, total number of shifts: %d\n", numberOfComparisons,
			numberOfShifts);

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
