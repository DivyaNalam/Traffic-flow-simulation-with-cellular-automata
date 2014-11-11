#pragma
using namespace std;

#include <iostream>
#include <conio.h>
#include "Road.h"
#include "Vehicle.h"

int Vehicle::vehicle_id_gen = 0;
int main()
{	
	class Road rd;

	rd.generateTraffic();
	_getch();
	return 1;
}