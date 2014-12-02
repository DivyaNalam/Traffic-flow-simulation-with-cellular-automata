
#pragma once

class LaneSite
{
	float siteDensity, flowDensity;
	int timeSteps, speed;
public:
	LaneSite(void);
	~LaneSite(void);
	bool isOccupied();
	void updateSite(int);
	int getSpeed();
};


