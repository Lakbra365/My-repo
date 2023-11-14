#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

void parseCSVData(ifstream& infile, vector<vector<string>>& generalData)
{
    string line;
    while (getline(infile,line,'\n'))
    {
        vector<string> row;
        stringstream lineStream(line);
        string value;

        while (getline(lineStream, value, ','))
        {
            row.push_back(value);
        }
        generalData.push_back(row);
    }
}
