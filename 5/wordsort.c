//Nicolas Sanchez
//COP 3502 GUHA 11/14/21
//Assignment 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Tree node struct.
typedef struct node
{
    char nodeWord[21];
    int wordFreq;
    int wordDepth;
    struct node *left;
    struct node *right;
}node;

//Word struct for storing input.
typedef struct wordArrayS
{
    char nodeWord[21];
    int wordFreq;
}wordArrayS;

//Functions.
node *buildTree(node *root, int action, char word[], int *count);
node *insert(node *current, char word[], int depth, int *count);
node *query(node *current, char word[]);
void inorder(node *root, wordArrayS *wordArray);
void mergeSort(wordArrayS *wordArray, int start, int end);
void merge(wordArrayS *wordArray, int start, int end, int mid);
void freeTree(node *root);

//Main.
int main(void)
{
    //"case", loop, and action variables.
    int totalActions, i, action;
    //Array to contain a word.
    char word[20];
    //Set a pointer value to 0 without it being NULL.
    int *count = calloc(1, sizeof(int));
    //Used to create the array of words later.
    int size;

    //Ask for the number of actions.
    scanf("%d", &totalActions);

    //Create root pointer for the bin tree.
    node *root = NULL;

    //Actions loop.
    for (i = 0; i < totalActions; i++)
    {   
        //Ask for the action to be performed and the word.
        scanf("%d %s", &action, word);

        //Add the word to the bin tree.
        root = buildTree(root, action, word, count);
    }

    //Set the value of count to size (just to prevent any possible issues).
    size = *count;

    //Create the array of structs that will contain the words and their frequencies.
    wordArrayS *wordArray = malloc(size * sizeof(wordArrayS));

    //Inorder function call done to copy the values from the bin tree into the array.
    inorder(root, wordArray);

    //Merge sort function call done to sort the array.
    mergeSort(wordArray, 0, size - 1);

    //Print out the words and their frequencies.
    for (i = 0; i < size; i++)
    {
        printf("%s %d\n", wordArray[i].nodeWord, wordArray[i].wordFreq);
    }

    //Free count.
    free(count);
    //Free the array.
    free(wordArray);
    //freeTree function call done to free each node in the bin tree.
    freeTree(root);

    return 0;
}

//buildTree.
node *buildTree(node *root, int action, char word[], int *count)
{
    //If the word is to be inserted into the tree.
    if (action == 1)
    {   
        //Call the insert fucntion and add the word.
        root = insert(root, word, 0, count);
        //Return the pointer to the tree.
        return root;
    }
    //If the action is a query.
    else
    {
        //Create a pointer in order to save the location of the node in the bin tree.
        //Call the query function.
        node *res = query(root, word);
        
        //If the pointer has a node.
        if (res != NULL)
        {   
            //Print the word frequency and depth.
            printf("%d %d\n", res->wordFreq, res->wordDepth);
            //return the original pointer.
            return root;
        }
        
        //If res does not have a node, print the requested statement.
        printf("-1 -1\n");
        //return the original pointer.
        return root;
    }
}

//Insert.
node* insert(node *current, char word[], int depth, int *count)
{
    //If the tree is empty (or an empty location has been reached) create a new node.
    if (current == NULL)
    {
        node *newNode = (node*)malloc(sizeof(node));
        newNode->right = NULL;
        newNode->left = NULL;
        newNode->wordFreq = 1;
        newNode->wordDepth = depth;
        strcpy(newNode->nodeWord, word);
        //Increase the value of count in order to track the size of the bin tree.
        (*count)++;
        return newNode;
    }

    //If the word in the tree is greater than the new word.
    else if (strcmp(current->nodeWord, word) > 0)
    {
        //Proceed left while tracking the depth recursivly.
        current->wordDepth = depth;
        current->left = insert(current->left, word, depth + 1, count);
    }
    //If the word in the tree is less than the new word.
    else if (strcmp(current->nodeWord, word) < 0)
    {
        //Proceed right while tracking the depths recursivly.
        current->wordDepth = depth;
        current->right = insert(current->right, word, depth + 1, count);
    }
    //If the words are the same (strcmp == 0).
    else
    {
        //Increase the word frequency.
        current->wordFreq++;
    }

    //return.
    return current;
}

