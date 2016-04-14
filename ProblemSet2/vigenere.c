#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int keychar2int(char keychar);
char caesar_char(char letter, int key);
bool isalpha_str(string s);

int main(int argc, string argv[])
{
    // Check that one and only one keyword is supplied, and that it is valid
    if (argc != 2)
    {
        printf("Usage: %s <string keyword>\n", argv[0]);
        return 1;
    }
    if (!isalpha_str(argv[1]))
    {
        printf("Keyword must contain only alphabetical characters.\n");
        return 1;
    }
    
    string keyword = argv[1];
    string cleartext = GetString();
    
    for (int i = 0, n = strlen(cleartext), keyword_index = 0; i < n; i++) {
        
        // The character to be encryped:
        char clear_char = cleartext[i];
        
        // The integer to use as a key to encrypt this character
        char key = keychar2int(keyword[keyword_index]);
        
        // Generate the encrypted character, and print it.
        char cipherchar = caesar_char(clear_char, key);
        printf("%c", cipherchar);
        
        /* If the encryped character was alphabetical, prepare to apply the next
         * character of the keyword, otherwise wait */
        if (isalpha(clear_char))
        {
            keyword_index = (keyword_index + 1) % strlen(keyword);
        }
    }
    printf("\n");
}

/* Convert individual characters of the key into numerical equivalents
 * e.g. 'z' = 25, 'b' = 1 etc. */
int keychar2int(char keychar)
{
    return (int) (tolower(keychar) - 97);
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

bool isalpha_str(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}