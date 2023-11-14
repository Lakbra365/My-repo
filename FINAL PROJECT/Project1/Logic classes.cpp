#include "DataFuncs.h"
#include <iostream>
#include <sstream>

using namespace std;

void parseCSVData(ifstream& infile, vector<vector<string>>& generalData) //Gets a csv file and turns it into a 2D list
{
    string line;
    while (getline(infile, line, '\n')) //Makes each line a part of a vector
    {
        vector<string> row;
        stringstream lineStream(line);
        string value;

        while (getline(lineStream, value, ','))//Makes each value separated by a comma a part of a vector
        {
            row.push_back(value);
        }
        generalData.push_back(row);
    }
}

structure::structure(string type)
{
    buildingBlock = type;
}

void DataManager::parseSpecificData(regex regexP, vector<int>& specificData) //Makes a list of values based on a regex condition of a 2D list
{
    int indexDesired = -1;

    ifstream infile;
    infile.open("csvText.txt");
    vector<vector<string>> generalData;
    parseCSVData(infile, generalData);

    for (int i = 0; i < generalData[0].size(); i++)
    {
        if (regex_match(generalData[0][i], regexP)) //checks index where the regex pattern is found
        {
            indexDesired = i;
            break;
        }
    }

    for (int i = 1; i < generalData.size(); i++) //stores all values from 2D list that belong to the sotred index in a list 
    {
        specificData.push_back(stoi(generalData[i][indexDesired]));
    }
}

PlotData::PlotData(vector<double> xData, vector<double> yData)
{
    this->xData = xData;
    this->yData = yData;
}