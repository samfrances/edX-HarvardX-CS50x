#include <stdio.h>
#include <cs50.h>

/* Prompt user for height of pyramid */
int ask_height(void)
{
    int height;
    
    do 
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    return height;
}

/* Print a pyramind given the height as an integer */
void print_pyramid(int height)
{
    // calculate width of the pyramid in characters
    int width = height + 1;
    
    // Print the pyramid
    /* The first row has 2 bricks, and the number of spaces is the width of the
     * pyramid minus these two bricks. With each iteration of the loop, the
     * number of bricks increases by one, and the number of spaces decreases
     * by one, until the bricks take up the entire width of the pyramid
     */
    for (int pounds = 2, spaces = width - 2; pounds <= width; pounds++, spaces--)
    {
        for (int i = 0; i < spaces; i++)
        {
            printf(" ");
        }
        
        for (int j = 0; j < pounds; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

int main(void)
{
    int height = ask_height();
    print_pyramid(height);
}