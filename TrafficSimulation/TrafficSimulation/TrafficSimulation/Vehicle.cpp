#include "Vehicle.h"


Vehicle::Vehicle(Lane *_lane, int _pos)
{
	vehicle_id = ++vehicle_id_gen;
	lane = _lane;
	pos = _pos;
	velocity = 1;
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
	pos = pos + velocity;
	lane->addVehicle(pos, velocity);
}

void Vehicle::updateVelocity()
{
	int slowVel = lane->shouldSlowDown(pos,velocity);
	if(slowVel != -1)
		velocity = slowVel;
	else if(lane->canAccelerate(pos, velocity) == 1)
		velocity++;
}