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

    string fileName;
    char** wordList;
    char** copy;
    char* buffer;
    int listSize;
    void resize(char**& oldArr, int size);
    void addWord(char*& word, int wordNum);
    void bubbleSort();
    void quickSortPivotLast(int l, int h);
    int partitionPivotLast(int low, int high);
    void mergeSort(int l, int h);
    void merge(int left, int middle, int right);
    void selectionSort();
    void mergeSort();
};


#endif // SORTINGCOMPETITION_H
