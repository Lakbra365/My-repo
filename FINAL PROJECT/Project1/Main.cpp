#include "DataFuncs.h"
#include <iostream>
#include <SDL.h>


using namespace std; 
int main(int argc, char** argv)
{ 
	//Call for instructions and create a data manager out of input received
	bool quit = false;
	string inputString;
	string desiredString;
	Instructions instruct(inputString);

	//determines if user wants a statistic or a plot
	if (inputString.size() == 2)
	{
		desiredString = inputString.substr(1, 2) + "$"; //Regex formatted string
		regex pattern(desiredString);
		StatisticsOp statistic(inputString.substr(0, 1), pattern);
	}
	else
	{
		desiredString = inputString.substr(0, 1) + "$"; //Regex formatted string
		regex pattern(desiredString);
		PlotData teamsData(pattern);
	}
	
	


	//Handling of quit events for SDL
	while (!quit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				// Set the quit flag to true
				quit = true;
				TTF_Quit();
				break;
			}
		}
	}
	return 0;
}