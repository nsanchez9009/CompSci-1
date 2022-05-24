//Nicolas Sanchez 10/31/21.
//COP 3502 GUHA.
//Assignment 4, Scholarly Reader.

#include <stdio.h>
#include <stdlib.h>

//Functions declarations.
void mergeSort(int *books, int start, int end);
void merge(int *books, int start, int end, int mid);
void pages(int *books, int bookNum, long long pageLimit);

//Main.
int main(void)
{
    //Loop variables.
    int cases, i;

    //Scan for cases.
    scanf("%d\n", &cases);

    //Loop for each case.
    for (i = 0; i < cases; i++)
    {
        //Loop variable and number of books variable.
        int bookNum, j;
        //long long variable to store the max number of pages. Exceeds 2 billion.
        long long pageLimit;

        //Scan for number of books and page limit.
        scanf("%d %lld\n", &bookNum, &pageLimit);

        //Malloc an array to store the number of pages of each book.
        int *books = malloc(bookNum * sizeof(int));

        //Loop through the array and scan for each book.
        for (j = 0; j < bookNum; j++)
        {
            scanf("%d", &books[j]);
        }

        //merge sort function call. bookNum - 1 to find the index of the last position in the array.
        mergeSort(books, 0, bookNum - 1);

        //Take the now sorted array and pass it into pages to get the result.
        pages(books, bookNum, pageLimit);

        free(books);   
    }
    return 0; 
}

//Merge sort function (splitting the array).
void mergeSort(int *books, int start, int end)
{
    //Divide and conquer.
    int mid;

    //Recursive base case. If start was to equal end, the splitting would be done and we would be left with 1 item.
    if (start < end)
    {
        //Get mid value.
        mid = (start + end)/2;

        //call for left side.
        mergeSort(books, start, mid);
        //call for right side.
        mergeSort(books, mid + 1, end);
        //sorting function call.
        merge(books, start, end, mid + 1);
    }
}

//Merge function. Sorting the values.
void merge(int *books, int start, int end, int mid)
{
    //Index for the temp array.
    int tempI = 0;
    //Index for the books array left side start.
    int side1 = start;
    //Index for the books array right side start.
    int side2 = mid;
    //Length of the array.
    int length = (end - start) + 1;
    
    //Calloc the temp array to the size of the number of numbers we are working with.
    int *temp = calloc(length, sizeof(int));

    //Loop to sort through each half of the books array.
    while (side1 < mid || side2 <= end)
    {
        //If the right side finished before the left side. This means if the right is done, just put everything from the left back into the array.
        //If the left side is not finished and the left side value is less than right side value.
        if (side2 > end || (side1 < mid && books[side1] < books[side2]))
        {
            //take the value from the left side and put it into the temp array.
            temp[tempI] = books[side1];
            //index to the next position in the temp array.
            tempI++;
            //index to the next position of the left side.
            side1++;
        }

        //If the right side is less than the left.
        else
        {
            //take the value from the right side and put it into the temp array.
            temp[tempI] = books[side2];
            //index to the next posistion in the temp array.
            tempI++;
            //index to the next position of the right side
            side2++;
        }
    }

    //Copy the values from the temp array into the correct location of the books array.
    for (tempI = start; tempI <= end; tempI++)
    {
        books[tempI] = temp[tempI - start];
    }

    //free temp.
    free(temp);
}

//Pages function. Calculate the amount of books you're able to read.
void pages(int *books, int bookNum, long long pageLimit)
{
    //Loop variable set to 0 because I'm indexing with a while loop.
    int i = 0;
    //Store the amount of pages.
    long long currentPages = 0;
    //Store the amount of books read.
    int totalBooks = 0;

    //Loop through the books array.
    for (i = 0; i < bookNum; i++)
    {
        //if the current pages plus the pages for the next book exceed the page limit, break.
        if((currentPages + books[i]) > pageLimit)
        {
            break;
        }

        //add the number of pages for the book to the current pages.
        currentPages += (long long)books[i];
        //increase the number of books read.
        totalBooks++;
    }

    //print the number of books read.
    printf("%d\n", totalBooks);
}