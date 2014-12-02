#pragma once
#include <vector>
#include "LaneSite.h"
#include "SideRoad.h"

class Road;

class Lane
{
	int max_sites , vehicle_queue; 
	LaneSite* sites;
	std::vector<SideRoad*> side_roads;
	Road* road;
public:
	Lane(Road*, size_t _max_sites);
	~Lane(void);
	void dumpLane();
	void newTrafficHandler(int traffic_condition);
	int isOccupied(int pos);
	bool addVehicle(int pos, int vel);
	bool findSideRoadIndex(int pos);
	void add2Queue(int sideroad_id);
	int getLength();
	void addSideRoad(int pos);
	void deleteVehicle(int vehicle_id, int pos);
	void removeVehicle(int pos);
	int canAccelerate(int pos, int vel);
	int shouldSlowDown(int pos, int vel);
	int getNextPosition(int pos,int vel);
	void newTrafficHandler(int traffic_condition, int lane_id);
	void clearTraffic();
	int getMaxSites();
};

