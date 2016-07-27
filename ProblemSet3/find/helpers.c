/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool linear_search(int value, int values[], int n)
{
    // Return false straight away if n not positive
    if (n <= 0) {
        return false;
    }
    
    // Search for needle
    for (int i = 0; i < n; i++) {
        if (values[i] == value) {
            return true;
        }
    }
    return false;
}

/**
 * Performs binary search on a sorted list.
 */
bool binary_search(int value, int values[], int lower, int upper) 
{
    if (lower > upper) {
        return false;
    }
    
    int middle = lower + ((upper - lower) / 2);
    if (values[middle] == value) {
        return true;
    }
    else if (values[middle] > value) {
        return binary_search(value, values, lower, middle-1);
    }
    else {
        return binary_search(value, values, middle+1, upper);
    }
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    return binary_search(value, values, 0, n-1);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // implements bubble sort an O(n^2) sorting algorithm
    int temp;
    
    // if array has less than 2 elements, do nothing
    if (n < 2) {
        return;
    }
    
    bool finished = false; // set finished flag initially to false
    while (!finished) {
        finished = true; // assume there is nothing to swap
        for (int i = 0; i < n-1; i++) {
            if (values[i] > values[i+1]) { // If a value is larger than the next value in the array
                finished = false; // we will need at least one more pass
                // swap those values
                temp = values[i];
                values[i] = values[i+1];
                values[i+1] = temp;
            }
        }
    }
}