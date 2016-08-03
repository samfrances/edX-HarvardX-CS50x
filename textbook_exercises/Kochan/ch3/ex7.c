// (3.31 x 10^-8 x 2.01 x 10^-7 ) / (7.16 x 10^-6 + 2.01 x 10^-8 )

#include <stdio.h>
#include <math.h>

int main(void)
{
    float answer = (3.31 * pow(10, -8) * 2.01 * pow(10, -7) ) / (7.16 * pow(10, -6) + 2.01 * pow(10, -8));
    printf("%e", answer);
}