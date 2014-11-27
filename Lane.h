#pragma once
class Road;
class Lane
{
	int max_sites, *sites , vehicle_queue; //Move max_velocity inside road
	Road* road;
public:
	Lane(Road*, size_t _max_sites);
	~Lane(void);
	void dumpLane();
	int isOccupied(int pos);
	void addVehicle(int pos, int vel);
	void add2Queue();
	bool addNewVehicle();
	int getLength();
	void deleteVehicle(int vehicle_id);
	void removeVehicle(int pos);
	int canAccelerate(int pos, int vel);
	int shouldSlowDown(int pos, int vel);
	int getNextPosition(int pos,int vel);
	void clearTraffic();
};