//Query.
node *query(node *current, char word[])
{
    //If the word is not found here (or just doesnt exist within the tree).
    if (current == NULL)
    {
        return NULL;
    }

    //Proceed left.
    else if (strcmp(current->nodeWord, word) > 0)
    {
        return query(current->left, word);
    }

    //Proceed right.
    else if (strcmp(current->nodeWord, word) < 0)
    {
        return query(current->right, word);
    }

    //If the word has been found, return the pointer to this word.
    else if (strcmp(current->nodeWord, word) == 0)
    {
        return current;
    }

    return NULL;
}

//Inorder.
void inorder(node *root, wordArrayS *wordArray)
{
    //This is used to iterate through the word array.
    //Because this function contains recursive calls, this variable needs to be static.
    //If not, the value would be reset with each call.
    static int i = 0;

    //If the tree is empty or the end has been reached.
    if(root == NULL)
    {
        return;
    }
    //Go left.
    inorder(root->left, wordArray);
    //Copy the word and word frequency from the bin tree to the word array.
    strcpy(wordArray[i].nodeWord, root->nodeWord);
    wordArray[i].wordFreq = root->wordFreq;
    i++;
    //Go right.
    inorder(root->right, wordArray);
}

//MergeSort.
void mergeSort(wordArrayS *wordArray, int start, int end)
{
    //Divide and conquer.
    int mid;

    //Recursive base case. If start was to equal end, the splitting would be done and we would be left with 1 item.
    if (start < end)
    {
        //Get mid value.
        mid = (start + end)/2;

        //call for left side.
        mergeSort(wordArray, start, mid);
        //call for right side.
        mergeSort(wordArray, mid + 1, end);
        //sorting function call.
        merge(wordArray, start, end, mid + 1);
    }
}

//Merge.
void merge(wordArrayS *wordArray, int start, int end, int mid)
{
    //Index for the temp array.
    int tempI = 0;
    //Index for the word array left side start.
    int side1 = start;
    //Index for the word array right side start.
    int side2 = mid;
    //Length of the array.
    int length = (end - start) + 1;
    
    //Malloc the temp array to the amount of words we are working with.
    wordArrayS *temp = malloc(length * sizeof(wordArrayS));

    //Loop to sort through each half of the words array.
    while (side1 < mid && side2 <= end)
    {
        //If the left side is greater than the right side.
        if (wordArray[side1].wordFreq > wordArray[side2].wordFreq)
        {
            //take the value from the left side and put it into the temp array.
            temp[tempI] = wordArray[side1];
            //index to the next position in the temp array.
            tempI++;
            //index to the next position of the left side.
            side1++;
        }

        //If the right side is less than the left.
        else if (wordArray[side1].wordFreq < wordArray[side2].wordFreq)
        {
            //take the value from the right side and put it into the temp array.
            temp[tempI] = wordArray[side2];
            //index to the next posistion in the temp array.
            tempI++;
            //index to the next position of the right side
            side2++;
        }

        //If the word frequencies are the same, compare the words together.
        else if (wordArray[side1].wordFreq == wordArray[side2].wordFreq)
        {
            //If the left word is less than the right word.
            if (strcmp(wordArray[side1].nodeWord, wordArray[side2].nodeWord) < 0)
            {
                //Save the left word into the temp array.
                temp[tempI] = wordArray[side1];
                //index to the next position in the temp array.
                tempI++;
                //index to the next position of the left side.
                side1++;
            }

            //If the left word is greater than the right word.
            else if (strcmp(wordArray[side1].nodeWord, wordArray[side2].nodeWord) > 0)
            {
                //Save the right word into the temp array.
                temp[tempI] = wordArray[side2];
                //index to the next posistion in the temp array.
                tempI++;
                //index to the next position of the right side
                side2++;
            }
        }
    }

    //If side1 has not finished, copy the remaining words into the temp array.
    while (side1 < mid)
    {
        temp[tempI] = wordArray[side1];
        //index to the next position in the temp array.
        tempI++;
        //index to the next position of the left side.
        side1++;
    }

    //If side2 has not finished, copy the remaining words into the temp array.
    while (side2 <= end)
    {
        temp[tempI] = wordArray[side2];
        //index to the next posistion in the temp array.
        tempI++;
        //index to the next position of the right side
        side2++;
    }

    //Copy the values from the temp array into the correct location of the books array.
    for (tempI = start; tempI <= end; tempI++)
    {
        wordArray[tempI] = temp[tempI - start];
    }

    //free temp.
    free(temp);
}

//FreeTree
void freeTree(node *root)
{
    //If an end has been reached or the tree is empty.
    if (root == NULL)
    {
        return;
    }

    //Go left.
    freeTree(root->left);
    //Go right.
    freeTree(root->right);
    
    //Free the current node.
    free(root);
}