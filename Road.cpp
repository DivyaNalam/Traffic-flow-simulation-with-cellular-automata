#pragma

#include "stdafx.h"
#include "Road.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
Road::Road(void)
{

	ifstream Fin("road.txt");
	string line;
	while(getline(Fin,line)) 
	{
		vector<int> side_roads;
		lanes[num_lanes] = new Lane(this,line.length());
		for(size_t pos = 0, len = line.length(); pos<len ; pos++)
		{
			if(line[pos] == '*')
			{	
				addNewVehicle(num_lanes,pos,0);
			}
			if(line[pos] == 'S')
				lanes[num_lanes]->addSideRoad(pos);
		}
		num_lanes++;
	}
	Fin.close();

	cout<<"Enter the speed limit for this road : ";
	cin>>max_vel;
	cout<<"Enter the traffic condition between (1 - 10) 1 - light traffic  10 -jammed ";
	cin>>traffic_condition;
	traffic_condition *= 10;

	for(int i=0; i<num_vehicles; i++)
		vehicles[i] = NULL;
}


Road::~Road(void)
{
	for(size_t lane=0, len=lanes.size(); lane<len; lane++)
		delete lanes[lane];
	for(size_t vehicle=0, len=vehicles.size(); vehicle<len; vehicle++)
		delete vehicles[vehicle];
}

void Road::generateInitialState() // generate accoring to the traffic condition - need not
{
	int curVh = 0;

	for(int j=0; j<num_vehicles; j++)
	{
		int lane, pos;
		Vehicle *vh;

		/*Choose a lane for putting the vehicle*/
		lane = rand()%num_lanes; 
		pos = rand()%50; //take the  length of each lane here
		while(lanes[lane]->isOccupied(pos))
			pos = rand()%50;
		
		vh = new Vehicle(lanes[lane], pos); 
		vehicles[curVh++] = vh;
	}
}

void Road::clearTraffic()
{
	for(int i=0;i<num_lanes;i++)
		lanes[i] ->clearTraffic();
}

void Road::deleteVehicle(int vehicle_id)
{
	vehicles.erase(vehicles.begin()+vehicle_id);
	num_vehicles-- ;
}

void Road::generateTraffic()
{
	/*clear everything and start again*/
	clearTraffic();
	generateInitialState();
	
	for(int i=0;i<100;i++)
	{
		updateTraffic();
	}
	for(int i=0; i<num_lanes; i++)
		lanes[i]->dumpLane();
}

int Road::getMaxVel()
{
	return max_vel;
}

void Road::addNewVehicle(int lane, int pos, int vel)
{
	bool isAdded = lanes[lane]->addVehicle(pos,vel);
	if(isAdded)		
		vehicles[num_vehicles++] = new Vehicle(lanes[lane],pos);
}
void Road::updateTraffic()
{
	/*generate new vehicles according to the traffic condition*/
	for(int i=0; i<num_lanes; i++)
	{
		bool shouldAddVehicle = rand()%100 < traffic_condition ;
		if(shouldAddVehicle)
			lanes[i]->add2Queue();
		addNewVehicle(i,0,0);
	}

	/*update vehicle velocity*/
	for(int i=0; i<num_vehicles; i++)
	{
		if(vehicles[i] != NULL)
		{
			vehicles[i]->updateVelocity();
		}
	}

	/*update vehicle position*/
	for(int i=0; i<num_vehicles; i++)
	{
		if(vehicles[i] != NULL)
		{
			vehicles[i]->updatePosition();
		}	
	}
}