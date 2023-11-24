#include "DataFuncs.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>


#define WIDTH 1366
#define HEIGHT 803

using namespace std;

Instructions::Instructions(string& type)
{
    bool quit = false;

    while (!quit) {
        callInstructions();
        cin >> type;

        if (type.size() == 1) {
            char desiredData[2];
            strcpy_s(desiredData, type.size() + 1, type.c_str());
            dataChoose(desiredData, quit);
        }
        else if (type.size() == 2) {
            char desiredData[3];
            strcpy_s(desiredData, type.size() + 1, type.c_str());
            dataChoose(desiredData, quit);
        }
        else {
            dataChoose();
        }
    }

}
void Instructions::dataChoose(char (&desiredData)[2], bool& quit) 
{
    verifyValidity(desiredData[0], quit);
}

void Instructions::dataChoose(char(&desiredData)[3], bool& quit) 
{
    switch (desiredData[0])
    {
    case 'a':
    case 'm':
    case 's':
        verifyValidity(desiredData[1], quit);
        break;
    default:
        cout << "Invalid choice, Please choose a valid character" << endl;
    }
        
    
}

void Instructions::dataChoose()
{
    // Handle character arrays of any length (N >= 3)
    cout << "Please enter a valid character array" << endl;
    
}


void Instructions::callInstructions()
{
    cout << " Type the data you want to see\n"
        << "M: for # of played matches by teams\n"
        << "P: for # of points by teams\n"
        << "G: for # of goals by teams\n"
        << "W: for # of wins by teams\n"
        << "L: for # of losses by teams\n"
        << "D: for # of draws by teams\n"
        << "if you want to see average, median or standard deviation \n"
        << "type a, m, or s respectively behind that data you want\n";
}

