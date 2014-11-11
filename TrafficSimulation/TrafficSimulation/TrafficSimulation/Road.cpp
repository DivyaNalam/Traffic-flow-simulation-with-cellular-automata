#pragma
using namespace std;

#include "Road.h"
#include <iostream>


Road::Road(void)
{
	float density;

	cout<<"Enter the number of lanes : ";
	cin>>num_lanes;

	cout<<"Enter the density of vehicles on road (0-1): ";
	cin>>density;
	num_vehicles = density*num_lanes*100;
	vehicles = new Vehicle *[num_vehicles];
	for(int i=0; i<num_vehicles; i++)
		vehicles[i] = NULL;
 
	cout<<"Enter the speed limit for this road : ";
	cin>>max_vel;

	lanes = new Lane *[num_lanes];
	for(int i=0; i<num_lanes; i++)
		lanes[i] = new Lane(max_vel);
}


Road::~Road(void)
{
	delete[] lanes;
	/*for(int i =0; i<num_vehicles; i++)
	{
		if(vehicles[i] != NULL)
			delete vehicles[i];
	}*/
	delete[] vehicles;
}

void Road::generateTraffic()
{
	int curVh = 0;

	for(int j=0; j<5; j++)
	{
		int lane;
		Vehicle *vh;

		/*Choose a lane for putting the vehicle*/
		lane = rand()%num_lanes;
		vh = new Vehicle(lanes[lane], 0);
		vehicles[curVh++] = vh;

		for(int i=0; i<num_lanes; i++)
			lanes[i]->dumpLane();
		updateTraffic();
	}
}

void Road::updateTraffic()
{
	for(int i=0; i<num_vehicles; i++)
	{
		if(vehicles[i] != NULL)
		{
			vehicles[i]->updateVelocity();
		}
	}
	for(int i=0; i<num_vehicles; i++)
	{
		if(vehicles[i] != NULL)
		{
			vehicles[i]->updatePosition();
		}	
	}
}