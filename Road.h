#pragma once

#include "Lane.h"
#include "Vehicle.h"

class Road
{
	int num_lanes, max_vel, num_vehicles;
	class Lane **lanes;
	class Vehicle **vehicles;
public:
	Road(void);
	~Road(void);
	void generateTraffic();
	void updateTraffic();
};

