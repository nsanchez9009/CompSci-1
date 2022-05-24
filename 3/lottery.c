//Nicolas Sanchez.
//COP 3502 GUHA.
//Winning the Lottery.

#include <stdio.h>
#include <stdlib.h>

//A single node structure.
typedef struct node{
    //data for the node.
    int data;

    //pointer to the next node.
    struct node *next;
} node;

//Structure for a group containing the groups information.
typedef struct group
{
    int people;
    int skip;
    int threshold;
} group;

//Functions.
node *createNode(int data);
node *addtolist(int index, node *list);
void phase1(group *groups, int groupAmount, int groupstructIndex, int **groupWinners);
node *eliminate(node *list, group* groups, int groupstructIndex);
void freeList(node *list);
void storeWinners(node *list, int **groupWinners, group *groups, int groupStructIndex);
void phase2(int **groupWinners, int groupAmount, group *groups);

//Main.
int main(void)
{
    //Case variable and loop variable.
    int cases, i, k;

    scanf("%d\n", &cases);

    //Loop for each case.
    for (i = 0; i < cases; i++)
    {
        int groupAmount, j;

        scanf("%d\n", &groupAmount);

        //Malloc an array of structs of type group. I do this so I can store the information for each group easily and still be able to access it later.
        group *groups = malloc(groupAmount * sizeof(group));

        //Malloc a 2d int array so that I can store the winners of each group.
        int **groupWinners = malloc(groupAmount * sizeof(int*));

        //Loop for each group.
        for (j = 0; j < groupAmount; j++)
        {
            //Scan for group information.
            scanf("%d %d %d\n", &groups[j].people, &groups[j].skip, &groups[j].threshold);

            //Phase 1 function call.
            phase1(groups, groupAmount, j, groupWinners);
        }

        //Phase 2 function call.
        phase2(groupWinners, groupAmount, groups);

        //Loop through groupwinners and free each array within in array.
        for (k = 0; k < groupAmount; k++)
        {
            free(groupWinners[k]);
        }

        //Free groupwinners and groups.
        free(groupWinners);
        free(groups);
    }

    return 0;
}

//Create node function.
node *createNode(int data)
{
    //Mallocs a node.
    node *newNode = (node*)malloc(sizeof(node));

    //Sets the data for that node the data the was passed in.
    newNode->data = data;

    //Set the next pointer to NULL.
    newNode->next = NULL;

    //return the node.
    return newNode;
}

//Add a node to the list.
node *addtolist(int index, node *list)
{
    //create a new node.
    node *newNode = createNode(index);
    
    //If the list is empty, just return the node making it the only node in the list.
    if (list == NULL)
    {
        return newNode;
    }

    //Create a current pointer to sort throught the list.
    node *current = list;

    //if current->next = NULL then the end of the list will be the next node.
    while (current->next != NULL)
    {
        //sort through by re assigning current.
        current = current->next;
    }

    //set the last node to point to the new node, adding the new node to the list.
    current->next = newNode;

    //return the updated list.
    return list;
}

//Phase 1.
void phase1(group *groups, int groupAmount, int groupstructIndex, int **groupWinners)
{
    //Loop variable.
    int i;
    //List head.
    node *list;
    //Set the list head to NULL because there is nothing in the list yet.
    list = NULL;

    //Loop through the amount of people.
    for (i = 0; i < groups[groupstructIndex].people; i++)
    {
        //create a node for each person and add it to the list.
        list = addtolist(i + 1, list);
    }

    //Print the group number.
    printf("Group #%d:\n", groupstructIndex + 1);
    
    //Eliminate function call.
    list = eliminate(list, groups, groupstructIndex);

    //Malloc the array for the winners.
    groupWinners[groupstructIndex] = malloc(groups[groupstructIndex].threshold * sizeof(int));

    //storeWinners function call.
    storeWinners(list, groupWinners, groups, groupstructIndex);

    //FreeList function call.
    freeList(list);
}

//Phase 2.
void phase2(int **groupWinners, int groupAmount, group *groups)
{
    //Loop variables.
    int i, j;

    //Winner variable, set to a high number so the first winner can be compared.
    int winner = 999999999;

    //Winner group number variable. Same rule.
    int winnerGroup = 999999999;

    //Loop for each group.
    for (i = 0; i < groupAmount; i++)
    {
        //Loop through the winners of each group.
        for (j = 0; j < groups[i].threshold; j++)
        {
            //If a winner in a group is less than the current winner.
            if (groupWinners[i][j] < winner)
            {
                //If this winner is equal to the current winner, continue.
                //This is done incase a group later has the same person as a winner.
                if (groupWinners[i][j] == winner)
                {
                    continue;
                }
                //If not any of those, the new winner and winner group are set.
                else
                {
                    winner = groupWinners[i][j];
                    winnerGroup = i + 1;
                }
            }
            //I cant remember why I added this. I have a bad headache and trying to understand isnt working right now.
            else if (j == groups[i].threshold - 1)
            {
                break;
            }
        }
    }
    //Print the lottery winner.
    printf("Lottery winner is person %d from group %d.\n", winner, winnerGroup);
}

