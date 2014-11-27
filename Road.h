#pragma once

#include "Lane.h"
#include "Vehicle.h"
#include <vector>

class Road
{
	int num_lanes, max_vel, num_vehicles, traffic_condition;
	std::vector <Lane*> lanes;
	std::vector <Vehicle*> vehicles; 

public:
	Road(void);
	~Road(void);
	void generateTraffic();
	int  getMaxVel();
	void updateTraffic();
	void deleteVehicle(int vehicle_id);
	void generateInitialState();
	void clearTraffic();
	void addNewVehicle(int lane);
};

