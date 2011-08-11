#include "Obstacle.h"


#include <cmath>
#include <iostream>
#include <GL/glut.h>

#include "global.h"
#include "objLoader/glm.h"
#include "imageloader.h"

//model
GLMmodel* pmodel2;

//texture
static GLuint MaskTexId;


void Obstacle::LoadVMask(void)
{
	// Load menu texture
	Image* image = loadBMP("tex/VMaskCol.bmp");
	glGenTextures( 1, &MaskTexId );
	glBindTexture( GL_TEXTURE_2D, MaskTexId );
	gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->pixels );
}

void drawVMask(void)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture( GL_TEXTURE_2D, MaskTexId );
    if (!pmodel2) {
        pmodel2 = glmReadOBJ("obj/VMask.obj");
        if (!pmodel2) exit(0);
        glmUnitize(pmodel2);
        glmFacetNormals(pmodel2);
        glmVertexNormals(pmodel2, 90.0);
    }
    
    glmDraw(pmodel2, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE );
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
}

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
	sunNum= 0;

    // TODO: define a size for each object
    objSize = 10.0;
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
	sunNum= 0;

    // TODO: define a size for each object
    objSize = 10.0;
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
	sunNum= 0;

    // TODO: define a size for each object
    objSize = 10.0;
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

void Obstacle::setObjSize(int size)
{
    objSize = size;
}

int Obstacle::getObjSize()
{
    return objSize;
}

void Obstacle::setObjRad(float rad)
{
	objRad= rad;
}

float Obstacle::getObjRad()
{
	return objRad;
}

void Obstacle::setSunNum(int sun)
{
	sunNum=sun;
}

int Obstacle::getSunNum()
{
	return sunNum;
}

void Obstacle::draw(int level, bool testMode)
{
    glPushMatrix();
    
    glTranslatef( getXPos(), getYPos(), getZPos() );
	if (objtype==TEAPOT)
	{
        if (!crash)
        {
           // glTranslatef(0.0, 0.0, -objSize);
		    glRotatef(spinAngle, xAxis, yAxis, zAxis);
		    glColor3f(0.5+0.5*sin(0.05*colorGen+M_PI),
                      0.5+0.5*sin(0.05*colorGen+M_PI/2),
                      0.5+0.5*sin(0.05*colorGen));
            glMaterialf(GL_FRONT, GL_DIFFUSE, 1.0);
		    glutSolidTeapot(25);
			setObjRad(25.0);
			if(testMode)
				glutWireSphere(25,10,10);
        }
	}
	if (objtype==SUN)
	{
        if (!crash)
        {						
		    //Sun position		
		    GLfloat pos[] = {getXPos(),getYPos(), getZPos(), 1.0f};		
			glColor3f(1,1,0);
            // glTranslatef(0.0, 0.0, -objSize);
			if (sunNum=1)
			{			  				
				  GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 10.0f };
				  GLfloat dif[] = { 0.7f, 0.7f, 0.7f, 1.0f };
				  GLfloat spec[] = { 1.0f, 0.0f, 0.0f, 1.0f };
				glEnable(GL_LIGHT1);
				glLightfv(GL_LIGHT1, GL_POSITION, pos);
	    		glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
				glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, dif);
			}
			if (sunNum=2)
			{			  			
				  GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 10.0f };
				  GLfloat dif[] = { 0.7f, 0.7f, 0.7f, 1.0f };
				  GLfloat spec[] = { 0.0f, 1.0f, 0.0f, 1.0f };
				glEnable(GL_LIGHT2);
				glLightfv(GL_LIGHT2, GL_POSITION, pos);
	    		//glLightfv(GL_LIGHT2, GL_AMBIENT, amb); 
				glLightfv(GL_LIGHT2, GL_SPECULAR, spec);
				glLightfv(GL_LIGHT2, GL_DIFFUSE, dif);
			}
			if (sunNum=3)
			{		
				  GLfloat amb[] = { 0.3f, 0.3f, 0.3f, 10.0f };
				  GLfloat dif[] = { 0.7f, 0.7f, 0.7f, 1.0f };
				  GLfloat spec[] = { 0.0f, 0.0f, 1.0f, 1.0f };
				glEnable(GL_LIGHT3);
				glLightfv(GL_LIGHT3, GL_POSITION, pos);
	    		//glLightfv(GL_LIGHT3, GL_AMBIENT, amb);
				glLightfv(GL_LIGHT3, GL_SPECULAR, spec);
				glLightfv(GL_LIGHT3, GL_DIFFUSE, dif);
			}
				glDisable(GL_LIGHTING);
				glutSolidSphere(10,20,20);
				glEnable(GL_LIGHTING);
				setObjRad(10.0);
				if(testMode)
					glutWireSphere(10,10,10);
        }
        else
        {

        }
	}
	
	if (objtype==CUBE)
	{
        if (!crash)
        {
            //glTranslatef(0.0, 0.0, -objSize);
            glColor3f(0,1,1);
        	glutWireCube(25);
			setObjRad(15.0);
			if(testMode)
				glutWireSphere(15,10,10);
        }
        else
        {

        }
	}
	
	if(objtype==VMASK)
	{
        if (!crash)
        {
            //glTranslatef(0.0, 0.0, -objSize);
			glPushMatrix();
		    glColor4f(1,0,0,.1);
		    glScalef(25,25,25);
		    drawVMask();
			glPopMatrix();
			glColor4f(1,0,1,1);
			setObjRad(25.0);
			if(testMode)
				glutWireSphere(25,10,10);
		}
        else
        {

        }
	}

	if(objtype==ICOSA)
	{
        if (!crash)
        {
            //glTranslatef(0.0, 0.0, -objSize);
            glColor3f(0,0,1);
        	glScalef(25,25,25);
		    glutSolidIcosahedron();
			setObjRad(25.0);
			if(testMode)	
				glutWireSphere(1,10,10);
        }
        else
        {

        }
	}

	if(objtype==CONE)
	{
        if (!crash)
        {
            //glTranslatef(0.0, 0.0, -objSize);
		    glColor3f(0,1,1);
		    glScalef(10,10,10);
		    glutSolidCone(1,1,20,20);
			setObjRad(10.0);
			if(testMode)
				glutWireSphere(1,10,10);
        }
		else 
        {
        
        }
	}

	if(objtype==TORUS)
	{
        if (!crash)
        {
            //glTranslatef(0.0, 0.0, -objSize);
            glColor3f(0,1,0);
            glutSolidTorus(5,10,30,30);
			setObjRad(15.0);
			if(testMode)
				glutWireSphere(15,10,10);
        }
        else 
        {

        }
	}
    glPopMatrix();
	spinAngle += 5.0;  
}

void Obstacle::move(int level)
{
    zPos += MOVE_BY*level;
}

/*
bool Obstacle::collide(int xDiff, int yDiff)
{
    return (xDiff < objSize/2 + PLAYER_SIZE && yDiff < objSize/2 + PLAYER_SIZE);
}
*/

void Obstacle::explode()
{
    crash = true;
}
