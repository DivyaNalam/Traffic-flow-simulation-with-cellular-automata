
#include "stdafx.h"
#include<iostream>
#include "Lane.h"
#include "Road.h"
#include "SideRoad.h"


using namespace std;
Lane::Lane(Road* _road, size_t _max_sites, int _lane_id)
{
	max_sites = _max_sites;
	road = _road;
	sites = new LaneSite[max_sites];
	vehicle_queue = 0;
	lane_id = _lane_id;
	addSideRoad(0);

}

void Lane::addSideRoad(int pos)
{
	side_roads.push_back(new SideRoad(pos,ENTRY));
}

Lane::~Lane(void)
{
	delete[] sites;
}

void Lane::dumpLane()
{
	for(int i=0; i<max_sites; i++)
	{
		if(!isOccupied(i))
			cout<<".";
		else
			cout<<sites[i].getSpeed();
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
	return sites[pos].isOccupied();

}

void Lane::clearTraffic()
{
	for(int i=0;i<max_sites;i++)
		sites[i].updateSite(-1);
}

void Lane::add2Queue(int sideroad_id)
{
	side_roads[sideroad_id]->add2Queue();
}

void Lane::newTrafficHandler(int traffic_condition, int lane_id)
{
	bool shouldAddVehicle;
	int side_road_probability = traffic_condition/2;
	
	/*check if new vehicle should be generated at the beginning of lane*/
	shouldAddVehicle = (rand()%100 < traffic_condition) ;
	if(shouldAddVehicle)
		add2Queue(0);

	/*vehicle additions at each side road*/
	for(int i=1; i<side_roads.size(); i++)
	{
		shouldAddVehicle = (rand()%100 < side_road_probability) ;
		if(shouldAddVehicle)
			add2Queue(i);
	}

	/*add the vehicles in their respective queues*/
	for(int i=0; i<side_roads.size(); i++)
	{
		if(!side_roads[i]->isEmpty() && road->addNewVehicle(lane_id,side_roads[i]->getSite(),0))
			side_roads[i]->removeFromQueue();
	}

}
bool Lane::findSideRoadIndex(int pos)
{
	for(int i=0; i<side_roads.size(); i++)
		if(side_roads[i]->getSite() == pos)
			return i;
	return -1;
}

bool Lane::addVehicle(int pos, int vel)
{
	if(!isOccupied(pos))
	{
		sites[pos].updateSite(vel);
		return true;
	}
	return false;
}

void Lane::removeVehicle(int pos)
{
	sites[pos].updateSite(-1);
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
		if(isOccupied(i))
			return i-pos-1;
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


void Lane::incrementSiteDensity(int pos)
{
	sites[pos].incrementSiteDensity();
}

void Lane::incrementFlowDensity(int pos)
{
	sites[pos].incrementFlowDensity();
}

int Lane::getSiteDensity(int pos)
{
	return sites[pos].getSiteDensity();
}

int Lane::getFlowDensity(int pos)
{
	return sites[pos].getFlowDensity();
}

Road* Lane::getRoad()
{
	return road;
}

int Lane::getLaneId()
{
	return lane_id;
}

bool Lane::isShiftable(int from, int to)
{
	/*Check for presence of vehicle in the same lane which can possibly come to "to" */
	for(int i=from; i<=to; i++)
	{
		if(isOccupied(i))
			return false;
	}
	return true;
}

bool Lane::checkIndicatingVehicle(int from, int to, Indicators indi)
{
	for(int i=from; i<=to; i++)
	{
		if(isOccupied(i)) 
		{
			Vehicle *vh = road->fetchVehicle(this, i);
			if((vh != NULL) && (vh->getIndicator() == indi))
				return true;
		}
	}
	return false;
}