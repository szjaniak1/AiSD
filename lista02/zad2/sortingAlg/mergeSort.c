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
	if(num1 <= num2)
	{
		return true;
	}
	else
	{
		return false;
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
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		
		mergeSort(tab, left, mid);
		mergeSort(tab, mid + 1, right);
		
		merge(tab, left, mid, right);
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
	int *arr = takeInput(size);
	
	mergeSort(arr, 0, size - 1);

	printf("%d %d\n", numberOfComparisons,numberOfShifts);

	return 0;
}
