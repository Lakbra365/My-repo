#pragma once

#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include "SDL.h"
#include "SDL_ttf.h"



using namespace std;

class VIZ
{
private:
    SDL_Window* win;
    SDL_Renderer* renderer;

protected:
    double xLimit;
    double yLimit;
    double standardStart = 100;

public:
    VIZ();
    void drawText(double posX, double posY, string text);
    void drawRect(double posY, double width, double posX = 100, double height = 10);
};

class Plot: public VIZ
{
private:
    vector<double> yData;
    double minVal;
    double maxVal;
public:
    Plot(vector<double> Data);
    void drawPlot();
    void getMinMax();
    void drawBars();
    void drawEverything();
};

class DataManager
{
private:
    vector<vector<string>> generalData;
public:
    void parseSpecificData(regex regexP, vector<double>& specificData);
    void parseCSVData(ifstream& infile);
};


class TeamsData: public DataManager
{
private:
    string labels;
    vector<double> xData;
public:
    TeamsData(regex command);
    
};