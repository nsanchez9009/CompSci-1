//Nicolas Sanchez.
//COP 3502 GUHA, 10/31/2021
//Test case generator for Assignment 4, Scholarly Reader.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Main.
int main(void)
{
    //Initialize srand seed so that you get random values each time you run the program.
    srand(time(NULL));

    //Create pointer output to file.
    //Create/open a file and sets it to write (overwrites current data).
    FILE *output = fopen("randomcase.in", "w");

    //Loop variables.
    int i, j;
    //Random int case variable from 1 - 25.
    int cases = 1;

    //Print to file the cases.
    fprintf(output, "%d\n", cases);

    //Loop for each case.
    for (i = 0; i < cases; i++)
    {   
        //Random int for the number of books, 1 - 100000.
        int books = rand() % (int)pow(10, 5) + 1;
        //Random long long for the page limit, 1 - 10^14.
        long long pageLimit = rand() % (long long)(pow(10, 14) - pow(10, 11) + 1) + pow(10, 11);
       
        //print to file the number of books and page limit.
        fprintf(output, "%d %lld\n", 100000, pageLimit);

        //Loop for each book.
        for (j = 0; j < books; j++)
        {
            //print to file the random number of pages for each book, 1 - 10^9.
            fprintf(output, "%d ", rand() % 1000000001);
        }
        //new line.
        fprintf(output, "\n");
    }
    //Close the file.
    fclose(output);

    return 0;
}