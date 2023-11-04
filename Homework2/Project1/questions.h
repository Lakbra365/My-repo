#pragma once
#include <iostream>
#include <map>
#include <string>
#include "Functions.h"

using namespace std;

void question1()
{
	printMap(locations());
}

template <typename T>
void question5()
{
	double timeStep = 25;
	map<T, double> planesInstantiated
	{
		{Airliner("AA", "PHL", "SCE"), 470},
		{Airliner("UA", "ORD", "SCE"),515},
		{Airliner("UA", "EWR", "SCE"),480},
		{Airliner("AA", "ORD", "SCE"),500},
		{GeneralAviation("PHL", "SCE"),140},
		{GeneralAviation("EWR", "SCE"),160},
		{GeneralAviation("ORD", "SCE"),180}
	};

	for (auto element : planesInstantiated)
	{
		element.first.setVel(element.second);
	}

	while (true)
	{
		double planeNum = 1;
		for (auto element : planesInstantiated)
		{
			element.first.operate(timeStep);
			cout << "Plane" << planeNum <<" pos: "<< element.first.pos<< endl;
		}
		
	}
}
