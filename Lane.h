#pragma once
#include <vector>

class Road;

class Lane
{
	int max_sites, *sites , vehicle_queue; //Move max_velocity inside road
	std::vector<int> side_roads;
	Road* road;
public:
	Lane(Road*, size_t _max_sites);
	~Lane(void);
	void dumpLane();
	int isOccupied(int pos);
	bool addVehicle(int pos, int vel);
	void add2Queue();
	int getLength();
	void addSideRoad(int pos);
	void deleteVehicle(int vehicle_id, int pos);
	void removeVehicle(int pos);
	int canAccelerate(int pos, int vel);
	int shouldSlowDown(int pos, int vel);
	int getNextPosition(int pos,int vel);
	void clearTraffic();
	int getMaxSites();
};

