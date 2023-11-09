#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "Functions.h"

using namespace std;

void question1()
{
	printMap(locations());
}

void question5()
{
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
	
	for (auto element : planesInstantiated)
	{
		element.first->setVel(element.second);
		element.first->setLoiter(20);
		element.first->time_on_ground();
	}


	while(true)
	{
		double planeNum = 1;
		for (auto element : planesInstantiated)
		{
			element.first->operate(timeStep);
			cout << "Plane" << planeNum <<" pos: "<< element.first->getPos()<< endl;
			planeNum += 1;
		}
		
	}
}
