#pragma once
#include <iostream>
#include <map>
#include <string>

using namespace std;


class Plane
{
protected:
	double wait_time;
private:
	double pos, vel, distance, loiter_time;
	bool at_SCE;
	string origin, destination;
	map<string, int> distances = locations();
public:
	Plane(string from, string to)
	{

	}
	virtual ~Plane()
	{

	}
	void operate(double dt)
	{

	}
	double getPos()
	{

	}
	double getVel()
	{

	}
	double getLoiter()
	{

	}
	string getOrigin()
	{

	}
	string getDestination()
	{

	}
	bool getIfSCE()
	{

	}
};


template <typename T, typename U>

void printMap(map<T, U> mapa)
{
	cout << "{" << endl;
	for (auto element : mapa)
	{
		cout << "[" << element.first << ", " << element.second << "]," << endl;
	}
	cout << "\b}";
}

map<string, int> locations()
{
	map<string, int> distances;
	distances = { {"PHL", 160},
	{"ORD", 640},
	{"EWR", 220} };

	return distances;
}
