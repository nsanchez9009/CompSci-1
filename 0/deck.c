#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Nicolas Sanchez
//Assignment 0
//COP 3502 GUHA

//functions.
int findSuit(char deckHalf1[], char deckHalf2[]);
int findAscend(char deckHalf1[], char deckHalf2[]);
int charInt(char card);

//main.
int main()
{ 
  char deckHalf1[52]; //first line of cards.
  char deckHalf2[52]; //second line of cards.
  int caseAmount; //input variable for case amount.
  int i; //loop variable.
  
  //input for case amount.
  scanf("%d", &caseAmount);

  //test case loop.
  for(i = 0; i < caseAmount; i++)
  {
     scanf("%s\n%s", deckHalf1, deckHalf2); //asking for cards.
     printf("%d ", findSuit(deckHalf1, deckHalf2)); //print suit sequence value.
     printf("%d\n", findAscend(deckHalf1, deckHalf2)); //print ascending sequence value.
  }
  return 0;
}

//find suit sequence function.
int findSuit(char deckHalf1[], char deckHalf2[])
{
  int i, x = 1, y = 1; //looping variables.
  int counter = 1; //this is used to record of the current sequence.
  int greatestSequence = 0; //this is used to store the greatest sequence found.
  char currentSuit; //this is used to remember the current suit.
  char deck[52]; //combining both deck halves.

  //loop combining both deck halves and removing unused characters.
  for (i = 1; i < 52; i++)
  {
      if (i <= 26)
      {
          deck[i] = deckHalf1[x];
          x = x + 2;
      }
      else if (i > 26)
      {
          deck[i] = deckHalf2[y];
          y = y + 2;
      }
  }

  currentSuit = deck[0]; //setting foundation for the current suit.
  
  //loop going through deck[].
  for(i = 0; i < 52; i++)
  {
    if (deck[i] == currentSuit) //if the suit is equal to current suit the counter is increased by 1.
    {
      counter++;
    }
    else if (deck[i] != currentSuit) //if not, current suit is reset to the new suit.
    {
       currentSuit = deck[i];
       if (counter > greatestSequence) //counter and greatest sequence are compared.
       {
          greatestSequence = counter; //if true, counters value is given to greatest sequence.
       }
       counter = 1; //counter is reset.
    }
  }
  return greatestSequence; //after the greatest sequence has been found, the value is returned.
}

//find ascending sequence function.
int findAscend(char deckHalf1[], char deckHalf2[])
{
   int i, x = 0, y = 0; //loop variables.
   int counter = 1; //counter.
   int faceValue[52]; //int array used to combine deckhalf 1 and 2 while also removing unused characters. It also will store the changed values.
   int greatestSequence = 0; //high score.

   //loop converting the deck halves into integers and combining them into 1 int array.
   for (i = 0; i < 52; i++)
   {
      if (i <= 26)
      {
         faceValue[i] = charInt(deckHalf1[x]); //char to int.
         x = x + 2; //loop through deck half by 2 in order to avoid suits.
      }
      else
      {
         faceValue[i] = charInt(deckHalf2[y]); //char to int on deck half 2.
         y = y + 2; //loop through deck half by 2 in order to avoid suits.
      }
   }

   //loop finding the acsending sequence in int array faceValue.
   for (i = 0; i < 52; i++)
   {
      if (faceValue[i] == faceValue[i+1]-1) //if the value in front of it is greater by 1, add 1 to counter.
      {
         counter++;
      }
      else if (faceValue[i] == 14 && faceValue[i+1] == 2) //if the value is 14 but with a 2 in front of it, add 1 to counter.
         {
            counter++;
         }
      else //if not ascending by 1. 
      {
         if (counter > greatestSequence) //check to see if counter has passed greatest sequence.
         {
            greatestSequence = counter; //if yes, override greatest sequence with counters value.
         }
         counter = 1; //reset counter.
      }
   }

   return greatestSequence; //return the greatest sequence.
}

//function to find face card values.
int charInt(char card)
{
   int faceValue; //return value for the character.

   //changing character into int.
   switch(card)
   {
      case '2':
         faceValue = 2;
         break;
      case '3':
         faceValue = 3;
         break;
      case '4':
         faceValue = 4;
         break;
      case '5':
         faceValue = 5;
         break;
      case '6':
         faceValue = 6;
         break;
      case '7':
         faceValue = 7;
         break;
      case '8':
         faceValue = 8;
         break;
      case '9':
         faceValue = 9;
         break;
      case 'T':
         faceValue = 10;
         break;
      case 'J':
         faceValue = 11;
         break;
      case 'Q':
         faceValue = 12;
         break;
      case 'K':
         faceValue = 13;
         break;
      case 'A':
         faceValue = 14;
         break;
   }
   return faceValue; //return value based on character.
}