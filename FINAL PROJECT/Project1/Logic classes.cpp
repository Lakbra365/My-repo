#include "DataFuncs.h"
#include <iostream>
#include <sstream>

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

Plot::Plot(regex command)
{
    parseSpecificData(command, xData);
}

VIZ::VIZ()
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    win = SDL_CreateWindow("Football Stats", // creates a window
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderClear(renderer);

    //SDL_RenderPresent(renderer);
}

void VIZ::drawRect(double posY, double width, double posX, double height)
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