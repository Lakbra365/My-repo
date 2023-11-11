#include <iostream>
#include <SDL.h>
#include "Functions.h"
#include "HW2_Visualizer.h"


using namespace std;

int main(int argc, char** argv)
{
	HW2_VIZ viz;
	double timeStep = 25;
	vector<pair<Plane*, double>> planesInstantiated
	{
		{new Airliner("AA", "PHL", "SCE"), 470},
		{new Airliner("UA", "ORD", "SCE"),515},
		{new Airliner("UA", "EWR", "SCE"),480},
		{new Airliner("AA", "ORD", "SCE"),500},
		{new GeneralAviation("PHL", "SCE"),140},
		{new GeneralAviation("EWR", "SCE"),160},
		{new GeneralAviation("ORD", "SCE"),180}
	};
	ATC atc;

	for (auto element : planesInstantiated)
	{
		element.first->setVel(element.second);
		element.first->setLoiter(20);
		element.first->time_on_ground();
		atc.register_plane(element.first);
	}


	while (true)
	{
		double planeNum = 1;
		for (auto element : planesInstantiated)
		{
			element.first->operate(timeStep);
			atc.control_traffic();
			viz.visualize_plane(element.first->planeType,element.first->getOrigin(),element.first->getDestination(),element.first->getPos() );
			viz.update(timeStep);
			cout << "Plane" << planeNum << " pos: " << element.first->getPos() << endl;
			planeNum += 1;
		}

	}
	return 0;
}