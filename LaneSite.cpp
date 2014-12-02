#include <stdafx.h>
#include "LaneSite.h"


LaneSite::LaneSite(void)
{
	speed = -1;
	siteDensity = flowDensity = 0;
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


void LaneSite::incrementSiteDensity()
{
	siteDensity++;
}

void LaneSite::incrementFlowDensity()
{
	flowDensity++;
}

int LaneSite::getSiteDensity()
{
	return siteDensity;
}

int LaneSite::getFlowDensity()
{
	return flowDensity;
}
