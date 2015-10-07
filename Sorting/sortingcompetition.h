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

    string largeFile;
    vector<string> wordList;
    vector<string> sorter;

};


#endif // SORTINGCOMPETITION_H
