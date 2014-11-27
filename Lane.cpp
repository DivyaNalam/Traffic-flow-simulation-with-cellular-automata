

#include<iostream>
#include "stdafx.h"
#include "Lane.h"
#include "Road.h"

using namespace std;
Lane::Lane(Road* _road, size_t _max_sites)
{
	max_sites = _max_sites;
	road = _road;
	sites = new int[max_sites];
	for(int i=0; i<max_sites; i++)
		sites[i] = -1;
}

Lane::~Lane(void)
{
	delete[] sites;
}

void Lane::dumpLane()
{
	for(int i=0; i<max_sites; i++)
	{
		if(sites[i] == -1)
			cout<<".";
		else
			cout<<sites[i];
	}
	cout<<"\n";
}

void Lane::deleteVehicle(int vehicle_id)
{
	road->deleteVehicle(vehicle_id);
}

int Lane::isOccupied(int pos)
{
	if(sites[pos] == -1)
		return 0;
	else
		return 1;
}

void Lane::clearTraffic()
{
	for(int i=0;i<max_sites;i++)
		sites[i] = -1;
}

void Lane::add2Queue()
{
	vehicle_queue++;
}

bool Lane::addNewVehicle()
{
	if(vehicle_queue && !isOccupied(0))
	{
		addVehicle(0,0);
		vehicle_queue--;
		return true;
	}
	return false;
}

void Lane::addVehicle(int pos, int vel)
{
	sites[pos] = vel;
}

void Lane::removeVehicle(int pos)
{
	sites[pos] = -1;
}

int Lane::getLength()
{
	return max_sites;
}

int Lane::getNextPosition(int pos,int vel)
{
	return (pos+vel);
}

int Lane::shouldSlowDown(int pos, int vel)
{
	for(int i=pos+1; i<=pos+vel; i++)
		if(sites[i] != -1)
			return i-pos;
	return -1;
}

int Lane::canAccelerate(int pos, int vel)
{
	if(vel == road->getMaxVel() )
		return 0;
	if(sites[pos+vel+1] == -1)
		return 1;
	else 
		return -1;
}
