#include <stdio.h>

int main (void)
{
	
	int numbers[10];
	int i, response, total;

	printf ("Enter ten numbers\n");

	for ( i = 0, total = 0; i < 10; ++i )
	{
		scanf("%i", &response);

		numbers[i] = response;
	}

	for ( i = 0, total = 0; i < 10; i++ )
		total += numbers[i];

	printf ("\nAverage: %f\n", total / 10.0);

	return 0;
}