void Instructions::verifyValidity(char character, bool& quit)
{
    switch (character)
    {
    case 'M':
    case 'D':
    case 'G':
    case 'W':
    case 'L':
    case 'P':
        quit = true;
        break;
    default:
        cout << "Invalid choice, Please choose a valid character" << endl;
    }
}
// ###################### VIZ ############################## //
VIZ::VIZ() //Constructor initializes SDL and SDL_TTF for following functions. 
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    if (TTF_Init() < 0)
    {
        printf("error initializing SDL_ttf: %s\n", TTF_GetError());
        return;
    }

    win = SDL_CreateWindow("Football Stats", // creates a window
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void VIZ::drawRect(double posY, double width, double posX, double height) //Creates a rectangle of set color in the visualizer
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_Rect rect;
    rect.x = posX;
    rect.y = posY;
    rect.w = width;
    rect.h = height;

    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void VIZ::drawText(double posX, double posY, string text) //All necessary code for rendering a line of text in SDL window
{
    //Font file location
    TTF_Font* font = TTF_OpenFont("OpenSans_SemiCondensed-Regular.ttf", 16);
    if (!font)
    {
        printf("error loading font: %s\n", TTF_GetError());
        TTF_Quit();
        return;
    }
    SDL_Color textColor = { 0,0,0,255 };

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor); // Render the desired text
    if (!textSurface)
    {
        printf("error rendering text: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        TTF_Quit();
        return;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        TTF_Quit();
        return;
    }

    SDL_FreeSurface(textSurface);

    // Render the text texture to the screen
    SDL_Rect textRect = { posX, posY, textSurface->w, textSurface->h }; // Position the text on the screen
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_RenderPresent(renderer);
    TTF_CloseFont(font);
}

// ###################### PLOT ############################## //

Plot::Plot(map<string, double> data) :VIZ()
{
    //Size Limits for the plot
    xLimit = WIDTH - 200;
    yLimit = HEIGHT - 200;
    yData = data;
    drawEverything();
}

void Plot::getMinMax() //Gets min and max values of the yData set
{
    minVal = 10000;
    maxVal = -10000;
    for (auto element : yData)
    {
        if (maxVal < element.second)
        {
            maxVal = element.second;
        }
        else if (minVal > element.second)
        {
            minVal = element.second;
        }
    }
}

void Plot::drawPlot() //Draws the base plot for the data
{
    drawRect(standardStart, 10, standardStart, yLimit); //Axis Y
    drawRect(standardStart + yLimit, xLimit, standardStart, 10); //Axis X
    drawYticks();
}

void Plot::drawYticks() //Draws Y Axis labels with its number
{
    const double numberTicks = (yLimit / 75);
    const double width = 10;
    const double tickX = standardStart - width; 
    double tickY = standardStart;

    for (int i = 0; i < numberTicks; i++) 
    {
        double initValue = (maxVal - ((maxVal / numberTicks) * i));
        int wholePart = initValue;
        int decimalPart = int(initValue * 10) - wholePart * 10;
        string dispNum = to_string(wholePart) + "." + to_string(decimalPart);

        drawRect(tickY, width, tickX, 1); //Ticks
        drawText(tickX - 30, tickY - 12, dispNum); //Numbers
        tickY += yLimit / numberTicks;
    }
}

void Plot::drawXticks(double xPos, string abrv) // Draws X axis Ticks and labels
{
    const double tickY = standardStart + yLimit + 10;

    drawRect(tickY, 1, xPos, 10);
    drawText(xPos - 9, tickY + 10, abrv);
}

void Plot::drawBars()//Draws the bars for each given data point
{
    const double conversionRate = yLimit / maxVal; //Proportionality constant between height and values
    const double barWidth = 20;
    const double barSeparation = (xLimit - (barWidth * yData.size())) / yData.size();

    int i = 0;
    for (auto element : yData) //Bars drawing
    {
        double xPos = standardStart + (barWidth * i) + (barSeparation * (i + 1));
        double height = element.second * conversionRate;
        double yPos = HEIGHT - standardStart - height;

        drawRect(yPos, barWidth, xPos, height);
        drawXticks(xPos + (barWidth / 2), element.first);
        i++;
    }
}

void Plot::drawEverything() //Encapsulates all plot necessary plot functions into a single organized function
{
    getMinMax();
    drawPlot();
    drawBars();
}
// ###################### DATA MANAGER ############################## //
DataManager::DataManager(regex command) //Parses data according to an user input, and plots it
{
    parseSpecificData(command, xData);
}

void DataManager :: parseCSVData(ifstream& infile,vector<vector<string>>& generalData) //Gets a csv file and turns it into a 2D list
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


void DataManager::parseSpecificData(regex regexP, map<string, double>& specificData) //Makes a map of values based on a regex condition of a 2D list
{
    int indexDesired = -1;
    ifstream infile,abrv;

    infile.open("csvText.txt"); //Raw data of teams wins, loses, goals, etc
    abrv.open("abreviations.txt"); //Raw data relating teams to its respective abreviation for future plot Xlabels
    parseCSVData(infile,generalData);
    parseCSVData(abrv,abreviations);
    
    for (int i = 0; i < generalData[0].size(); i++)
    {
        if (regex_match(generalData[0][i], regexP)) //checks index where the regex pattern is found
        {
            indexDesired = i;
            break;
        }
    }
    for (int i = 1; i < generalData.size(); i++) //stores all values from 2D list that belong to the sorted index to a map of the form {Team abreviation(key) : Team score (value)}
    {
        string abreviation;
        for (int j = 0; j < abreviations.size();j++)
        {
            if (abreviations[j][0] == generalData[i][0])
            {
                abreviation = abreviations[j][1];
                break;
            }
        }
        specificData[abreviation] = (stoi(generalData[i][indexDesired]));
    }
}

// ###################### PLOT DATA ############################## //
PlotData::PlotData(regex command) :DataManager(command) //When user wants a plot
{
    Plot plot(xData);
}

// ###################### STATISTICS OP ############################## //
StatisticsOp::StatisticsOp(string operation, regex command) : DataManager(command) //when user wants an statistic value
{
    if (operation == "a")
    {
        mean();
    }
    else if (operation == "m")
    {
        median();
    }
    else if (operation == "s")
    {
        std();
    }
    else {
        cout << "Invalid operation: " << operation << endl;
    }
}

double StatisticsOp::mean()
{
    double result = 0;
    for (auto element : xData)
    {
        result += element.second;
    }
    result /= xData.size();
    cout << "The mean is: " << result << endl;
    return result;
}

void StatisticsOp::std() //calculates standard deviation
{
    const double average = mean();
    double result = 0;

    for (auto element : xData)
    {
        result += pow(element.second - average, 2);
    }
    result /= xData.size();
    cout << "The Variance is: " << result << endl;
    cout << "The std is: " << sqrt(result) << endl;
}

void StatisticsOp::median()
{
    vector<double> values;
    int medianIndex = xData.size()/2;
    double result;

    for (auto element : xData) 
    {
        values.push_back(element.second);
    }
    sort(values.begin(), values.end()); //organizes the xData values from min to max
    
    if (xData.size() % 2 == 0)
    {
        result = (values[medianIndex] + values[medianIndex - 1])/2;
    }
    else
    {
        result = values[medianIndex];
    }
    cout << "The median is: " << result << endl;
}

