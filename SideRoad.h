#pragma once

enum Type{ENTRY,EXIT} ;

class SideRoad
{
	int site, vehicle_queue;
	Type behaviour;
	
public:
	SideRoad(int _site, Type _behaviour);
	void add2Queue();
	void removeFromQueue();
	int getSite();
	bool isEmpty();
};
