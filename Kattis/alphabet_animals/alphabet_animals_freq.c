//Nicolas Sanchez
//RP1 Alphabet Animals Kattis
//9/3/21

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//function declarations.
void checkWords(char **words, char word[], int nameAmount, int freqArray[]);

//main.
int main(void)
{
    //amount of names and looping variable.
    int nameAmount, i, ireallywanttoignoreimportantinfo;
    //first word input variable.
    char word[21];
    //word input array for the loop.
    char wordInput[21];
    //length of the word so we know how much memory we need to allocate.
    int wordLength;
    //freq array variable.
    int freqArray[26];
    //initalizes all indexes in freqArray to 0.
    for(i = 0; i < 26; i++)
    {
        freqArray[i] = 0;
    }
    //getting first word input and the number of names. Used ireallywanttoignoreimportantinfo because the error was kind of annoying.
    ireallywanttoignoreimportantinfo = scanf("%s\n%d\n", word, &nameAmount);

    //keep asking until nameAmount is a valid input.
    while (nameAmount < 0 && nameAmount > 100000)
    {
        ireallywanttoignoreimportantinfo = scanf("%d", &nameAmount);
    }

    //making a pointer that points to an array(which is just an array but an array is a pointer) f pointers whos amount is determined by nameAmount.
    char **words = malloc(nameAmount * sizeof(char*)); 
    
    //loop for creating each array that will hold a word and storing the word into the created array.
    for (i = 0; i < nameAmount; i++)
    {
        //ask for word.
        ireallywanttoignoreimportantinfo = scanf("%s", wordInput);

        //get the length of the word so you know how big to make the array that will hold a word.
        wordLength = strlen(wordInput) + 1;

        //setting the size of the array. wordLength being how many array blocks, and sizeof(char) being what each array block will be.
        words[i] = malloc(wordLength * sizeof(char));

        //copying the word, wordInput, into the array, words.
        strcpy(words[i], wordInput);
    }
    //storing the first character of each word in words using ascii math.
    for(i=0; i<nameAmount; i++)
    {
        freqArray[words[i][0] - 'a']++;
    }
    checkWords(words, word, nameAmount, freqArray);
}

//check words and see if they do stuff.
void checkWords(char **words, char word[], int nameAmount, int freqArray[])
{
    int i; //loop variable.
    int flagFirst; //flag variable for knowing when to save the first correct word.
    int flagWin = 0; //flag variable to when a correct answer is made.
    int eliminated; //elimination value.
    char topName[21]; //array containing a string of the very first word.
    int topLength; //array to get the index for the last character in the very first word.
    char firstElimination[21]; //array containing the first word that eliminates.
    int elimFlag = 0; //if a word eliminates at any point, this is increased.
    int wordLength;//find the index for the last character in the string word.
    
    //copy the very first word in topName.
    strcpy(topName, word);
    //get the index for the last character in the first word.
    topLength = strlen(topName) - 1;
    //loop through each word.
    for (i = 0; i < nameAmount; i++)
    {
        //if the last character of the very first word equals the first character of the next word and if flagwin = 0. This is done to just save the first correct word.
        if (topName[topLength] == words[i][0] && flagWin == 0)
        {
            //copy the next word into word.
            strcpy(word, words[i]);
            wordLength = strlen(word) - 1;
            //save the position of the first word into flag first.
            flagFirst = i;
            //increase flag win because the answer was correct.
            flagWin++;
            //Check to see if the word eliminates.
            if(freqArray[word[wordLength]-'a'] <= 1)
            {
                if(word[0] == word[wordLength])
                {
                    eliminated++;
                    strcpy(firstElimination, words[i]);
                    break;
                }
                else if(freqArray[word[wordLength]-'a'] == 0)
                {
                    eliminated++;
                    strcpy(firstElimination, words[i]);
                    break;
                }
                else
                {
                    continue;
                }
                //if it turns out a word eliminates, increase elim flag because the next time this loops "eliminated" will be changed to a new value.
                if (eliminated > 0)
                {
                    elimFlag++;
                }
                //save it.
                else if (eliminated > 0 && elimFlag == 1)
                {
                    printf("%s", word);
                    strcpy(firstElimination, word);
                }
            }
        }
        //if the last character of the very first word equals the first character of the next word.
        else if (topName[topLength] == words[i][0])
        {
            //increase flagwin because the word is correct.
            flagWin++;
            //copy the new word into word for testing.
            strcpy(word, words[i]);
            //check to see if the word eliminates.
            wordLength = strlen(word) - 1;
            if(freqArray[word[wordLength]-'a'] <= 1)
            {   
                if(word[0] == word[wordLength])
                {
                    eliminated++;
                    strcpy(firstElimination, words[i]);
                    break;
                }
                else if(freqArray[word[wordLength]-'a'] == 0)
                {
                    eliminated++;
                    strcpy(firstElimination, words[i]);
                    break;
                }
                else
                {
                    continue;
                }
            }
            //if it turns out a word eliminates, increase elim flag because the next time this loops "eliminated" will be changed to a new value.
            if (eliminated > 0)
            {
                elimFlag++;
            }
            if (eliminated > 0 && elimFlag == 1)
            {
                strcpy(firstElimination, word);
            }
        }
    }
    //if flagWin equals 0, print the question mark. This means that all words were incorrect and flag win never increased.
    if (flagWin == 0)
    {
        printf("?\n");
    }
    //if flagwin is less than nameAmount and flagWin is greater than 0. Meaning there was a correct word.
    else if (flagWin <= nameAmount && flagWin > 0)
    {
        //if elimination requirements were met. if elimFlag is greater than 0 it means a word eliminates.
        if (eliminated > 0 || elimFlag > 0)
        {
            //print the first word that eliminated with a !.
            printf("%s!", firstElimination);
        }
        //if elimination requirements were not met. elimFlag never increased, print the first correct word.
        else if (eliminated == 0 && elimFlag == 0)
        {
            //print the first correct word.
            printf("%s", words[flagFirst]);
        }
    }
    //freeing memory.
    for (i = 0; i < nameAmount; i++)
    {
        free(words[i]);
    }
    free(words);
}

