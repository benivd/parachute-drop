#include "Obstacle.h"


#include <iostream>
#include <GL/glut.h>

#include "global.h"


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

void Obstacle::draw(int level)
{
    // Make object transparent after FOGEND
    
    glPushMatrix();
    glColor4f(1.0, 1.0, 1.0,(getZPos()/(-1000) < (1 - 0.25*(level-1) ? 1.0:0.0)));
    glTranslatef( getXPos(), getYPos(), getZPos() );
    glutSolidTeapot(2.5);
    glPopMatrix();    
}

void Obstacle::move(int level)
{
    zPos += MOVE_BY*level;
}
