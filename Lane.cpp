
#include "stdafx.h"
#include<iostream>
#include "Lane.h"
#include "Road.h"


using namespace std;
Lane::Lane(Road* _road, size_t _max_sites)
{
	max_sites = _max_sites;
	road = _road;
	sites = new int[max_sites];
	vehicle_queue = 0;
	for(int i=0; i<max_sites; i++)
		sites[i] = -1;
}

void Lane::addSideRoad(int pos)
{
	side_roads.push_back(pos);
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

void Lane::deleteVehicle(int vehicle_id, int pos)
{
	removeVehicle(pos);
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

bool Lane::addVehicle(int pos, int vel)
{
	if(pos != 0 && !isOccupied(pos))
	{
		sites[pos] = vel;
		return true;
	}
	if(pos == 0 && vehicle_queue && !isOccupied(0))
	{
		sites[0] = 0;
		vehicle_queue--;
		return true;
	}
	return false;
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
	for(int i=pos+1; i<=pos+vel && i<max_sites; i++)
		if(sites[i] != -1)
			return i-pos;
	return -1;
}

int Lane::canAccelerate(int pos, int vel)
{
	if(vel == road->getMaxVel())
		return 0;
	if(pos+vel+1 >= max_sites) /*vehicles go out of lane bound. Let it accelarate . Delete the vehicle in updatePosition() */
		return 1;
	if(!isOccupied(pos+vel+1))
		return 1;
	else 
		return 0;
}

int Lane::getMaxSites()
{
	return max_sites;
}
