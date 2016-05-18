
//
//  main.cpp
//  Project 5
//
//  Created by Caroline Quigg on 11/9/15.
//  Copyright © 2015 Caroline Quigg. All rights reserved.
//
#define _CRT_SECURE_NO_DEPRECATE

#include <cstring>
#include <iostream>
#include <cctype>
#include "utilities.h"
#include <cassert>
using namespace std;


const int MAX_WORD_LEN = 6;

int manageOneRound(const char words[][MAX_WORD_LEN +1] , int nWords, int wordnum);
void updateStats(int& tot , int& maximum, int& minimum, int rounds, int guesses);
bool isLowerCase (char check [] , int n);
bool isInList (const char words[][MAX_WORD_LEN +1],int nWords, char guess []);
void findStones (const char secret[] , char probe[]);

int main() {
    const int MAX_WORDS = 9000;
    //declare wordList
    char wordList [MAX_WORDS][MAX_WORD_LEN +1];
    //number of words in the list
    int wordNum = loadWords(wordList, MAX_WORDS);
    //check that words were loaded
    if (wordNum < 1)
    {
        cout<<"No words were loaded, so I can't play the game."<<endl;
        return -1;
    }
    

    //prompt for rounds
    cout<<"How many rounds do you want to play? ";
    int rounds;
    cin >> rounds;
    cin.ignore(10000, '\n');
    //check that user input is valid
    if( rounds <=0)
    {
        cout<<"The number of rounds must be positive."<<endl;
        return -1;
    }
    cout <<endl;
    
    int total = 0;
    int max = 0;
    int min  =0;
    cout.setf(ios::fixed);
    cout.precision(2);

    //go through rounds
    for (int i =1 ; i<=rounds ; i++)
    {
        //get secret word info
        int secret_index = randInt(0,wordNum-1);
        int length = strlen(wordList[secret_index]);
        
        //setup round
        cout << "Round " << i << endl;
        cout <<"The secret word is "<<length<< " letters long."<<endl;
        
        //run the round and get results
        int tries = manageOneRound(wordList,wordNum ,secret_index);
        if (tries == 1)
            cout<<"You got it in 1 try."<<endl;
        else
           cout<<"You got it in " << tries <<" tries."<<endl;
        //update the statistics
        updateStats(total, max, min, i, tries);

        cout<<"Average: "<<static_cast<double>(total)/i <<", minimum: "<<min<<", maximum: "<<max<<endl;
        cout<<endl;
    }

}


int manageOneRound(const char words[][MAX_WORD_LEN +1] , int nWords, int wordnum)
{

    const int MAXLINE = 100;
    //check that arguments are valid
    if (nWords<=0||wordnum<0 || wordnum>=nWords) return -1;
    char probe [MAXLINE];
    //prompt user for probe word until probe equals secret word
    int nTries=0;
    do
    {
        cout<<"Probe word: ";
        cin.getline(probe,MAXLINE);
        //check that probe is 4-6 lower case letters
        if (strlen(probe)<4 || strlen(probe)>6 || !isLowerCase(probe, strlen(probe)) )
        {
            //reprompt
            cout<<"Your probe word must be a word of 4 to 6 lower case letters."<<endl;
            continue;
        }
        //check that the probe is a valid word
        if(!isInList(words,nWords,probe))
        {
            //reprompt
            cout<<"I don't know that word."<<endl;
            continue;
        }
        //valid try
        nTries++;
        //find rocks and pebbles
        findStones(words[wordnum],probe);
        
        
    }while (strcmp(probe,words[wordnum])!=0);
    return nTries;
}

void updateStats(int& tot , int& maximum, int& minimum, int rounds, int guesses)
{
    //if only one round, then the total, max, min, all the same
    if (rounds==1)
    {
        tot = guesses;
        maximum=guesses;
        minimum = guesses;
    }
    //else update the max and min, as well as the total
    else
    {
        tot+=guesses;
        if (guesses>maximum)
            maximum = guesses;
        if (guesses<minimum)
            minimum = guesses;
    }
}

bool isLowerCase (char word [] , int n)
{
    //make sure the probe is made up of lowercase letters
    for (int i=0; i<n ;i++)
    {
        //char is not a lowercase letter
        if (!islower(word[i]))
            return false;
    }
    return true;
}

bool isInList (const char words[][MAX_WORD_LEN +1],int nWords, char guess [])
{

    for (int i =0 ; i<nWords ; i++)
    {
        //check if the probe word is in the array
        if (strcmp(guess, words[i]) == 0)
            return true;
    }
    //probe word is not in the word list
    return false;
}

void findStones (const char secret[] , char probe[])
{
    char copy[MAX_WORD_LEN + 1];
    strcpy(copy,secret);
    int rocks=0;
    int pebbles=0;
    const char OFF_LIMITS_SECRET = '0';
    const char OFF_LIMITS_PROBE='1';
    //check if probe and secret are the same
    if (strcmp(secret,probe)==0)
        return;
    
    //search for rocks
    for (int i =0 ;i<strlen(probe) ;i++)
    {
        if(i>= strlen(copy))break;
        if (probe[i] == copy[i])
        {
            rocks++;
            //update probe and keyword copy so that the rock or pebble letter is not considered anymore (i.e. char value changed from lowercase letter to '0')
            //probe and copy changed to different values to avoid errors when searching for pebbles

            copy[i]=OFF_LIMITS_SECRET;
            probe[i]=OFF_LIMITS_PROBE;
        }
    }
    //search for pebbles
    for (int k=0; k<strlen(probe) ; k++)
    {
    for (int j=0 ; j<strlen(secret);j++)
    {
        //found a pebble
        if (probe[k] == copy[j])
        {
            pebbles++;
            //update copy of keyword, so that the rock or pebble letter is not considered anymore (i.e. char value changed from lowercase letter to '0')
            copy[j]=OFF_LIMITS_SECRET;
            //move on to next letter in probe
            break;
        }
    }
    
    }
    cout <<"Rocks: "<<rocks <<", Pebbles: "<<pebbles<<endl;
}


