#pragma
using namespace std;

#include <iostream>
#include <conio.h>
#include "Road.h"
#include "Vehicle.h"

int Vehicle::vehicle_id_gen = 0;
int main(int argc, char **argv)
{	
	class Road rd(argc, argv);

	rd.generateTraffic();
	_getch();
	return 1;
}