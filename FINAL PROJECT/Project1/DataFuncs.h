#pragma once

#include <regex>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class DataManager
{
private:
public:
    void parseSpecificData(regex regexP, vector<int>& specificData);
};

class structure
{
private:
    string buildingBlock;
public:
    structure(string type);
};

class PlotDrawing
{

};
class PlotData
{
private:
    vector<double> xData, yData;
public:
    PlotData(vector<double> xData, vector<double> yData);
};