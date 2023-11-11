#pragma once
#include <iostream>
#include <map>
#include <string>
#include <random>


using namespace std;

map<string, int> locations()
{
	map<string, int> distances;
	distances = { {"PHL", 160},
	{"ORD", 640},
	{"EWR", 220} };

	return distances;
}

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
	string planeType;
	Plane(string from, string to)
	{
		origin = from;
		destination = to;
		pos, vel, wait_time, loiter_time, at_SCE = 0;
		if (origin == "SCE")
		{
			distance = distancesMap.find(destination)->second;
		}
		else
		{
			distance = distancesMap.find(origin)->second;
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
					time_on_ground();
					string placeholder = origin;
					origin = destination;
					destination = placeholder;
					pos = 0.0;
				}
			}
		}
	}
	double getPos()
	{
		return pos;
	}
	double getVel()
	{
		return vel;
	}
	double getLoiter()
	{
		return loiter_time;
	}
	string getOrigin()
	{
		return origin;
	}
	string getDestination()
	{
		return destination;
	}
	bool getSCE()
	{
		return at_SCE;
	}
	void setVel(double inputVel)
	{
		vel = inputVel;
	}
	void setLoiter(double inputLoiter)
	{
		loiter_time = inputLoiter;
	}
	double distance_to_SCE()
	{
		if (destination == "SCE")
		{
			return distance - pos;
		}
	}
	virtual double time_on_ground()
	{
		return wait_time;
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

class Airliner : public Plane
{
private:
	string airline;
public:
	string planeType = "Airliner";
	Airliner(string airlineI, string from, string to) : Plane(from, to)
	{
		airline = airlineI;
	}
	~Airliner()
	{

	}
	string plane_type()
	{
		return airline;
	}
	double time_on_ground()
	{
		wait_time = draw_from_normal_dist(1800, 600);
		return wait_time;
	}
};

class GeneralAviation : public Plane
{
public:
	string planeType = "General Aviation";
	GeneralAviation(string from, string to): Plane(from,to)
	{

	}
	~GeneralAviation()
	{

	}
	double time_on_ground()
	{
		wait_time = draw_from_normal_dist(600, 60);
		return wait_time;
	}
};

class ATC
{
private:
	unsigned int MAX_LANDED_PLANE_NUM = 2;
	unsigned int AIRSPACE_DISTANCE = 50;
	vector<Plane*> registered_planes
	{
		
	};
public:
	ATC()
	{

	}
	~ATC()
	{

	}
	void register_plane(Plane* newPlane)
	{
		registered_planes.push_back(newPlane);
	}
	void control_traffic()
	{
		unsigned int landed_planes = 0;
		unsigned int i = 0;
		while (i< registered_planes.size())
		{
			landed_planes += registered_planes[i]->getSCE();
			i++;
		}
		if (landed_planes >= MAX_LANDED_PLANE_NUM)
		{
			i = 0;
			while (i < registered_planes.size())
			{
				bool x = registered_planes[i]->getSCE();
				double y = registered_planes[i]->distance_to_SCE();
				double z = registered_planes[i]->getLoiter();
				if ( x == 0 && y <= AIRSPACE_DISTANCE && z == 0 )
				{
					registered_planes[i]->setLoiter(100);
					i++;
				}
			}
		}
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





