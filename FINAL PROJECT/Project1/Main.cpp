#include "DataFuncs.h"
#include <iostream>
#include <SDL.h>


using namespace std; 
int main(int argc, char** argv)
{
	char desiredData;
	Instructions instruct(desiredData);
	string desiredString = string(1,desiredData) + "$";
	regex pattern(desiredString);
	DataManager teamsData(pattern);
	bool quit = false;

	//Handling of quit events
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