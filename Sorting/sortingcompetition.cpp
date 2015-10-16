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

SortingCompetition::~SortingCompetition(){
    for(int i = 0; i < listSize; i++){
        delete[] copy[i];
        delete[] wordList[i];
    }
    delete[] copy;
    delete[] wordList;
    delete[] buffer;
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
    //mergeSort(copy, 0, listSize-1);
    quickSortPivotLast(0, listSize-1);
    //selectionSort();
    //bubbleSort();
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
                if(strcmp(firstTemp,secondTemp) < 0){
                    //switches words
                    copy[firstVal] = secondTemp;
                    copy[secondVal] = firstTemp;
                }
            }
        }
    }
}

void SortingCompetition::quickSortPivotLast(int l, int h){

    //tests to see if lowest index is less than highest
    if(l < h){
        //sends indexs to partition and returns the pivot index
        int p = partitionPivotLast(l, h);
        //recursive call to quicksort for both sides of pivot
        quickSortPivotLast(l, p-1);
        quickSortPivotLast(p+1, h);
    }
}

int SortingCompetition::partitionPivotLast(int low, int high){
    char* pivot = copy[high];
    //varibles that will be used
    char* firstTemp;

    int left = low-1;

    for(int right = low; right < high; right++){
        if(strlen(copy[right]) < strlen(pivot)){
            left++;
            firstTemp = copy[left];
            copy[left] = copy[right];
            copy[right] = firstTemp;
        }
        if(strlen(copy[right]) == strlen(pivot)){
            if(strcmp(copy[right],pivot) < 0){
                left++;
                firstTemp = copy[left];
                copy[left] = copy[right];
                copy[right] = firstTemp;
            }
        }
    }
    firstTemp = copy[left+1];
    copy[left+1] = copy[high];
    copy[high] = firstTemp;

    return left+1;
}

void SortingCompetition::quickSortMedOfThree(int l, int h){
    //tests to see if lowest index is less than highest
    if(l < h){
        //sends indexs to partition and returns the pivot index
        int p = partitionMedOfThree(l, h);
        //recursive call to quicksort for both sides of pivot
        quickSortPivotLast(l, p-1);
        quickSortPivotLast(p+1, h);
    }
}

int SortingCompetition::partitionMedOfThree(int low, int high){
    int pivotIndex = medianOfThree(low, high);
    char* temp;
    char* pivot = copy[pivotIndex];
    copy[pivotIndex] = copy[high];
    copy[high] = pivot;

    int j = low;
    int k = high-1;

    while(j < k){
        while(strlen(copy[j]) < strlen(pivot))
            j++;
        while(strlen(copy[j]) == strlen(pivot)){
            if(strcmp(copy[j], pivot) <= 0)
                j++;
        }
        while(strlen(copy[k]) > strlen(pivot))
            k--;
        while(strlen(copy[k]) == strlen(pivot)){
            if(strcmp(copy[k], pivot) >= 0)
                k--;
        }
        if(j < k){
            temp = copy[j];
            copy[j] = copy[k];
            copy[k] = temp;
        }
    }
    copy[high] = copy[k];
    copy[k] = pivot;
    return k;
}

int SortingCompetition::medianOfThree(int firstVal, int lastVal){
    char* tempArry[3];
    int tempInt[3];
    if(lastVal-firstVal >= 2){
        int temp;
        tempInt[0] = firstVal;
        tempInt[1] = firstVal+(lastVal-firstVal)/2;
        tempInt[2] = lastVal;
        tempArry[0] = copy[tempInt[0]];
        tempArry[1] = copy[tempInt[1]];
        tempArry[2] = copy[tempInt[2]];
        for(int i = 0; i < 1; i++){
            for(int j = 1; j < 2; j++){
                if(strlen(tempArry[i]) < strlen(tempArry[j])){
                    temp = tempInt[i];
                    tempInt[i] = tempInt[j];
                    tempInt[j] = temp;
                }
                if(strlen(tempArry[i]) < strlen(tempArry[j])){
                    if(strcmp(tempArry[i],tempArry[j]) < 0){
                        temp = tempInt[i];
                        tempInt[i] = tempInt[j];
                        tempInt[j] = temp;
                    }
                }
            }
        }
        return tempInt[1];
    } else{
        return lastVal;
    }
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

/*void SortingCompetition::mergeSort(int l, int h){
    if(l < h){
        int middle = l+(h-l)/2;
        mergeSort(l, middle);
        mergeSort(middle+1, h);
        merge(l ,middle, h);
    }
}

void SortingCompetition::merge(int left, int middle, int right){
    int i;
    int j;
    int k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    char** tempL = new char*[n1];
    char** tempR = new char* [n2];

    for(i = 0; i < n1; i++)
        tempL[i] = copy[left+i];
    for(j = 0; j < n2; j++)
        tempR[j] = copy[middle + 1 + j];

    i = 0;
    j = 0;
    k = 1;

    while(i < n1 && j < n2){
        if(strlen(tempL[i]) < strlen(tempR[j])){
            copy[k] = tempL[i];
            i++;
        }
        if(strlen(tempL[i]) > strlen(tempR[j])){
            copy[k] = tempR[j];
            j++;
        }
        if(strlen(tempL[i]) == strlen(tempR[j])){
            if(strcmp(tempL[i], tempR[j]) < 0){
                copy[k] = tempL[i];
                i++;
            } else{
                copy[k] = tempR[j];
                j++;
            }
        }
        k++;
    }
    while(i < n1){
        copy[k] = tempL[i];
        i++;
        k++;
    }
    while(j < n2){
        copy[k] = tempR[j];
        j++;
        k++;
    }
}*/
