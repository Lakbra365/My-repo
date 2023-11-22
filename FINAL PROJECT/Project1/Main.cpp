#include "DataFuncs.h"
#include <iostream>
#include <SDL.h>


using namespace std; 
int main(int argc, char** argv)
{
	DataManager test;
	regex pattern("G$");
	vector<double> specificData;
	test.parseSpecificData(pattern, specificData);
	cout << "[";
	for (const auto& row : specificData)
	{
		cout << row << ", ";
	}
	cout << "]"<< endl;
	// Parsed data code ends here

	Plot plot(specificData);
	//code for drawing plot ends here
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				// Set the quit flag to true
				quit = true;
				break;
			}
		}
	}
	return 0;
}