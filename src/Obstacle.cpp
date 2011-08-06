#include "Obstacle.h"

#include <string>
#include <iostream>
#include <GL/glut.h>
using namespace std;

// default constructor added
Obstacle::Obstacle()
{
}


Obstacle::Obstacle(float x, float y, float z , Obstacle* nextnode)
{
	xPos = x;
	yPos = y;
	zPos = z;
	next = nextnode;
}

/*
Obstacle::~Obstacle()
{

}
*/

void Obstacle::setXPos(float x)
{
	xPos = x;
}

void Obstacle::setYPos(float y)
{
	yPos = y;
}

void Obstacle::setZPos(float z)
{
	zPos = z;
}

float Obstacle::getXPos()
{
	return xPos;
}

float Obstacle::getYPos()
{
	return yPos;
}

float Obstacle::getZPos()
{
	return zPos;
}

void Obstacle::setNext(Obstacle* nextnode)
{
	next = nextnode;
}

Obstacle* Obstacle::getNext()
{
	return next;
}

void Obstacle::draw()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef( this->getXPos(), this->getYPos(), this->getZPos() );
    glutSolidTeapot(5.0);
    glPopMatrix();    
}

void Obstacle::move()
{
    zPos += 5;
}
