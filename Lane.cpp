#pragma
using namespace std;

#include<iostream>
#include "Lane.h"


Lane::Lane(int _max_vel)
{
	max_sites = 100;
	sites = new int[max_sites];
	for(int i=0; i<max_sites; i++)
		sites[i] = -1;
	max_vel = _max_vel;
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

int Lane::isOccupied(int pos)
{
	if(sites[pos] == -1)
		return 1;
	else
		return 0;
}

void Lane::addVehicle(int pos, int vel)
{
		sites[pos] = vel;
}

void Lane::removeVehicle(int pos)
{
	sites[pos] = -1;
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
	if(vel == max_vel)
		return 0;
	if(sites[pos+vel+1] == -1)
		return 1;
	else 
		return -1;
}