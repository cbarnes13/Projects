#include "sortingcompetition.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <string.h>
#include <iomanip>
#include <algorithm>

using namespace std;

SortingCompetition::SortingCompetition(const string& inputFileName)
{
    //intializes variables
    setFileName(inputFileName);
    wordList = new char*[1000];
    copy = new char*[1000];
    buffer = new char[100];
    listSize = 0;

}

void SortingCompetition::setFileName(const string& inputFileName)
{

    fileName = inputFileName;

}

bool SortingCompetition::readData()
{
    //reads data
    ifstream file(fileName);

    if (!file.is_open())
    {
        cerr<< "File could not be opened"<<endl;
        exit(EXIT_FAILURE);
    }

    string word = " ";

    while (!file.eof())
    {
        if(listSize != 0 && listSize%1000 == 0)
            resize(wordList, listSize);
        file >> word;
        strcpy(buffer,word.c_str());
        addWord(buffer, listSize);
        word = " ";
        listSize++;
    }

    return true;

}

bool SortingCompetition::prepareData()
{
    //copies word list to the copy array
    delete[] copy;
    copy = new char*[listSize];
    for(int counter = 0; counter < listSize; counter++)
        copy[counter] = wordList[counter];
    return true;
}

void SortingCompetition::sortData()
{
    //quickSortMedOfThree(0, listSize-1);
    //selectionSort();
    //bubbleSort();
    mergeSort();
}

void SortingCompetition::bubbleSort(){
    //creates two temp variables
    char* firstTemp;
    char* secondTemp;
    for(int firstVal = 0; firstVal < listSize-1; firstVal++){
        for(int secondVal = 1; secondVal < listSize; secondVal++){
            //copies form copy array to temp vals
            firstTemp = copy[firstVal];
            secondTemp = copy[secondVal];
            //compares length to see if the second word is longer
            //than the first
            if(strlen(firstTemp) < strlen(secondTemp)){
                //switches words
                copy[firstVal] = secondTemp;
                copy[secondVal] = firstTemp;
            }
            //test to see if the words have same length
            if(strlen(firstTemp) == strlen(secondTemp)){
                //test for aphabeticaly
                if(strcmp(firstTemp,secondTemp) > 0){
                    //switches words
                    copy[firstVal] = secondTemp;
                    copy[secondVal] = firstTemp;
                }
            }
        }
    }
}

void SortingCompetition::quickSortMedOfThree(int l, int h){
    if(l < h){
        int p = partition(l, h);
        quickSortMedOfThree(l, p-1);
        quickSortMedOfThree(p+1, h);
    }
}

int SortingCompetition::partition(int low, int high){
    char* pivot = copy[high];
    char* firstTemp;
    //char* secondTemp;
    int i = low-1;

    for(int j = low; j < high; j++){
        if(strlen(copy[j]) < strlen(pivot)){
            i++;
            firstTemp = copy[i];
            copy[i] = copy[j];
            copy[j] = firstTemp;
        }
        if(strlen(copy[j]) == strlen(pivot)){
            if(strcmp(copy[j],pivot) > 0){
                i++;
                firstTemp = copy[i];
                copy[i] = copy[j];
                copy[j] = firstTemp;
            }
        }
    }
    firstTemp = copy[i+1];
    copy[i+1] = copy[high];
    copy[high] = firstTemp;

    return i+1;
}

void SortingCompetition:: selectionSort()
{
    char* temp;
    char* firstTemp;
    char* secondTemp;
    int min_index = 0;

    for ( int i = 0; i < (listSize - 1); i++)
    {
        min_index = i;

        for ( int j = (i+1); j < listSize; j++)
        {
            firstTemp = copy[min_index];
            secondTemp = copy[j];

            if(strlen(firstTemp) > strlen(secondTemp)){
                min_index = j;
            }

            else if (strlen(firstTemp) == strlen(secondTemp) && strcmp(copy[j] , copy[min_index]) < 0 )
            {
                min_index = j;
            }
        }

        if (min_index != i)
        {
            temp = copy[i];
            copy[i] = copy[min_index];
            copy[min_index] = temp;
        }

    }

}

void SortingCompetition:: mergeSort()
{
    int firstHalf = 0;
    int secondHalf = 0;


    if ( (listSize % 2) == 0)
    {
        firstHalf = listSize/2;
        secondHalf = firstHalf;
    }
    else
    {
        firstHalf = (listSize-1)/2;
        secondHalf = firstHalf + 1;
    }

    char** firstHalfTemp = new char*[firstHalf];
    for (int fht = 0; fht < firstHalf; fht++)
    {
        firstHalfTemp[fht] = copy[fht];
    }
    sort(firstHalfTemp[0] , firstHalfTemp[firstHalf-1]);

    char** secondHalfTemp = new char*[secondHalf];
    for (int sht = firstHalf; sht < listSize; sht++)
    {
        secondHalfTemp[sht] = copy[sht];
    }
    sort(secondHalfTemp[0] , secondHalfTemp[secondHalf-1]);

    //http://mathbits.com/MathBits/CompSci/Arrays/Merge.htm

    int firstCounter = 0;
    int secondCounter = 0;
    int finalCounter = 0;
    char* firstTemp;
    char* secondTemp;

    while ( (firstCounter < firstHalf) && (secondCounter < secondHalf) )
    {
        firstTemp = firstHalfTemp[firstCounter];
        secondTemp = secondHalfTemp[secondCounter];

        if(strlen(firstTemp) > strlen(secondTemp))
        {
            copy[finalCounter] = secondTemp;
            secondCounter++;
        }

        else if (strlen(firstTemp) == strlen(secondTemp) && strcmp(firstTemp , secondTemp) < 0 )
        {
            copy[finalCounter] = secondTemp;
            secondCounter++;
        }
        else
        {
            copy[finalCounter] = firstTemp;
            firstCounter++;
        }

        finalCounter++;
    }

    while (firstCounter < firstHalf)
    {
        firstTemp = firstHalfTemp[firstCounter];
        copy[finalCounter] = firstTemp;
        firstCounter++;
        finalCounter++;
    }

    while (secondCounter < secondHalf)
    {
        secondTemp = secondHalfTemp[secondCounter];
        copy[finalCounter] = secondTemp;
        secondCounter++;
        finalCounter++;

    }


}

void SortingCompetition::outputData(const string &outputFileName){
    //prints out sorted words
    ofstream outputFile;
    outputFile.open(outputFileName);
    for(int counter = 0; counter < listSize; counter++){
        outputFile <<copy[counter]<<endl;
    }
    outputFile.close();
}

void SortingCompetition::resize(char **&oldArr, int size){
    //resizes char array
    char** temp = new char*[size+1000];
    for(int counter = 0; counter < size; counter++)
        temp[counter] = oldArr[counter];
    delete[] oldArr;
    oldArr = temp;
}

void SortingCompetition::addWord(char *&word, int wordNum){
    //adds word to char array
    wordList[wordNum] = new char[strlen(word)+1];
    strcpy(wordList[wordNum],word);
    wordList[wordNum][strlen(word)] = '\0';
}