//Eliminate a node.
node *eliminate(node *list, group* groups, int groupstructIndex)
{
    //Loop variables.
    int i, j;

    //index pointer to sort through the list.
    node *current = list;

    //a pointer for the node before the current node.
    node *before = NULL;

    //a pointer to delete a node.
    node *delet = NULL;

    //find the amount of eliminations by subtracting the threshold from the amount of people.
    int elimAmount = groups[groupstructIndex].people - groups[groupstructIndex].threshold;

    //Make our linked list circular.
    //Sort throught the list.
    while (current != NULL)
    {
        //If the pointer to the next node is NULL, we have reached the end.
        if (current->next == NULL)
        {
            //set the last node to point to the beginning.
            current->next = list;

            //break or else we will be stuck forever.
            break;
        }
        //If not, keep going.
        else
        {
            current = current->next;
        }
    }

    //reassign current to the beginning.
    current = list;

    //Loop for the amount of eliminations.
    for (i = 0; i < elimAmount; i++)
    {   
        //If the skip value for a group is 0.
        if (groups[groupstructIndex].skip == 0)
        {
            //sort to the end of the circular list by setting the terminator to the front instead of NULL.
            while(current->next != list)
            {
                current = current->next;
            }
            //save the "last" node in the list
            before = current;

            //set the new head to the next node.
            list = current->next->next;

            //mark the node we want to delete for deletion.
            delet = current->next;

            //print the nodes person number, data.
            printf("%d\n", delet->data);

            //re link the list by setting the last node to the new head, keeping it a circle.
            before->next = current->next->next;

            //set the pointer for the node we will delete to NULL. Im honestly not sure if this is even needed.
            delet->next = NULL;

            //free the node.
            free(delet);

            //set the new current.
            current = before->next;

            //continue to the next instance of the for loop.
            continue;
        }

        //Loop for the number of skips.
        for (j = 0; j <= groups[groupstructIndex].skip; j++)
        {
            //save the node before the node we will delete.
            if (j == groups[groupstructIndex].skip - 1)
            {
                before = current;
            }

            //If we finished skipping and reached the node.
            else if (j == groups[groupstructIndex].skip)
            {
                //If the node we landed on is the head (and not the beginning of this), re assign the head to the following node.
                if (current == list && i >= 1)
                {
                    list = current->next;
                }

                //remove the node from the list and re link the list.
                before->next = current->next;

                //mark the node for deletion.
                delet = current;

                //again with this.
                delet->next = NULL;

                //print the eliminated person.
                printf("%d\n", delet->data);

                //free the node.
                free(delet);

                //re assign current.
                current = before->next;

                //continue to the next loop instance.
                continue;
            }

            //keep skipping.
            current = current->next;
        }
    }

    //return the winners of the groups in an updated list.
    return list;
}

//Storing the winners.
void storeWinners(node *list, int **groupWinners, group *groups, int groupStructIndex)
{
    //Loop variable.
    int i;

    //pointer to sort throught the list.
    node *current = list;

    //Loop for the number of winners for this group.
    for (i = 0; i < groups[groupStructIndex].threshold; i++)
    {
        //save the person from the list into its spot into the groupWinners 2d array.
        groupWinners[groupStructIndex][i] = current->data;

        //move to the next node/person.
        current = current->next;
    }
}

//Free each node in the list.
void freeList(node *list)
{
    //Pointer for sorting through the list.
    node *current = list;

    //Saving the next node after the node marked for deletion.
    node *next = NULL;

    //Node to delete.
    node *delet = NULL;

    //Sort through a circular linked list.
    do
    {
        current = current->next;
    } while (current->next != list);

    //Set the last pointer to NULL destroying the circle.
    current->next = NULL;

    //resetting current to the beginning.
    current = list;

    //Sort through the list like normal.
    while (current != NULL)
    {
        //Save the next node in order to re assign current.
        next = current->next;

        //mark the current node for deletion.
        delet = current;

        //free the node.
        free(delet);

        //re assign current.
        current = next;
    }
}
