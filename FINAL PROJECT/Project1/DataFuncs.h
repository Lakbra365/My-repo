#pragma once

#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include "SDL.h"

using namespace std;

class VIZ
{
    SDL_Window* win;
    SDL_Renderer* renderer;

public:
    VIZ();

    void drawRect(double posY, double width, double posX = 40, double height = 10);
};

class DataManager
{
private:
    vector<vector<string>> generalData;
public:
    void parseSpecificData(regex regexP, vector<double>& specificData);
    void parseCSVData(ifstream& infile);
};


class Plot: public DataManager
{
private:
    string labels;
    vector<double> xData;
public:
    Plot(regex command);
    
};