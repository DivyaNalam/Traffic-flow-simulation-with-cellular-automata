#include "stdafx.h"
#include "Vehicle.h"
#include "Road.h"
using namespace std;

Vehicle::Vehicle(Lane* _lane, int _pos)
{
	vehicle_id = ++vehicle_id_gen;
	lane = _lane;
	pos = _pos;
	velocity = 0;
	lane->addVehicle(pos, velocity);
	indicate = NONE;
}


Vehicle::~Vehicle(void)
{
	vehicle_id_gen = 0;
}

int Vehicle::getVehicleId()
{
	return vehicle_id;
}

void Vehicle::updatePosition()
{
	int new_pos = lane->getNextPosition(pos,velocity);
	int flowUpdatePos;
	lane->incrementSiteDensity(new_pos);
	lane->removeVehicle(pos);
	if(new_pos!=pos)
	{
		flowUpdatePos = (new_pos>=lane->getLength()) ? lane->getLength() : new_pos;
		for(int p=pos+1; p<=flowUpdatePos; p++)
			lane->incrementFlowDensity(p);
	}
	if(new_pos >= lane->getLength())
	{
		lane->deleteVehicle(vehicle_id,pos);
		return;
	}
	lane->addVehicle(new_pos, velocity);
	pos = new_pos;
}

void Vehicle::moveVehicle(Lane *dstLane)
{
	int to = pos + velocity + 1;
	int actualPosition = (to < dstLane->getMaxSites())? to:dstLane->getMaxSites();

	for(int p=pos; p<=velocity; p++)
		lane->incrementFlowDensity(p);
	dstLane->incrementSiteDensity(actualPosition);
	lane->incrementFlowDensity(actualPosition);
	if(to > dstLane->getMaxSites())
	{
		actualPosition = lane->getMaxSites();
		lane->deleteVehicle(vehicle_id, pos);
	}
	else
	{
		actualPosition = to;
		lane->removeVehicle(pos);
		dstLane->addVehicle(to, velocity+1);
		setIndicator(NONE);
	}
}

void Vehicle::updateVelocity()
{
	int slowShiftProb = 60, noAccShiftProb = 30;
	Road *rd = lane->getRoad();

	int slowVel = lane->shouldSlowDown(pos,velocity);
	if(slowVel != -1)
	{
		if(rand()%100 < slowShiftProb)
			rd->addShiftIntension(this);
		velocity = slowVel; /*should the velocity be changed if the shift intention is declared*/
	}
	else if(lane->canAccelerate(pos, velocity) == 1)
		velocity++;
	else
	{
		if(velocity!=rd->getMaxVel() && rand()%100 < noAccShiftProb)
			rd->addShiftIntension(this);
	}
	
	if(velocity!=1 && velocity!=0 && rand()%100<25)
		velocity--;
}

Lane *Vehicle::getLane()
{
	return lane;
}

int Vehicle::getPos()
{
	return pos;
}

int Vehicle::getVelocity()
{
	return velocity;
}

void Vehicle::setIndicator(Indicators indi)
{
	indicate = indi;
}

Indicators Vehicle::getIndicator()
{
	return indicate;
}