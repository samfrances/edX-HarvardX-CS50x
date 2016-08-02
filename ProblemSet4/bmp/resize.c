/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // remember filenames and resize factor
    char* infile = argv[2];
    char* outfile = argv[3];
    int resize_factor = atoi(argv[1]);
    
    // Check resize factor is positive int less than 100
    if (resize_factor < 1 || resize_factor > 100)
    {
        printf("Resize factor must be a positive integer less than or equal to 100.\n");
        return 1;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // Calculate padding in input file
    int input_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    
    // Make a copy of input file's headers, for use in output file
    BITMAPFILEHEADER bf2 = bf;
    BITMAPINFOHEADER bi2 = bi;
    
    // Calculate bfSize, biWidth, biHeight, biSizeImage
    
    // Calcuate biWidth and biHeight
    bi2.biWidth = bi.biWidth * resize_factor;
    bi2.biHeight = bi.biHeight * resize_factor;
    
    // determine padding for lines in output file
    int output_padding =  (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // Remeber length of line in ouput in bytes with padding
    int linelengthbytes = bi2.biWidth * sizeof(RGBTRIPLE) + output_padding;
    
    // biSizeImage
    bi2.biSizeImage = linelengthbytes * abs(bi2.biHeight);
    
    // Calculate bfSize as header size of headers plus size of image including padding
    bf2.bfSize = sizeof(bf2) + sizeof(bi2) + bi2.biSizeImage;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);


    // Reserve heap space for array to store resized scanline (not including padding)
    RGBTRIPLE* resized_line = malloc(bi2.biWidth * sizeof(RGBTRIPLE));

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline and store resized version in resized_line
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // Copy pixels to array and expand by factor CHECK
            for (int k = j * resize_factor; k < ((j * resize_factor) + resize_factor); k++)
            {
                resized_line[k] = triple;
            }
            
        }
        
        // skip over padding, if any
        fseek(inptr, input_padding, SEEK_CUR);
        
        // write expanded line to output x times where x = resize_factor
        for (int j = 0; j < resize_factor; j++)
        {
            fwrite(resized_line, sizeof(RGBTRIPLE), bi2.biWidth, outptr); //CHECK
           
            // Add padding
            for (int k = 0; k < output_padding; k++)
            {
                fputc(0x00, outptr);
            }
        }

    }
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // free resized_line
    free(resized_line);

    // that's all folks
    return 0;
}
