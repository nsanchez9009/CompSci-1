//Nicolas Sanchez
//Tree House Walking
//COP 3502 Guha

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Structure containing the x and y values for a tree. Used to calculate the distances later.
typedef struct tree{
    int x;
    int y;
} tree;

//Function headers.
double distance(int x1, int y1, int x2, int y2);
void precompDistance(tree *trees, double **distanceGrid, int numTrees);
double permPairs(double **distanceGrid, int *check, int numTrees, int permCount, int *testArray);
double getSum(double **distanceGrid, int *testArray, int numTrees);
void freeArray(double **distanceGrid, int *testArray, tree *trees, int *check, int numTrees);

//Main.
int main(void)
{
     //Variables.
     int numCases, numTrees, sum, i, j;
     int x = 0;
     int y = 0;

     //Ask for the number of cases.
     scanf("%d\n", &numCases);

     //Loop for the amount of cases.
     for (i = 0; i < numCases; i++)
     {
          //Ask for the number of trees (or ropes technically).
          scanf("%d", &numTrees);

          //Get the real number of trees.
          numTrees *= 2;

          //This array will contain a permutation of the trees that will be used to test pairs.
          int *testArray = malloc(numTrees * sizeof(int));

          //this is a grid containing the distances of each pair.
          double **distanceGrid = malloc(numTrees * sizeof(double*));

          //this is an array of structs containing each tree and its coordinates.
          tree *trees = malloc(numTrees * sizeof(tree));

          //bool array to use as a base case.
          int *check = calloc(numCases, sizeof(int));

          //Loop through each tree and ask for the x and y coordinates.
          for (j = 0; j < numTrees; j++)
          {
               distanceGrid[j] = malloc(numTrees * sizeof(double));
               scanf("%d %d", &trees[j].x, &trees[j].y);
          }

          //Calculate the distances.
          precompDistance(trees, distanceGrid, numTrees);

          //Print the minimum sum.
          printf("%.3lf\n", permPairs(distanceGrid, check, numTrees, 0, testArray));
          
          //free.
          freeArray(distanceGrid, testArray, trees, check, numTrees);
     }
}

//Distance calculator.
double distance(int x1, int y1, int x2, int y2)
{
     int distX, distY, distance;

     distX = x2 - x1;
     distY = y2 - y1;

     distX = distX * distX;
     distY = distY * distY;

     return sqrt(distY + distX);
}

//Storing distance calculations into the grid.
void precompDistance(tree *trees, double **distanceGrid, int numTrees)
{
     //Loop variables.
     int i, j;
     
     //Loop through the x axis.
     for (i = 0; i < numTrees; i++)
     {
          //Loop through the y axis.
          for (j = 0; j < numTrees; j++)
          {
               //Optimization preventing repeated calculations. Matching values and equivalent values.
               if (i >= j)
               {
                   continue;
               }
               
               //store the value into its position on the grid.
               distanceGrid[i][j] = distance(trees[i].x, trees[i].y, trees[j].x, trees[j].y);
          }
     }
}

//Function that creates permutations.
double permPairs(double **distanceGrid, int *check, int numTrees, int permCount, int *testArray)
{
     //Variables. I is used as a loop variable and also as a way to find the numbers to create a permutation.
     int i;
     double sum;

     //Base case. If the permutation is finished, return the sum.
     if (permCount == numTrees)
     {
          return getSum(distanceGrid, testArray, numTrees);
     }

     //set the minimum sum to a really high number so that it can be reset on the first call. If not, minSum would never change.
     double minSum = 99999999999;

     //Loop through the amount of trees.
     for (i = 0; i < numTrees; i++)
     {

          //if a tree has already been used, continue.
          if (check[i] == 1)
          {
               continue;
          }

          //Optimization. If the position is odd (x value for a pair), its greater than 0 (to prevent accessing bad memory),
          //and if the first value (x) of an x and y pair is greater than the y value, continue. This is done to skip over repeated pairs.
          //A repeated pair; (1, 2) and (2, 1). Every pair will have a match like this, so we skip over the others and only keep 1.
          //To do that we apply this formatting rule.
          if ((permCount % 2 != 0 && permCount > 0) && testArray[permCount - 1] > i)
          {
              continue;
          }

          //Optimization. This one works the same way but instead of checking the y, you check to see if the x value in the current pair is
          //greater than the x value in the previous pair. If it is not, continue. For example, (1, 2) (3, 4) and (3, 4) (1, 2).
          //The second one is the same, so we get rid of it by applying a second formatting rule.
          else if (permCount % 2 == 0 && permCount > 1 && testArray[permCount - 2] > i)
          {
               continue;
          }

          //Set the put the chosen tree number (i) in the test array's recursion count position.
          testArray[permCount] = i;

          //Change the bool array value so that the computer knows that this number has already been used.
          check[i] = 1;

          //Recursive call to create the permutation. Increase the recursion count by 1. 
          sum = permPairs(distanceGrid, check, numTrees, permCount + 1, testArray);

          //If the sum returned is less than the minimum sum. Overwrite it.
          if (sum < minSum)
          {
               minSum = sum;
          }

          //reset check to 0 for each tree so that the next permutation can choose from all the trees.
          check[i] = 0;
     }

     //return the minimum sum.
     return minSum;
}

//getSum Function used to caluclate the sum of distances in a permutation.
double getSum(double **distanceGrid, int *testArray, int numTrees)
{
     //Variables.
     int i;
     double sum = 0;

     //Loop through the test array by 2 because we are adding the distances between 2 trees.
     for (i = 0; i < numTrees; i += 2)
     {
          //testArray {1, 2, 3, 4, 5, 6}
          //Distance of 1 and 2. Distance of 3 and 4. Etc....
          sum += distanceGrid[testArray[i]][testArray[i + 1]];
     }

     //return the sum of distances.
     return sum;
}

//function for freeing.
void freeArray(double **distanceGrid, int *testArray, tree *trees, int *check, int numTrees)
{
     //Loop variable.
     int i;

     //Free each y value in the distance grid.
     for (i = 0; i < numTrees; i++)
     {
          free(distanceGrid[i]);
     }

     //Free the x values.
     free(distanceGrid);

     //Free other mallocs/callocs.
     free(testArray);
     free(trees);
     free(check);
}
