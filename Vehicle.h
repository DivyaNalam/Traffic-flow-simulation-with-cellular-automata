#pragma once
#include "Lane.h"

class Vehicle
{
	int vehicle_id, velocity;
	class Lane *lane;
	int pos;
public:
	static int  vehicle_id_gen;
	Vehicle(Lane *_lane, int _pos);
	~Vehicle(void);
	int getVehicleId();
	void updatePosition();
	void updateVelocity();
};

