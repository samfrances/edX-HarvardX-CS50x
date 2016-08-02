/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE;

bool check_block_sig(BYTE* block);

int main(int argc, char* argv[])
{
    int BLOCKSIZE = 512;
    
    // Initialise variables to keep track of output file names.
    int file_number = 0;
    char file_name[8];
    sprintf(file_name, "%03i.jpg", file_number);
    
    // open raw file for reading
    FILE* infile = fopen("card.raw", "r");
    if (infile == NULL)
    {
        printf("Could not open card.raw\n");
        return 2;
    }
    
    // open file for writing
    FILE* outfile = fopen(file_name, "w");
    if (outfile == NULL)
    {
        fclose(infile);
        fprintf(stderr, "Could not create %s.\n", file_name);
        return 3;
    }
    
    // Allocate array to store each block
    BYTE* current_block = malloc(sizeof(BYTE) * BLOCKSIZE);
    
    
    
    bool first_file_started = false;
    while (fread(current_block, BLOCKSIZE, 1, infile) == 1)
    {

        // Check if block read in starts with a jpg signature
        if (check_block_sig(current_block))
        {
            // On all loops after the first, close the last file and open a new one
            if (first_file_started) {
                fclose(outfile);
                file_number++;
                sprintf(file_name, "%03i.jpg", file_number);
                outfile = fopen(file_name, "w");
                if (outfile == NULL)
                {
                    fclose(infile);
                    fprintf(stderr, "Could not create %s.\n", file_name);
                    return 3;
                }
            }
            else
            {
                first_file_started = true;
            }
            
        }
        if (first_file_started)
        {
            fwrite(current_block, sizeof(BYTE) * BLOCKSIZE, 1, outfile);   
        }
        
    }
    
    // Free current_block
    free(current_block);
    
    // Close input and output files
    fclose(infile);
    fclose(outfile);
    
}

bool check_block_sig(BYTE* block)
{
    return block[0] == 0xff &&
           block[1] == 0xd8 &&
           block[2] == 0xff &&
           (block[3] & 0xf0) == 0xe0; // Bitmask to test whether first four bits of byte are 1110
}
