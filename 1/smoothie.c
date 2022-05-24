//Nicolas Sanchez
//Assignment 1 Making Smoothies
//COP 3502

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//struct item containing an item ID and the number of parts for that item.
typedef struct item
{
    int itemID;
    int numParts;
} item;

//struct recipe containing total parts of the items in a recipe, the number of items in a recipe, and a pointer to an array itemList
//containing items with their number of parts.
typedef struct recipe
{
    int numItems;
    int totalParts;
    item *itemList;
} recipe;

//functions.
char **readIngredients(int numIngredients);
recipe **readAllRecipes(int numRecipes);
recipe *readRecipe(int numItems);
double *calculateOrder(int numSmoothies, recipe **recipeList, int numIngredients);
void printOrder(char** ingredientNames, double* orderList, int numIngredients);
void freeIngredients(char** ingredientList, int numIngredients);
void freeRecipes(recipe** recipeList, int numRecipes);

//main.
int main (void)
{
    //variables
    int i, numIngredients, numRecipes, numStores, numSmoothies;
    char **ingredientList;
    recipe **recipeList;
    double *orderList;

    //ask for number of ingredients
    scanf("%d", &numIngredients);
    while (numIngredients > 100000)
    {
        printf("no\n");
        return 1;
    }
    //call readIngredients and pass through numIngredients.
    ingredientList = readIngredients(numIngredients);

    //ask for number of smoothie reciepies.
    scanf("%d", &numRecipes);
    while (numRecipes > 100000)
    {
        printf("no\n");
        return 1;
    }
    //call readAllRecipes and pass through numRecipes.
    recipeList = readAllRecipes(numRecipes);

    //ask for number of stores.
    scanf("%d", &numStores);
    while (numStores < 1 || numStores > 100)
    {
        printf("no\n");
        return 1;
    }
    //cycle through each store.
    for (i = 0; i < numStores; i++)
    {
        //ask for number of smoothies.
        scanf("%d", &numSmoothies);
        //call calculate order.
        orderList = calculateOrder(numSmoothies, recipeList, numIngredients);
        //print the store number.
        printf("Store #%d:\n", i+1);
        //call print order.
        printOrder(ingredientList, orderList, numIngredients);
        //free order list so nothing bad happens on the next loop.
        free(orderList);
    }
    //freeing memory.
    freeIngredients(ingredientList, numIngredients);
    freeRecipes(recipeList, numRecipes);
    
    return 0;
}

//readIngredients.
char **readIngredients(int numIngredients)
{
    int i;
    char ingredient[21];
    int ingredientLen = 0;

    //dynamically allocate a 2d array of pointers of size numIngredients.
    char **ingredientList = malloc(numIngredients * sizeof(char*));
    
    //loop through to get each ingredient based off of numIngredients.
    for (i = 0; i < numIngredients; i++)
    {
        //ask for ingredient name.
        scanf("%s", ingredient);
        //get the length of the ingredient name including the null terminator in order to malloc.
        ingredientLen = strlen(ingredient) + 1;
        //malloc each index to contain the ingredient string.
        ingredientList[i] = malloc(ingredientLen * sizeof(char));
        //then copy the ingredient into ingredientList for storage.
        strcpy(ingredientList[i], ingredient);
    }
    //return the 2d array ingredient List.
    return ingredientList;
}

//readAllRecipes.
recipe **readAllRecipes(int numRecipes)
{
    int i;
    int numItems;

    //malloc a 2d array of size numRecipes containing pointers.
    recipe **recipeList = malloc(numRecipes * sizeof(recipe*));

    //loop through each recipe.
    for (i = 0; i < numRecipes; i++)
    {
        //malloc each index to contains recipes.
        recipeList[i] = malloc(sizeof(recipe));
        //scan for the number of items that will be in the recipe.
        scanf("%d",  &numItems);
        //call readRecipe and have it return to a spot in recipeList.
        recipeList[i] = readRecipe(numItems);
    }
    //return the 2d array.
    return recipeList;
}

//readRecipe.
recipe *readRecipe(int numItems)
{
    int i;
    
    //malloc a struct called current recipe.
    recipe *currentRecipe = malloc(sizeof(recipe));

    //calloc an array of struct item.
    currentRecipe->itemList = calloc(numItems, sizeof(item));

    //loop through each item.
    for (i = 0; i < numItems; i++)
    {
        //ask for the item id and the number of parts for that item, then store it accordingly.
        scanf("%d %d", &currentRecipe->itemList[i].itemID, &currentRecipe->itemList[i].numParts);
        //increase totalParts.
        currentRecipe -> totalParts += (currentRecipe->itemList[i].numParts);
    }
    //save numItems for this recipe.
    currentRecipe->numItems = numItems;
    //return this recipe.
    return currentRecipe;
}

//calculateOrder.
double *calculateOrder(int numSmoothies, recipe **recipeList, int numIngredients)
{
    int i, j,  recipeID;
    double smoothieWeight;
    
    //calloc an array of doubles of size numIngredients.
    double *amtOfEachItem = calloc(numIngredients, sizeof(double));

    //loop through the number of smoothies.
    for (i = 0; i < numSmoothies; i++)
    {
        //ask for the recipe id.
        scanf("%d", &recipeID);
        //ask for the weight.
        scanf("%lf", &smoothieWeight);
        //loop through each item in the item list for this recipe.
        for (j = 0; j < recipeList[recipeID]->numItems; j++)
        {
            //calculate the order for each ingredient.
            amtOfEachItem[recipeList[recipeID]->itemList[j].itemID] += ((double)recipeList[recipeID]->itemList[j].numParts/recipeList[recipeID]->totalParts)*(smoothieWeight);
        }
    }
    //return the list of orders.
    return amtOfEachItem;
}

//printOrder.
void printOrder(char** ingredientNames, double* orderList, int numIngredients)
{
    int i;

    //loop through the ingredients.
    for (i = 0; i < numIngredients; i++)
    {
        //if an ingredient is not needed, don't print. If an ingredient is needed, print.
        if (orderList[i] > 0)
        {
            //print the name and also the order for that ingredient.
            printf("%s %lf\n", ingredientNames[i], orderList[i]);
        }
    }
}

//freeIngredients.
void freeIngredients(char** ingredientList, int numIngredients)
{
    int i;

    //free each ingredient.
    for (i = 0; i < numIngredients; i++)
    {
        free(ingredientList[i]);
    }
    //free ingredientList.
    free(ingredientList);
}

//freeRecipes.
void freeRecipes(recipe** recipeList, int numRecipes)
{
    int i;

    //free each recipe within recipeList.
    for (i = 0; i < numRecipes; i++)
    {
        free(recipeList[i]);
    }
    //free recipeList
    free(recipeList);
}