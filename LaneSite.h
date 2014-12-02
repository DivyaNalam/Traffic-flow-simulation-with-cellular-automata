#pragma once

#include"common.h"

class LaneSite
{
	int siteDensity, flowDensity, speed;

public:
	LaneSite(void);
	~LaneSite(void);
	bool isOccupied();
	void updateSite(int);
	int getSpeed();
	void incrementSiteDensity();
	void incrementFlowDensity();
	int getSiteDensity();
	int getFlowDensity();
};


