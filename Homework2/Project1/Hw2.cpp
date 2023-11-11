#include <iostream>
#include <SDL.h>
#include "Functions.h"
#include "HW2_Visualizer.h"


using namespace std;

int main(int argc, char** argv)
{
	HW2_VIZ viz;
	double timeStep = 10;
	vector<pair<Plane*, double>> planesInstantiated
	{
		{new Airliner("AA", "PHL", "SCE"), 470/60},
		{new Airliner("UA", "ORD", "SCE"),515/60},
		{new Airliner("UA", "EWR", "SCE"),480/60},
		{new Airliner("AA", "ORD", "SCE"),500/60},
		{new GeneralAviation("PHL", "SCE"),140/60},
		{new GeneralAviation("EWR", "SCE"),160/60},
		{new GeneralAviation("ORD", "SCE"),180/60}
	};
	ATC atc;

	for (auto element : planesInstantiated)
	{
		element.first->setVel(element.second);
		element.first->setLoiter(70);
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
			viz.visualize_plane(element.first->plane_type(), element.first->getOrigin(), element.first->getDestination(), element.first->getPos());
			planeNum += 1;
		}
		viz.update(timeStep);
	}
	return 0;
}