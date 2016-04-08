#include <stdio.h>
#include <cs50.h>
#include <math.h>

/* Ask user for change owed as floating point, and return change as number of
 * cents (an int), rounded correctly. Re-prompts if non-number or number less 
 * than 0 given.
 */
int ask_change(void)
{
    float change;
    
    printf("O hai! ");
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    while (change < 0);
    
    int cents = (int) round(change * 100);
    
    return cents;
}

/* Take number of cents required as change, and return an integer giving the
 * minimum number of coins that can be given in change. Assumes that the only 
 * coins available are quarters (25¢), dimes (10¢), nickels (5¢),
 * and pennies (1¢).
 */
int min_coins(int cents)
{
    const int quarter = 25;
    const int dime = 10;
    const int nickel = 5;
    const int penny = 1;
    
    int coins = 0;
    
    while (cents > 0)
    {
        /* Determine the largest type of coin you can give, and deduct this from
           amount of change remaining to return */
        if (cents >= quarter)
        {
            cents -= quarter;
        }
        else if (cents >= dime)
        {
            cents -= dime;
        }
        else if (cents >= nickel)
        {
            cents -= nickel;
        }
        else if (cents >= penny)
        {
            cents -= penny;
        }
        
        // increment the coin counter
        coins++;
    }
    
    return coins;
}

int main(void)
{
    int coins = min_coins(ask_change());
    printf("%i\n", coins);
}