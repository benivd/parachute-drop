#include "Obstacle.h"


#include <iostream>
#include <GL/glut.h>

#include "global.h"


// default constructor added
Obstacle::Obstacle()
{
	objtype = TEAPOT;
}


Obstacle::Obstacle(float x, float y, float z , Obstacle* nextnode)
{
	xPos = x;
	yPos = y;
	zPos = z;
	next = nextnode;
	objtype = TEAPOT;
}

Obstacle::Obstacle(float x,float y,float z,Obstacle* nextnode, objType objT)
{
	xPos = x;
	yPos = y;
	zPos = z;
	next = nextnode;
	objtype = objT;
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

void Obstacle::setObjType(objType objT)
{
	objtype= objT;
}

objType Obstacle::getObjType()
{
	return objtype;
}

void Obstacle::draw(int level)
{
    // Make object transparent after FOGEND
    
    glPushMatrix();
    glColor4f(1.0, 1.0, 1.0,(getZPos()/(-1000) < (1 - 0.25*(level-1) ? 1.0:0.0)));
    glTranslatef( getXPos(), getYPos(), getZPos() );
	if (objtype==TEAPOT)
	{
		glColor3f(0,0,1);
		glutSolidTeapot(25);
	}
	if (objtype==SUN)
	{
		GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 0.1f };
		GLfloat dif[] = { 0.7f, 0.7f, 0.7f, 0.1f };
		GLfloat spec[] = { 1.0f, 1.0f, 1.0f, 10.0f };

		//Sun position		
		GLfloat pos[] = {getXPos(),getYPos(), getZPos(), 1.0f};
		glColor3f(1,1,0);
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_POSITION, pos);
		//glLightfv(GL_LIGHT1, GL_AMBIENT, amb); ambient looks wierd
		glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
		glDisable(GL_LIGHTING);
		glutSolidSphere(10,20,20);
		glEnable(GL_LIGHTING);
	}
    glPopMatrix();    
}

void Obstacle::move(int level)
{
    zPos += MOVE_BY*level;
	if (objtype==SUN)
	{
		GLfloat pos[] = {getXPos(),getYPos(), getZPos(), 1.0f};
		glLightfv(GL_LIGHT1, GL_POSITION, pos);
	}
}
