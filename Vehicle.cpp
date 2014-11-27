#include "stdafx.h"
#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle(Lane* _lane, int _pos)
{
	vehicle_id = ++vehicle_id_gen;
	lane = _lane;
	pos = _pos;
	velocity = 0;
	lane->addVehicle(pos, velocity);
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
	lane->removeVehicle(pos);
	pos = lane->getNextPosition(pos,velocity);
	if(pos > lane->getLength())
	{
		lane->deleteVehicle(vehicle_id);
		return;
	}
	lane->addVehicle(pos, velocity);
}

void Vehicle::updateVelocity()
{
	int slowVel = lane->shouldSlowDown(pos,velocity);
	if(slowVel != -1)
		velocity = slowVel;
	else if(lane->canAccelerate(pos, velocity) == 1)
		velocity++;

	if(velocity!=0 && velocity!=-1 && rand()%100<25)
		velocity--;
}