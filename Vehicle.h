#pragma once
#include "Lane.h"

class Vehicle
{
	int vehicle_id, velocity;
	class Lane *lane;
	int pos;
	Indicators indicate;

public:
	static int  vehicle_id_gen;
	Vehicle(Lane *_lane, int _pos);
	~Vehicle(void);
	int getVehicleId();
	void updatePosition();
	void updateVelocity();
	bool shiftIntended();
	Lane *getLane();
	int getPos();
	int getVelocity();
	void setIndicator(Indicators);
	Indicators getIndicator();
	void moveVehicle(Lane*);
};


