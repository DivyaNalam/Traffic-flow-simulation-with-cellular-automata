#pragma

//#define GLUT_DISABLE_ATEXIT_HACK

#include "stdafx.h"
#include "Road.h"
#include <iostream>
#include <fstream>
#include <string>
#include <process.h>
#include <Windows.h>

/*#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>*/

Road *curRoad;
int canSleep = 1;

using namespace std;
Road::Road()
{
	//ifstream Fin("C:\\Users\\Divya\\Documents\\Self organization\\Cellular Automata\\GitCellularAutomata\\road.txt");
	ifstream Fin("road.txt");
	string line;
	if(!Fin)
	{
		cout<<"provide input file road.txt";
		return;
	}

	num_lanes = num_vehicles = 0;
	while(getline(Fin,line)) 
	{
		lanes.push_back(new Lane(this,line.length()));
		for(size_t pos = 0, len = line.length(); pos<len ; pos++)
		{
			if(line[pos] == '*')
			{	
				addNewVehicle(num_lanes,pos,0);
			}
			if(line[pos] == 'S')
				lanes[num_lanes]->addSideRoad(pos);
		}
		num_lanes++;
	}
	Fin.close();

	cout<<"Enter the speed limit for this road : ";
	cin>>max_vel;
	cout<<"Enter the traffic condition between (1 - 10) 1 - light traffic  10 -jammed ";
	cin>>traffic_condition;
	traffic_condition *= 10;

	::curRoad = this;
	::canSleep = 1;
	
//	_beginthread(waitingThread, 0, (void *)*argv);
	
}

Road::~Road(void)
{
	for(size_t lane=0, len=lanes.size(); lane<len; lane++)
		delete lanes[lane];
	for(size_t vehicle=0, len=vehicles.size(); vehicle<len; vehicle++)
		delete vehicles[vehicle];
}

void Road::generateInitialState() // generate accoring to the traffic condition - need not
{
	int curVh = 0;

	for(int j=0; j<num_vehicles; j++)
	{
		int lane, pos;
		Vehicle *vh;

		/*Choose a lane for putting the vehicle*/
		lane = rand()%num_lanes; 
		pos = rand()%50; //take the  length of each lane here
		while(lanes[lane]->isOccupied(pos))
			pos = rand()%50;
		
		vh = new Vehicle(lanes[lane], pos); 
		vehicles[curVh++] = vh;
	}
}

void Road::clearTraffic()
{
	for(int i=0;i<num_lanes;i++)
		lanes[i] ->clearTraffic();
}

void Road::deleteVehicle(int vehicle_id)
{
	for(std::vector<Vehicle*>::iterator it = vehicles.begin(); it!=vehicles.end(); it++)
		if((*it)->getVehicleId() == vehicle_id)
		{
			vehicles.erase(it);
			num_vehicles-- ;
			break;
		}
}

void Road::generateTraffic()
{
	/*clear everything and start again*/
	//clearTraffic();
	//generateInitialState();
	cout<<"First Dump\n";
	for(int i=0; i<num_lanes; i++)
		lanes[i]->dumpLane(); 

	for(int i=0;i<100;i++)
	{
		if(num_vehicles <= 0) 
			break;
		updateTraffic();
		for(int i=0; i<num_lanes; i++)
			lanes[i]->dumpLane();
		Sleep(1000);
        ::canSleep = 0;  
	}
}

int Road::getMaxVel()
{
	return max_vel;
}

bool Road::addNewVehicle(int lane, int pos, int vel)
{
	bool isAdded = lanes[lane]->addVehicle(pos,vel);
	if(isAdded)		
	{
		vehicles.push_back(new Vehicle(lanes[lane],pos));
		num_vehicles++; 
	}
	return isAdded;
}
void Road::updateTraffic()
{
	
	/*update vehicle velocity*/
	for(int i=0; i<num_vehicles; i++)
	{
		if(vehicles[i] != NULL)
		{
			vehicles[i]->updateVelocity();
		}
	}

	/*update vehicle position*/
	for(int i=0; i<num_vehicles; i++)
	{
		if(vehicles[i] != NULL)
		{
			vehicles[i]->updatePosition();
		}	
	}
	/*generate new vehicles according to the traffic condition*/
	for(int i=0; i<num_lanes; i++)
	{
		lanes[i]->newTrafficHandler(traffic_condition, i);
	}

}

#ifdef LINDA
void Road::waitingThread(void *argv)
{
    int argc =1;
    glutInit(&argc, (char **)&argv);                 
    glutCreateWindow("Freeway traffic simulation"); 
    glutInitWindowSize(600, 600);   
    glutInitWindowPosition(50, 50); 
    glutDisplayFunc(Road::staticDisplayRoad);
    glutTimerFunc(1, Road::staticDisplayTrigger, 0); 
    glutMainLoop();
    _endthread();
}

void Road::staticDisplayRoad()
{
    curRoad->displayRoad();
}

void Road::staticDisplayTrigger(int value)
{
    if(::canSleep == 0)
    {
        glutPostRedisplay();
        ::canSleep = 1;
    }
    glutTimerFunc(100, staticDisplayTrigger, 0);
}

void Road::displayRoad()
{
    int l, longestLaneSites =0;
    float y, x, site_size, vehicle_size;

    glClear(GL_COLOR_BUFFER_BIT);         
 
    /* drawing the lanes */
    y = 0.0;
    for(l=0; l<num_lanes; l++)
    {
        glBegin(GL_LINES);              
            glColor3f(1.0f, 0.0f, 0.0f); 
            glLineWidth(10.0);
            glVertex2f(-1.0f, y);    
            glVertex2f( 1.0f, y);
        glEnd();
        glBegin(GL_LINES);              
            glColor3f(1.0f, 1.0f, 1.0f); 
            glLineWidth(10.0);
            glVertex2f(-1.0f, y+0.05);
            glVertex2f(1.0f, y+0.05);
        glEnd();
        y = y+0.1;
        if((l!=num_lanes) && (lanes[l]->getMaxSites() > longestLaneSites))
            longestLaneSites = lanes[l]->getMaxSites();
    }

    /*calculating site size*/
    site_size = (float)2.0/ (float)longestLaneSites;

    /*Vehicle should fit inside site. Hence, its radius should be small enough*/
    vehicle_size = ((site_size < 0.1) ? site_size : 0.1 )/2;

    /*drawing the sites*/
    y = 0.0;
    for(l=0; l<num_lanes; l++)
    {
        int num_sites = lanes[l]->getMaxSites();
        x = -1.0;
        for(int s=0; s<num_sites; s++)
        {
            glBegin(GL_LINES);              
                glColor3f(1.0f, 0.0f, 0.0f); 
                glLineWidth(10.0);
                glVertex2f(x, y);    
                glVertex2f(x, y+0.05);
            glEnd();

            if(lanes[l]->isOccupied(s) == 1)
            {
                float xoffset = site_size*0.2, yoffset = 0.01;
                glBegin(GL_POLYGON);
                    glColor3f(0.0f, 0.0f, 1.0f);
                    glVertex2f(x+xoffset,y+yoffset);
                    glVertex2f(x+xoffset, y+0.1-yoffset);
                    glVertex2f(x+site_size-xoffset, y+0.1-yoffset);
                    glVertex2f(x+site_size-xoffset, y+yoffset);
                glEnd();
            }
            x = x+site_size;
        }
        y = y + 0.1;
    }


    glFlush();  
}
#endif