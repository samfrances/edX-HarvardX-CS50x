/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
bool adjacent(int row1, int col1, int row2, int col2);
void swap_tiles(int row1, int col1, int row2, int col2);
bool find_tile(int cell_value, int result[], int d);


int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // Calculate nuber of tiles
    int ntiles = (d * d) - 1;
    
    // Set empty tile, represented by 0
    board[d-1][d-1] = 0;
    
    // If number of tiles is even, reverse 1 and 2
    if (ntiles % 2 != 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
    else
    {
        board[d-1][d-2] = 1;
        board[d-1][d-3] = 2;
    }
    
    // Fill in the rest of the board
    int col = 0;
    int row = 0;
    for (int i = (d*d)-1; i > 2; i--)
    {
        board[row][col] = i;
        col++;
        if (col == d)
        {
            row++;
            col = 0;
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    int number;
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            number = board[row][col];
            if (number == 0)
            {
                printf("%2c ", '_');
            }
            else
            {
                printf("%2i ", board[row][col]);
            }
            if (col == d-1)
            {
                printf("\n\n");
            }
        }
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // find tile, or return false if not found
    int tile_position[2];
    if (!find_tile(tile, tile_position, d))
    {
        printf("tile not found\n");
        return false;
    }
    
    // find blank tile, or return false if not found
    int blank_position[2];
    if (!find_tile(0, blank_position, d))
    {
        return false;
    }
    
    // calculate if tile is next to the blank
    if (adjacent(tile_position[0], tile_position[1], blank_position[0], blank_position[1]))
    {
        //swap the tiles
        swap_tiles(tile_position[0], tile_position[1], blank_position[0], blank_position[1]);
        return true;
    }

    // if not, return false
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // If the first tile isn't 1, or the last tile isn't blank, the game isn't won yet
	if (board[0][0] != 1)
	{
		return false;
	}
	if (board[d-1][d-1] != 0) {
		return false;
	}

	int prev_row = 0;
	int prev_col = 0;
	for (int row = 0; row < d; row++)
	{
		for (int col = 0; col < d; col++)
		{
			// Ignore the first row
			if (row == 0 && col == 0) {
				continue;
			}

			// Ignore the last row
			if (row == d-1 && col == d-1)
			{
				continue;
			}

			// The value of a cell should be 1 more than its successor
			if (board[row][col] - board[prev_row][prev_col] != 1)
			{
				return false;
			}
			prev_row = row;
			prev_col = col;
		}
	}
	return true;
}


// Helper functions

/**
 * Finds tile and modifies given array to give {row, col}
 */
bool find_tile(int tile_value, int result[], int d)
{
	// If tile_value is outside of the range of possible values, return false
	if (tile_value < 0 || tile_value > d*d-1)
	{
		return false;
	}

	// Otherwise, search for the correct number
	for (int row = 0; row < d; row++) 
	{
		for (int col = 0; col < d; col++)
		{
			if (board[row][col] == tile_value)
			{
				// Modify supplied array with {row, col}, and return true
				result[0] = row;
				result[1] = col;
				return true;
			}
		}
	}
	return false;
}

/**
 * Determines if two tiles are adjacent
 */
bool adjacent(int row1, int col1, int row2, int col2)
{
	if ((row1 == row2) && (abs(col1 - col2) == 1)) 
	{
		return true;
	}
	if ((col1 == col2) && (abs(row1 - row2) == 1)) 
	{
		return true;
	}
	return false;
}

/**
 * Swaps the values of two tiles
 */
void swap_tiles(int row1, int col1, int row2, int col2)
{
	int temp = board[row1][col1];
	board[row1][col1] = board[row2][col2];
	board[row2][col2] = temp;
}