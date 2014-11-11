#pragma once
class Lane
{
	int max_sites, *sites, max_vel;
public:
	Lane(int);
	~Lane(void);
	void dumpLane();
	int isOccupied(int pos);
	void addVehicle(int pos, int vel);
	void removeVehicle(int pos);
	int canAccelerate(int pos, int vel);
	int shouldSlowDown(int pos, int vel);
};

