#include <stdio.h>

void sort(int a[], int n);
void print_arr(int a[], int n);

int main(void)
{
	int i;
	int array[16] = {  34, -5, 6, 0, 12, 100, 56, 22,
					   44, -3, -9, 12, 17, 22, 6, 11 };

	printf("The array before the sort:\n");

	print_arr(array, 16);

	sort(array, 16);

	printf("\n\nThe array after the sort:\n");

	print_arr(array, 16);

	printf("\n");

	return 0;

}

void sort(int a[], int n)
{
	int i, j, temp;

	for ( i = 0; i < n; ++i )
		for (j = i + 1; j < n; ++j )
			if ( a[i] > a [j] )
			{
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
}

void print_arr(int a[], int n)
{
	for ( int i = 0; i < n; i ++)
		printf("%i ", a[i]);
}