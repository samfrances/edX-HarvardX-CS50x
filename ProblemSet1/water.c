#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask user for showering time in minutes
    printf("minutes: ");
    int minutes = GetInt();
    
    // Tell the user how many bottles of water their shower consumes
    int bottles = minutes * 12;
    printf("bottles: %i\n", bottles);
}