#include "DataFuncs.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>



#define WIDTH 1366
#define HEIGHT 803


using namespace std;

void DataManager :: parseCSVData(ifstream& infile) //Gets a csv file and turns it into a 2D list
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


void DataManager::parseSpecificData(regex regexP, vector<double>& specificData) //Makes a list of values based on a regex condition of a 2D list
{
    int indexDesired = -1;

    //remove after test
    ifstream infile;
    infile.open("csvText.txt");
    parseCSVData(infile);
    //end remove

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

TeamsData::TeamsData(regex command)
{
    parseSpecificData(command, xData);
}

VIZ::VIZ()
{
    // returns zero on success else non-zero
    xLimit = WIDTH - 200;
    yLimit = HEIGHT - 200;

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
    TTF_Font* font = TTF_OpenFont("C:/Users/zombi/Documents/My folders/Classes/3 semester/AERSP 424/Homework2/My-repo/FINAL PROJECT/Project1/OpenSans_SemiCondensed-Regular.ttf", 16);
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

    // Free the surface
    SDL_FreeSurface(textSurface);

    // Render the text texture to the screen
    SDL_Rect textRect = { posX, posY, textSurface->w, textSurface->h }; // Position the text on the screen
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Clean up font resources
    TTF_CloseFont(font);
}


Plot::Plot(vector<double> data) :VIZ()
{
    yData = data;
    drawEverything();
}

void Plot::getMinMax() //Gets min and max values of the yData set
{
    minVal = yData[0];
    maxVal = yData[0];
    for (double element : yData)
    {
        if (maxVal < element)
        {
            maxVal = element;
        }
        else if (minVal > element)
        {
            minVal = element;
        }
    }
    cout << "min: " << minVal << endl;
    cout << "max: " << maxVal << endl;
}

void Plot::drawPlot() //Draws the base plot for the data
{
    const double numberTicks = (yLimit / 50); 
    double width = 10;
    double tickX = standardStart - width;
    double tickY = standardStart;

    drawRect(standardStart, 10, standardStart, yLimit); //Axes
    drawRect(standardStart + yLimit, xLimit, standardStart, 10);

    for (int i = 0; i < numberTicks; i++) // Axis Y ticks & numbers
    {
        string numberLabel = to_string(int(maxVal - ((maxVal / numberTicks) * i)));
        drawRect(tickY, width, tickX, 1);
        drawText(tickX - 20, tickY -12, numberLabel);
        tickY += yLimit / numberTicks;
    }
}

void Plot::drawBars()//Draws the bars for each given data point
{
    const double conversionRate = yLimit / maxVal; //Proportionality constant between height and values
    const double barWidth = 20;
    const double barSeparation = (xLimit - (barWidth*yData.size()))/yData.size();
    

    for (int i = 0; i < yData.size(); i++) //Bars
    {
        double xPos = standardStart + (barWidth*i) +(barSeparation* (i+1));
        double height = yData[i] * conversionRate;
        double yPos = HEIGHT - standardStart - height;

        drawRect(yPos, barWidth, xPos, height);
    }
}

void Plot::drawEverything() //Encapsulates all plot necessary plot functions into a single organized function
{
    getMinMax();
    drawPlot();
    drawBars();
}