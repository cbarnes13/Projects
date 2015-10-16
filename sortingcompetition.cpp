#include "sortingcompetition.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <string.h>
#include <iomanip>

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

SortingCompetition::SortingCompetition(const SortingCompetition &arg){
    listSize = arg.listSize;
    buffer = new char[100];
    for(int i = 0; i < 100; i++)
    {
        buffer[i] = arg.buffer[i];
    }
    wordList = new char*[listSize+1000];
    for(int i = 0; i < listSize; i++)
    {
        wordList[i] = arg.wordList[i];
    }
    copy = new char*[listSize+1000];
    for(int i = 0; i < listSize; i++)
    {
        copy[i] = arg.copy[i];
    }
}

SortingCompetition& SortingCompetition::operator=(const SortingCompetition &arg){
    if(this == &arg){
        return *this;
    }
    listSize = arg.listSize;
    for(int i = 0; i < 100; i++)
    {
        buffer[i] = arg.buffer[i];
    }
    for(int i = 0; i < listSize; i++)
    {
        wordList[i] = arg.wordList[i];
    }
    for(int i = 0; i < listSize; i++)
    {
        copy[i] = arg.copy[i];
    }
    return *this;
}

SortingCompetition::~SortingCompetition()
{
    //delete varibles
    delete[] buffer;
    for(int i = 0; i < listSize; i++){
        delete[] wordList[i];
        delete[] copy[i];
    }
    delete[] wordList;
    delete[] copy;

}

void SortingCompetition::setFileName(const string& inputFileName)
{
    //set file name
    fileName = inputFileName;

}

bool SortingCompetition::readData()
{
    //opens file
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr<< "File could not be opened"<<endl;
        exit(EXIT_FAILURE);
    }
    //reads data and sends it to addword
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

void SortingCompetition::addWord(char *&word, int wordNum)
{
    //adds word to char array
    wordList[wordNum] = new char[strlen(word)+1];
    strcpy(wordList[wordNum],word);
    wordList[wordNum][strlen(word)] = '\0';
}

void SortingCompetition::resize(char **&oldArr, int size)
{
    //resizes char array
    char** temp = new char*[size+1000];
    for(int counter = 0; counter < size; counter++)
        temp[counter] = oldArr[counter];
    delete[] oldArr;
    oldArr = temp;
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
    //uncomment which sort method you would
    //like to use

    quickSortPivotLast(0, listSize-1);
    //quickSortMedOfFive(0, listSize-1);
    //quickSortMedOfThree(0, listSize-1);
    //quickSortPivotFirst(0, listSize-1);
    //selectionSort();
    //bubbleSort();
}

void SortingCompetition:: selectionSort()
{
    //create variables
    char* temp;
    char* firstTemp;
    char* secondTemp;
    int min_index = 0;

    for ( int i = 0; i < (listSize - 1); i++)
    {
        //set min_index
        min_index = i;

        for ( int j = (i+1); j < listSize; j++)
        {
            //sets temps
            firstTemp = copy[min_index];
            secondTemp = copy[j];
            //compares length
            if(strlen(firstTemp) > strlen(secondTemp)){
                //sets min_index
                min_index = j;
            }
            //determines alphabetical order
            else if (strlen(firstTemp) == strlen(secondTemp) && strcmp(copy[j] , copy[min_index]) < 0 )
            {
                //set min_index
                min_index = j;
            }
        }
        //tests to see if min_index is no equal to i
        if (min_index != i)
        {
            //swap values
            temp = copy[i];
            copy[i] = copy[min_index];
            copy[min_index] = temp;
        }

    }

}

void SortingCompetition::bubbleSort()
{
    //creates two temp variables
    char* temp;
    //bubble sort method
    for(int firstVal = 1; firstVal < listSize; firstVal++)
    {
        for(int secondVal = 0; secondVal < listSize-1; secondVal++)
        {
            //compares length to see if the first word is longer
            //than the second
            if(strlen(copy[firstVal]) < strlen(copy[secondVal]))
            {
                //switches words
                temp = copy[firstVal];
                copy[firstVal] = copy[secondVal];
                copy[secondVal] = temp;
            }
            //test to see if the words have same length
            if(strlen(copy[firstVal]) == strlen(copy[secondVal]))
            {
                //test for aphabetical order
                if(strcmp(copy[firstVal],copy[secondVal]) < 0)
                {
                    //switches words
                    temp = copy[firstVal];
                    copy[firstVal] = copy[secondVal];
                    copy[secondVal] = temp;
                }
            }
        }
    }
}
void SortingCompetition::quickSortPivotFirst(int l, int h)
{

    //tests to see if lowest index is less than highest
    if(l < h){
        //sends indexs to partition and returns the pivot index
        int p = partitionPivotFisrt(l, h);
        //recursive call to quicksort for both sides of pivot
        quickSortPivotFirst(l, p-1);
        quickSortPivotFirst(p+1, h);
    }
}

