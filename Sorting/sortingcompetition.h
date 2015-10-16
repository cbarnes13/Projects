#ifndef SORTINGCOMPETITION_H
#define SORTINGCOMPETITION_H
#include <stdio.h>
#include <string>
using namespace std;


class SortingCompetition
{
public:

    SortingCompetition(const string& inputFileName);

    void setFileName(const string& inputFileName);

    bool readData();

    bool prepareData();

    void sortData();

    void outputData(const string& outputFileName);

private:
    //dstr
    ~SortingCompetition();

    //variablies
    string fileName;
    char** wordList;
    char** copy;
    char* buffer;
    int listSize;
    void resize(char**& oldArr, int size);
    void addWord(char*& word, int wordNum);

    //selectionsort
    void selectionSort();

    //bubblesort
    void bubbleSort();

    //quicksort using first pivot
    void quickSortPivotFirst(int l, int h);
    int partitionPivotFisrt(int low, int high);

    //quicksort using last pivot
    void quickSortPivotLast(int l, int h);
    int partitionPivotLast(int low, int high);

    //quicksort with median of 3
    void quickSortMedOfThree(int l, int h);
    int partitionMedOfThree(int low, int high);
    int medianOfThree(int firstVal, int lastVal);

    //quicksort median of 5
    void quickSortMedOfFive(int l, int h);
    int partitionMedOfFive(int low, int high);
    int medianOfFive(int firstVal, int lastVal);

    //mergesort testers
    //void mergeSort(int l, int h);
    //void merge(int left, int middle, int right);
    //void merge(char** &charArr, int lhs, int mid,int rhs);
    //void mergeSort(char** &charArr, int lhs, int rhs);
};


#endif // SORTINGCOMPETITION_H
