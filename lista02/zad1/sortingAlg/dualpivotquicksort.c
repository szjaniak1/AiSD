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
	if (num1 < num2)
	{
		return true;
	}
	return false;
}

bool isOk2(int num1, int num2)
{	
	numberOfComparisons++;
	if (num1 >= num2)
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

int partition(int *tab, int low, int high, int *lp)
{
	numberOfComparisons++;
	if (tab[low] > tab[high])
	{
		swap(&tab[low], &tab[high]);
		numberOfShifts++;
	}

	int j = low + 1;
	int g = high - 1, k = low + 1, p = tab[low], q = tab[high];

	while (k <= g) 
	{
		if (isOk(tab[k], p))
		{
			swap(&tab[k], &tab[j]);
			numberOfShifts++;
			j++;
		}
		else if (isOk2(tab[k], q))
		{
			while (isOk(q, tab[g]) && k < g)
			{
				g--;
			}
			
			swap(&tab[k], &tab[g]);
			numberOfShifts++;
			g--;

			if (isOk(tab[k], p))
			{
				swap(&tab[k], &tab[j]);
				numberOfShifts++;
				j++;
			}
		}
		k++;
	}
	j--;
	g++;

	swap(&tab[low], &tab[j]);
	swap(&tab[high], &tab[g]);
	numberOfShifts += 2;

	*lp = j;

	return g;	
}

void dualPivotQuickSort(int *tab, int low, int high)
{
	if (low < high)
	{
		int lp, rp;
	       	rp = partition(tab, low, high, &lp);

		dualPivotQuickSort(tab, low, lp - 1);
		dualPivotQuickSort(tab, lp + 1, rp - 1);
		dualPivotQuickSort(tab, rp + 1, high);

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

	dualPivotQuickSort(arr, 0, size - 1);

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