int SortingCompetition::partitionPivotFisrt(int low, int high)
{
    //sets pivot
    char* pivot = copy[low];
    copy[low] = copy[high];
    copy[high] = pivot;
    //creates a temp char star
    char* firstTemp;
    //index of smaller element
    int left = low-1;

    //for loop starting from the left most element
    for(int right = low; right < high; right++)
    {
        //tests if the length is smaller than the pivot's
        if(strlen(copy[right]) < strlen(pivot))
        {
            //adds to left index
            left++;
            //swaps words
            firstTemp = copy[left];
            copy[left] = copy[right];
            copy[right] = firstTemp;
        }
        //test for length equality
        if(strlen(copy[right]) == strlen(pivot))
        {
            //tests for alphabetical order
            if(strcmp(copy[right],pivot) < 0)
            {
                //adds to left index
                left++;
                //swaps words
                firstTemp = copy[left];
                copy[left] = copy[right];
                copy[right] = firstTemp;
            }
        }
    }
    //puts pivot back in place
    firstTemp = copy[left+1];
    copy[left+1] = copy[high];
    copy[high] = firstTemp;

    //returns index
    return left+1;

    //http://geeksquiz.com/quik-sort/
}

void SortingCompetition::quickSortPivotLast(int l, int h)
{

    //tests to see if lowest index is less than highest
    if(l < h){
        //sends indexs to partition and returns the pivot index
        int p = partitionPivotLast(l, h);
        //recursive call to quicksort for both sides of pivot
        quickSortPivotLast(l, p-1);
        quickSortPivotLast(p+1, h);
    }
}

int SortingCompetition::partitionPivotLast(int low, int high)
{
    //sets pivot
    char* pivot = copy[high];
    //creates a temp char star
    char* firstTemp;
    //index of smaller element
    int left = low-1;

    //for loop starting from the left most element
    for(int right = low; right < high; right++)
    {
        //tests if the length is smaller than the pivot's
        if(strlen(copy[right]) < strlen(pivot))
        {
            //adds to left index
            left++;
            //swaps words
            firstTemp = copy[left];
            copy[left] = copy[right];
            copy[right] = firstTemp;
        }
        //test for length equality
        if(strlen(copy[right]) == strlen(pivot))
        {
            //tests for alphabetical order
            if(strcmp(copy[right],pivot) < 0)
            {
                //adds to left index
                left++;
                //swaps words
                firstTemp = copy[left];
                copy[left] = copy[right];
                copy[right] = firstTemp;
            }
        }
    }
    //puts pivot back in place
    firstTemp = copy[left+1];
    copy[left+1] = copy[high];
    copy[high] = firstTemp;

    //returns index
    return left+1;

    //http://geeksquiz.com/quik-sort/
}

void SortingCompetition::quickSortMedOfThree(int l, int h)
{
    //tests to see if lowest index is less than highest
    if(l < h){
        //sends indexs to partition and returns the pivot index
        int p = partitionMedOfThree(l, h);
        //recursive call to quicksort for both sides of pivot
        quickSortPivotLast(l, p-1);
        quickSortPivotLast(p+1, h);
    }
}

int SortingCompetition::partitionMedOfThree(int low, int high)
{
    //gets pivot index from medianOfThree function
    int pivotIndex = medianOfThree(low, high);
    //creates a temp char star
    char* firstTemp;
    //sets pivot
    char* pivot = copy[pivotIndex];
    //index of smaller element
    int left = low-1;

    //for loop starting from the left most element
    for(int right = low; right < high; right++)
    {
        //tests if the length is smaller than the pivot's
        if(strlen(copy[right]) < strlen(pivot))
        {
            //adds to left index
            left++;
            //swaps words
            firstTemp = copy[left];
            copy[left] = copy[right];
            copy[right] = firstTemp;
        }
        //test for length equality
        if(strlen(copy[right]) == strlen(pivot))
        {
            //tests for alphabetical order
            if(strcmp(copy[right],pivot) < 0)
            {
                //adds to left index
                left++;
                //swaps words
                firstTemp = copy[left];
                copy[left] = copy[right];
                copy[right] = firstTemp;
            }
        }
    }
    //puts pivot back in place
    firstTemp = copy[left+1];
    copy[left+1] = copy[high];
    copy[high] = firstTemp;

    //returns index
    return left+1;

    //http://geeksquiz.com/quik-sort/
}

