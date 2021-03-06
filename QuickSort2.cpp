#include "stdafx.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void quickSort(int arr[], int, int);

int partition(int arr[], int, int);

int main()
{

	int arr[] = { 7, -13, 1, 3, 10, 5, 2, 4 };
	int p = 0;
	int q = sizeof(arr) / sizeof(int);

	cout << "So, the sorted list (using Quicksort) will be " << endl;
	cout << endl << endl;
	quickSort(arr, p, q);

	for (int i = 0; i < q; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}


void quickSort(int arr[], int p, int q)
{
	int r;

	if (p<q)
	{
		r = partition(arr, p, q);
		quickSort(arr, p, r);
		quickSort(arr, r + 1, q);
	}
}



int partition(int arr[], int p, int q)
{
	int x = arr[p];
	int i = p;
	int j;

	for (j = p + 1; j<q; j++)
	{
		if (arr[j] <= x)
		{
			i = i + 1;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}

	}
	int tempa = arr[i];
	arr[i] = arr[p];
	arr[p] = tempa;
	return i;
}
