#include "sortingcompetition.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

SortingCompetition:: SortingCompetition(const string& inputFileName)
{

    setFileName(inputFileName);

}

void SortingCompetition:: setFileName(const string& inputFileName)
{

    largeFile = inputFileName;

}

bool SortingCompetition:: readData()
{
    ifstream file(largeFile);

    if (!file.is_open())
    {
        cerr<< "File could not be opened"<<endl;
        exit(EXIT_FAILURE);
    }

    string token = " ";
    int tokenCounter = 0;

    while (!file.eof())
    {
        file >> token;
        wordList.push_back(token);
        token = " ";
        tokenCounter++;
    }
    if (wordList.size() == tokenCounter)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool SortingCompetition:: prepareData()
{
    if (readData() == true)
    {
        sorter.clear();
        for(int counter = 0; counter < wordList.size(); counter++)
            sorter.push_back(wordList[i]);
        return true;
    }

    else
    {
        return false;
    }

}

void SortingCompetition:: sortData()
{
    string firstTemp;
    string secondTemp;
    for(int firstVal = 0; firstVal<sorter.size()-2; firtVal++){
        for(int secondVal = 1; secondVal<sorter.size()-1; secondVal++){
            firstTemp = sorter[firstVal];
            secondTemp = sorter[secondTemp];
            if(firstTemp.length() > secondTemp.length())
                swap(sorter[firstVal],sorter[secondVal]);
            if(firstTemp.length() == secondTemp.length()){
                if(firstTemp.compare(secondTemp) > 0)
                    swap(sorter[firstVal],sorter[secondVal]);
            }
        }
    }



}
void SortingCompetition:: outputData(const string &outputFileName){
    ofstream outputFile;
    outputFile.open(outputFileName);
    for(int counter = 0; counter < sorter.size(); counter++){
        outputFile <<sorter[counter]<<endl;
    }
    outputFile.close();
}