int SortingCompetition::medianOfThree(int firstVal, int lastVal)
{
    //makes sure there are enough variables
    if(lastVal-firstVal >= 2)
    {
        //creates temp arrays and variables
        char* tempArry[3];
        int tempInt[3];
        int temp;
        //initalize those arrays
        tempInt[0] = firstVal;
        tempInt[1] = firstVal+(lastVal-firstVal)/2;
        tempInt[2] = lastVal;
        tempArry[0] = copy[tempInt[0]];
        tempArry[1] = copy[tempInt[1]];
        tempArry[2] = copy[tempInt[2]];
        //bubble sort for loop to sort variables
        for(int i = 0; i < 1; i++)
        {
            for(int j = 1; j < 2; j++)
            {
                if(strlen(tempArry[i]) < strlen(tempArry[j]))
                {
                    temp = tempInt[i];
                    tempInt[i] = tempInt[j];
                    tempInt[j] = temp;
                }
                if(strlen(tempArry[i]) < strlen(tempArry[j]))
                {
                    if(strcmp(tempArry[i],tempArry[j]) < 0)
                    {
                        temp = tempInt[i];
                        tempInt[i] = tempInt[j];
                        tempInt[j] = temp;
                    }
                }
            }
        }
        //return middle val
        return tempInt[1];
    } else{
        //if size is too small return lastVal
        return lastVal;
    }
}

void SortingCompetition::quickSortMedOfFive(int l, int h)
{
    //tests to see if lowest index is less than highest
    if(l < h){
        //sends indexs to partition and returns the pivot index
        int p = partitionMedOfFive(l, h);
        //recursive call to quicksort for both sides of pivot
        quickSortPivotLast(l, p-1);
        quickSortPivotLast(p+1, h);
    }
}

int SortingCompetition::partitionMedOfFive(int low, int high)
{
    //gets pivot index from medianOfThree function
    int pivotIndex = medianOfFive(low, high);
    //creates a temp char star
    char* firstTemp;
    //sets pivot
    char* pivot = copy[pivotIndex];
    //index of smaller element
    int left = low-1;

    //for loop starting from the left most element
    for(int right = low; right < high; right++)
    {
        //tests if the length is smaller than the pivot's
        if(strlen(copy[right]) < strlen(pivot))
        {
            //adds to left index
            left++;
            //swaps words
            firstTemp = copy[left];
            copy[left] = copy[right];
            copy[right] = firstTemp;
        }
        //test for length equality
        if(strlen(copy[right]) == strlen(pivot))
        {
            //tests for alphabetical order
            if(strcmp(copy[right],pivot) < 0)
            {
                //adds to left index
                left++;
                //swaps words
                firstTemp = copy[left];
                copy[left] = copy[right];
                copy[right] = firstTemp;
            }
        }
    }
    //puts pivot back in place
    firstTemp = copy[left+1];
    copy[left+1] = copy[high];
    copy[high] = firstTemp;

    //returns index
    return left+1;

    //http://geeksquiz.com/quik-sort/
}

int SortingCompetition::medianOfFive(int firstVal, int lastVal)
{
    //makes sure there are enough variables
    if(lastVal-firstVal >= 4)
    {
        //creates temp arrays and variables
        char* tempArry[5];
        int tempInt[5];
        int temp;
        //initalize those arrays
        tempInt[0] = firstVal;
        tempInt[2] = firstVal+(lastVal-firstVal)/2;
        tempInt[4] = lastVal;
        tempInt[1] = tempInt[0]+(tempInt[2]-tempInt[0])/2;
        tempInt[3] = tempInt[2]+(tempInt[4]-tempInt[2])/2;
        tempArry[0] = copy[tempInt[0]];
        tempArry[1] = copy[tempInt[1]];
        tempArry[2] = copy[tempInt[2]];
        tempArry[3] = copy[tempInt[3]];
        tempArry[4] = copy[tempInt[4]];
        //bubble sort for loop to sort variables
        for(int i = 0; i < 4; i++)
        {
            for(int j = 1; j < 5; j++)
            {
                if(strlen(tempArry[i]) < strlen(tempArry[j]))
                {
                    temp = tempInt[i];
                    tempInt[i] = tempInt[j];
                    tempInt[j] = temp;
                }
                if(strlen(tempArry[i]) < strlen(tempArry[j]))
                {
                    if(strcmp(tempArry[i],tempArry[j]) < 0)
                    {
                        temp = tempInt[i];
                        tempInt[i] = tempInt[j];
                        tempInt[j] = temp;
                    }
                }
            }
        }
        //return middle val
        return tempInt[2];
    } else{
        //if size is too small return lastVal
        return lastVal;
    }
}

void SortingCompetition::outputData(const string &outputFileName)
{
    //prints out sorted words
    ofstream outputFile;
    outputFile.open(outputFileName);
    for(int counter = 0; counter < listSize; counter++)
    {
        outputFile <<copy[counter]<<endl;
    }
    outputFile.close();
}
