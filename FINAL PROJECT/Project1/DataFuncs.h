#pragma once

#include <regex>
#include <string>
#include <vector>
#include<map>
#include <fstream>
#include "SDL.h"
#include "SDL_ttf.h"



using namespace std;

struct Instructions // Struct contains the initial set of instructions shown at the instant program is ran for the user 
{
    
    Instructions(string& type);
    void dataChoose();
    void dataChoose(char(&desiredData)[2], bool& quit);
    void dataChoose(char(&desiredData)[3], bool& quit);
    void callInstructions();
    void verifyValidity(char character, bool& quit);
};
class VIZ //This class handles content related to the raw initial window and raw text seen after running the code
{
private:
    SDL_Window* win;
    SDL_Renderer* renderer;

public:
    VIZ();
    void drawText(double posX, double posY, string text);
    void drawRect(double posY, double width, double posX = 100, double height = 10);
};

class Plot: public VIZ //Class handles all content related to the drawing of a Plot with a given set of data
{
private:
    double xLimit, yLimit, minVal, maxVal;
    const double standardStart = 100; // top-left location of plot is in (standardStart,standardStart) coordinates
    map<string, double> yData;

public:
    Plot(map<string,double> Data);
    void drawPlot();
    void drawYticks();
    void drawXticks(double xPos, string abrv);
    void getMinMax();
    void drawBars();
    void drawEverything();
};

class DataManager //Class handles the parsing of raw data into, useful and readable data for the computer
{
private:
    vector<vector<string>> generalData;
    vector<vector<string>> abreviations;
protected:
    map<string, double> xData;
public:
    DataManager(regex command);
    void parseSpecificData(regex regexP, map<string,double>& specificData);
    void parseCSVData(ifstream& infile, vector<vector<string>>& generalData);
};

class PlotData : public DataManager
{
public:
    PlotData(regex command);
};

class StatisticsOp : public DataManager
{
public:
    StatisticsOp(string operation, regex command);
    double mean();
    void std();
    void median();
};

