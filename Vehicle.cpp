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
	int new_pos = lane->getNextPosition(pos,velocity);
	if(pos == new_pos)
		return;
	lane->removeVehicle(pos);
	if(new_pos >= lane->getLength())
	{
		lane->deleteVehicle(vehicle_id,pos);
		return;
	}
	lane->addVehicle(new_pos, velocity);
	pos = new_pos;
}

void Vehicle::updateVelocity()
{
	int slowVel = lane->shouldSlowDown(pos,velocity);
	if(slowVel != -1)
		velocity = slowVel;
	else if(lane->canAccelerate(pos, velocity) == 1)
		velocity++;
	int a = rand()%100;
	if(velocity!=1 && velocity!=0 && a<25)
		velocity--;
}