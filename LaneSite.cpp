#include "LaneSite.h"


LaneSite::LaneSite(void)
{
	speed = -1;
	timeSteps = siteDensity = flowDensity = 0.0;

}

LaneSite::~LaneSite(void)
{
}

void LaneSite::updateSite(int _speed)
{
	speed = _speed;
}

bool LaneSite::isOccupied()
{
	if(speed == -1)
		return 0;
	else
		return 1;
}

int LaneSite::getSpeed()
{
	return speed;
}