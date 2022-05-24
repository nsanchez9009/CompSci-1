//Nicolas Sanchez
//RP2 Counting Stars
//COP 3502

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Functions.
char **gridMaker(int gridX, int gridY);
void floodFill(char **grid, int gridX, int gridY, int x, int y);

//Main.
int main(void)
{
    //Grid and loop.
    int gridX, gridY, i, j;

    //Star flag variable.
    int numStars = 0;

    //2d grid array.
    char **grid;

    //cases variable.
    int cases = 0;

    //When scan, if eof stop scanning. If not, keep scanning.
    while (scanf("%d %d", &gridX, &gridY) != EOF)
    {
        //If input is invalid.
        while (gridX < 1 || gridY > 100)
        {
            printf("Invalid Input\n");
            return 0;
        }

        //Pass to gridMaker to make our 2d array.
        grid = gridMaker(gridX, gridY);

        //Find a star character in the 2d array and then call floodfill to being checking.
        for (i = 0; i < gridX; i++)
        {   
            for (j = 0; j < gridY; j++)
            {
                if (grid[i][j] == '-')
                {
                    //increase the number of stars because a star was found.
                    numStars++;

                    //pass in the 2d array, The grid for borders, and the location of the character.
                    floodFill(grid, gridX, gridY, i, j);
                }
            }
        }

        //increase the case number.
        cases++;

        //print the results.
        printf("Case %d: %d\n", cases, numStars);

        //reset numStars so the next cases arent cumulative.
        numStars = 0;
    }

    //free grid.
    for (i = 0; i < gridX; i++)
    {
        free(grid[i]);
    }
    free(grid);

    return 0;
}

//gridMaker.
char **gridMaker(int gridX, int gridY)
{
    int i;

    //make a 2d array of pointers of size gridX.
    char **grid = malloc(gridX * sizeof(char*));
    
    //loop through each pointer and then malloc another array to hold each string. Eventually making the grid.
    for (i = 0; i < gridX; i++)
    {
        grid[i] = malloc((gridY + 1) * sizeof(char));
        scanf("%s", grid[i]);
    }

    //return the grid.
    return grid;
}

//floodFill.
void floodFill(char **grid, int gridX, int gridY, int x, int y)
{
    //loop variable.
    int i;
    //up down left and right.
    int moves = 4;
    //up and down.
    int DX[] = {-1, 0, 0, 1};
    //left and right.
    int DY[] = {0 , -1, 1, 0};

    //Base case 1: if you reach a border, return.
    if (x < 0 || x >= gridX || y < 0 || y >= gridY)
    {
        return;
    }

    //Base case 2: if you reach a character that has already been marked. (used for unwinding from the recursion tree).
    if (grid[x][y] == 'X')
    {
        return;
    }

    //Base case 3: if you reach the night sky.
    if (grid[x][y] == '#')
    {
        return;
    }

    //Change the character to an X to prevent re checking later.
    grid[x][y] = 'X';

    //Recursive call. 4 moves (up down left right). the position of the grid is based on the loop indexing the DX and DY arrays.
    //For example, x is 3 and y is 4. x+DX[0] (first loop) would move x up to 2 (up because the array works like that).
    //y+DY[0] doesnt do anything because we are first checking up (the first move). And it would do this for each move, you get the point.
    for (i = 0; i < moves; i++)
    {
        floodFill(grid, gridX, gridY, x+DX[i], y+DY[i]);
    }
}