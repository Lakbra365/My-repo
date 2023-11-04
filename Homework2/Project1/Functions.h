#pragma once
#include <iostream>
#include <map>
#include <string>
#include <random>


using namespace std;


class Plane
{
protected:
	double wait_time;
private:
	double pos, vel, distance, loiter_time;
	bool at_SCE;
	string origin, destination;
	map<string, int> distancesMap = locations();
public:
	Plane(string from, string to)
	{
		origin = from;
		destination = to;
		pos, vel, wait_time, loiter_time, at_SCE = 0;
		if (distancesMap.find(from) == distancesMap.end())
		{
			distance = distancesMap.find(from)->second;
		}
		else
		{
			distance = distancesMap.find(to)->second;
		}
	}
	virtual ~Plane()
	{
		
	}
	void operate(double dt)
	{
		if (loiter_time < 0) 
		{
			loiter_time = 0;
		}
		if (wait_time < 0)
		{
			wait_time = 0;
		}
		if (loiter_time != 0)
		{
			loiter_time -= dt;
		}
		else
		{
			if (wait_time != 0)
			{
				wait_time -= dt;
			}
			else
			{
				if (pos < distance)
				{
					pos += vel * dt;
					at_SCE = 0;
				}
				else
				{
					if (destination == "SCE")
					{
						at_SCE = 1;
					}
					else
					{
						time_on_ground();
						string placeholder = origin;
						origin = destination;
						destination = placeholder;
						pos = 0.0;
					}
				}
			}
		}
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
	bool getSCE()
	{

	}
	void setVel()
	{

	}
	void setLoiter()
	{

	}
	double distance_to_SCE()
	{
		if (destination == "SCE")
		{
			return distance - pos;
		}
	}
	virtual void time_on_ground()
	{

	}
	virtual string plane_type()
	{
		return "GA";
	}
	static double draw_from_normal_dist(double mean, double std)
	{
		random_device rd{};
		mt19937 gen{ rd() };
		normal_distribution<> d{ mean,std };
		return d(gen);
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
