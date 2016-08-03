// Write a program that converts 27° from degrees Fahrenheit (F) to degrees Celsius (C)
// using the following formula:
// C = ( F - 32) / 1.8

#include <stdio.h>

int main(void)
{
    int f = 27;
    float c = (f - 32) / 1.8;
    printf("%i° Fahrenheit is %f° Celsius.", f, c);
}