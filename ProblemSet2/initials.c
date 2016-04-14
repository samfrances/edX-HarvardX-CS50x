#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(void)
{
    // Ask user for their name
    string name = GetString();

    // Output the first character as a capital, if it is a letter
    if (name[0] != ' ')
    {
        printf("%c", toupper(name[0]));
    }
    
    /* Loop through the rest of the characters, printing a capitalised character
     * if it is a letter preceded by a space. */
    for (int i = 1, len_name = strlen(name); i < len_name; i++)
    {
        if (name[i - 1] == ' ' && isalpha(name[i]))
        {
            printf("%c", toupper(name[i]));
        }
    }
    
    // Print the final newline
    printf("\n");
}