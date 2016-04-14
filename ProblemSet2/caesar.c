#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char caesar_char(char letter, int key);

bool is_int(string s);

int main(int argc, string argv[])
{
    // Check that command line arguments are valid
    if (argc != 2 || !is_int(argv[1])) 
    {
        printf("Usage: %s <int key>\n", argv[0]);
        return 1;
    }
    
    // Convert key argument to an integer
    int key = atoi(argv[1]);
    
    // Get a string from user input
    string cleartext = GetString();
    
    // Print out ciphertext
    for (int i = 0, n = strlen(cleartext); i < n; i++)
    {
        printf("%c", caesar_char(cleartext[i], key));
    }
    printf("\n");
}

// Convert individual characters of cleartext into ciphertexts
char caesar_char(char letter, int key)
{
    if (isalpha(letter)) 
    {
        // lowercase letters start at 97, uppercase at 65
        int start = 97;
        if (isupper(letter))
        {
            start = 65;
        }
        
        /* Calculate and refurn ciphercharacter, taking into account starting
         * point of ascii alphabetic character ranges, but subtracting to 
         * apply the caesar cipher formula and then adding back at the end */
        return (char) ((((letter - start) + key) % 26) + start);
    }
    else
    {
        // return non-alphabetic characters unchanged
        return letter;
    }
}

// Check if a string represents an integer
bool is_int(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}