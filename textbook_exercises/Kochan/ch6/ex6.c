#include <stdio.h>

int main (void)
{
	
	int Fibonacci_m2, Fibonacci_m1, Fibonacci, i;

	Fibonacci_m2 = 0; // n - 2
	Fibonacci_m1 = 1; // n - 1

    printf("%i %i ", Fibonacci_m2, Fibonacci_m1);

	for ( i = 2; i < 15; ++i )
    {
        Fibonacci = Fibonacci_m2 + Fibonacci_m1;

        printf("%i ", Fibonacci);

		Fibonacci_m2 = Fibonacci_m1;
        Fibonacci_m1 = Fibonacci;
    }

    printf("\n");

	return 0;
}