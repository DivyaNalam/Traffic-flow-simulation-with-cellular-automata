#include <stdafx.h>
#include "SideRoad.h"

SideRoad::SideRoad(int _site, Type _behaviour)
{
	site = _site;
	behaviour = _behaviour;
	vehicle_queue = 0;
}

void SideRoad::add2Queue()
{
	vehicle_queue++;
}

int SideRoad::getSite()
{
	return site;
}

bool SideRoad::isEmpty()
{
	return vehicle_queue<=0 ;
}

void SideRoad::removeFromQueue()
{
	vehicle_queue--;
}