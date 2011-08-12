#include "Obstacle.h"


#include <cmath>
#include <iostream>
#include <GL/glut.h>

#include "global.h"
#include "objLoader/glm.h"
#include "imageloader.h"

//model
GLMmodel* pmodel2;
GLMmodel* pmodel3;
GLMmodel* pmodel4;

//texture
static GLuint MaskTexId;
static GLuint ballTexId;


void Obstacle::LoadVMask(void)
{
	// Load menu texture
	Image* image = loadBMP("tex/VMaskCol.bmp");
	glGenTextures( 1, &MaskTexId );
	glBindTexture( GL_TEXTURE_2D, MaskTexId );
	gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->pixels );
}

void Obstacle::LoadBall(void)
{
	// Load menu texture
	Image* image = loadBMP("tex/Broccoli2.bmp");
	glGenTextures( 1, &ballTexId );
	glBindTexture( GL_TEXTURE_2D, ballTexId );
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

void drawBroc(void)
{
	//glBindTexture( GL_TEXTURE_2D, ballTexId );
    if (!pmodel3) {
        pmodel3 = glmReadOBJ("obj/ladybird.obj");
        if (!pmodel3) exit(0);
        glmUnitize(pmodel3);
        glmFacetNormals(pmodel3);
        glmVertexNormals(pmodel3, 90.0);
    }
    
    glmDraw(pmodel3, GLM_SMOOTH | GLM_MATERIAL );
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
}

void drawSkull(void)
{
	//glBindTexture( GL_TEXTURE_2D, ballTexId );
    if (!pmodel4) {
        pmodel4 = glmReadOBJ("obj/skull.obj");
        if (!pmodel4) exit(0);
        glmUnitize(pmodel4);
        glmFacetNormals(pmodel4);
        glmVertexNormals(pmodel4, 90.0);
    }
    
    glmDraw(pmodel4, GLM_SMOOTH  | GLM_MATERIAL );
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
	objScaler=0;

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
	objScaler=0;

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
	objScaler=0;

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

void Obstacle::setLevel(int level)
{
	level= level;
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
			glRotatef(45,1,1,0);
            if (level != 0) objScaler+=.1;
			float scale=sin(objScaler);
			glRotatef(abs(scale)*180,1,1,0);
			setXPos(getXPos()+(scale));
			setYPos(getYPos()+scale);
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

	if(objtype==BALL)
	{
        if (!crash)
        {
			glScalef(10,10,10);
			glRotatef(180,0,1,0);
			objScaler+=5;
			glRotatef(objScaler,1,0,0);
           	drawBroc();
			setObjRad(9.0);
			if(testMode)	
				glutWireSphere(.9,10,10);
        }
        else
        {

        }
	}

	if(objtype==CONE)
	{
        if (!crash)
        {
			if (level != 0) objScaler+=.01;
			float scale=abs(cos(objScaler));
		    glColor3f(0,1,1);
		    glScalef(scale*10,scale*10,10);
		    glutSolidCone(1,1,20,20);
			setObjRad(scale*10.0);
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
			if (level != 0) objScaler+=.1;
			float scale=sin(objScaler);
			setXPos(getXPos()+scale);
            glColor3f(1,1,1);
			glRotatef(-90,1,0,0);
			glScalef(10,10,10);
            drawSkull();
			setObjRad(10.0);
			if(testMode)
				glutWireSphere(1,10,10);
        }
        else 
        {

        }
	}
    glPopMatrix();
	if (level != 0) spinAngle += 5.0;  
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
