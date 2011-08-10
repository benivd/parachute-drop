#include "Obstacle.h"


#include <cmath>
#include <iostream>
#include <GL/glut.h>

#include "global.h"


// default constructor added
Obstacle::Obstacle()
{
    crash = false;
	objtype = TEAPOT;
	xAxis = rand() % 2;
	yAxis = rand() % 2;
	if (xAxis == 0 && yAxis == 0)
		zAxis = 1;
	else
		zAxis = rand() % 2;
	spinAngle = 0.0;
	colorGen = rand() % 360;
}


Obstacle::Obstacle(float x, float y, float z , Obstacle* nextnode)
{
    crash = false;
	xPos = x;
	yPos = y;
	zPos = z;
	xAxis = rand() % 2;
	yAxis = rand() % 2;
	if (xAxis == 0 && yAxis == 0)
		zAxis = 1;
	else
		zAxis = rand() % 2;
	spinAngle = 0.0;
	colorGen = rand() % 360;
	next = nextnode;
	objtype = TEAPOT;
}

Obstacle::Obstacle(float x,float y,float z,Obstacle* nextnode, objType objT)
{
    crash = false;
	xPos = x;
	yPos = y;
	zPos = z;
	xAxis = rand() % 2;
	yAxis = rand() % 2;
	if (xAxis == 0 && yAxis == 0)
		zAxis = 1;
	else
		zAxis = rand() % 2;
	spinAngle = 0.0;
	colorGen = rand() % 360;
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

void Obstacle::setCrash(bool state)
{
    crash = state;
}

bool Obstacle::getCrash()
{
    return crash;
}

void Obstacle::draw(int level)
{
    glPushMatrix();
    
    glTranslatef( getXPos(), getYPos(), getZPos() );
	if (objtype==TEAPOT)
	{
        if (!crash)
        {
		    glRotatef(spinAngle, xAxis, yAxis, zAxis);
		    glColor3f(0.5+0.5*sin(0.05*colorGen+M_PI),
                      0.5+0.5*sin(0.05*colorGen+M_PI/2),
                      0.5+0.5*sin(0.05*colorGen));
		    glutSolidTeapot(25);
        }
	}
	if (objtype==SUN)
	{
        if (!crash)
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
        else
        {

        }
	}
	
	if (objtype==CUBE)
	{
        if (!crash)
        {
            glColor3f(0,1,1);
        	glutWireCube(25);
        }
        else
        {

        }
	}
	
	if(objtype==DODEC)
	{
        if (!crash)
        {
		    glColor3f(1,0,0);
		    glScalef(25,25,25);
		    glutSolidDodecahedron();
        }
        else
        {

        }
	}

	if(objtype==ICOSA)
	{
        if (!crash)
        {
            glColor3f(0,0,1);
        	glScalef(25,25,25);
		    glutSolidIcosahedron();
        }
        else
        {

        }
	}

	if(objtype==CONE)
	{
        if (!crash)
        {
		    glColor3f(0,1,1);
		    glScalef(10,10,10);
		    glutSolidCone(10,10,20,20);
        } else {
        
        }
	}

	if(objtype==TORUS)
	{
        if (!crash)
        {
            glColor3f(0,1,0);
            glutSolidTorus(5,10,30,30);
        } else {

        }
	}
    glPopMatrix();
	spinAngle += 5.0;  
}

void Obstacle::move(int level)
{
    zPos += MOVE_BY*level;
}

bool Obstacle::collide(int xDiff, int yDiff)
{
    return (xDiff < 5 && yDiff < 5);
}

void Obstacle::explode()
{
    crash = true;
}
