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
GLMmodel* pmodel5;
GLMmodel* pmodel6;

//texture
static GLuint MaskTexId;
static GLuint BUGTexId;


void Obstacle::LoadVMask(void)
{
	// Load menu texture
	Image* image = loadBMP("tex/VMaskCol.bmp");
	glGenTextures( 1, &MaskTexId );
	glBindTexture( GL_TEXTURE_2D, MaskTexId );
	gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->pixels );
}

void Obstacle::LoadBug(void)
{
	// Load menu texture
	Image* image = loadBMP("tex/color.bmp");
	glGenTextures( 1, &BUGTexId );
	glBindTexture( GL_TEXTURE_2D, BUGTexId );
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

void drawBug(void)
{
	//glBindTexture( GL_TEXTURE_2D, BUGTexId );
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

void drawGlove(void)
{
	//glBindTexture( GL_TEXTURE_2D, BUGTexId );
	//http://www.turbosquid.com/FullPreview/Index.cfm/ID/223158
    if (!pmodel5) {
        pmodel5 = glmReadOBJ("obj/gloveLow_poly.obj");
        if (!pmodel5) exit(0);
        glmUnitize(pmodel5);
        glmFacetNormals(pmodel5);
        glmVertexNormals(pmodel5, 90.0);
    }
    
    glmDraw(pmodel5, GLM_SMOOTH | GLM_MATERIAL );
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
}

void drawSword(void)
{
	//glBindTexture( GL_TEXTURE_2D, BUGTexId );
	//http://www.turbosquid.com/FullPreview/Index.cfm/ID/362147
    if (!pmodel6) {
        pmodel6 = glmReadOBJ("obj/rzr.obj");
        if (!pmodel6) exit(0);
        glmUnitize(pmodel6);
        glmFacetNormals(pmodel6);
        glmVertexNormals(pmodel6, 90.0);
    }
    
    glmDraw(pmodel6, GLM_SMOOTH );
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
}


void drawSkull(void)
{
	//glBindTexture( GL_TEXTURE_2D, BUGTexId );
	//http://www.turbosquid.com/FullPreview/Index.cfm/ID/269706
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
	objScaler= rand() %100;

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
	objScaler= rand() %100;

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
	objScaler= rand() %100;

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
	if(level!=0)objScaler+=1;
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
				float scale=abs(cos(objScaler));
				glutSolidSphere((scale*2)+10,20,20);
				glEnable(GL_LIGHTING);
				setObjRad((scale*2)+10.0);
				if(testMode)
					glutWireSphere((scale*2)+10,10,10);
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
			float scale=sin(objScaler/10);
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
			float scale=sin(objScaler/10);
			glRotatef(scale*20,0,0,1);
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

	if(objtype==BUG)
	{
        if (!crash)
        {
			glScalef(20,20,20);
			glRotatef(180,0,1,0);
			objScaler+=4;
			glRotatef(objScaler,1,0,0);
           	drawBug();
			setObjRad(18.0);
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
			float scale=abs(cos(objScaler/10));
		    glColor3f(scale,(1-scale),0);
		    glScalef(scale*20,scale*20,10);
		    glutSolidCone(1,1,20,20);
			setObjRad(scale*20.0);
			if(testMode)
				glutWireSphere(1,10,10);
        }
		else 
        {
        
        }
	}

	if(objtype==SKULL)
	{
        if (!crash)
        {
			float scale=sin(objScaler/10);
			setXPos(getXPos()+scale);
            glColor3f(1,1,1);
			glRotatef(-90,1,0,0);
			glScalef(20,20,20);
            drawSkull();
			setObjRad(20.0);
			if(testMode)
				glutWireSphere(1,10,10);
        }
        else 
        {

        }
	}

	if(objtype==GLOVE)
	{
        if (!crash)
        {
            //glTranslatef(0.0, 0.0, -objSize);
			glPushMatrix();
			float scale=sin(objScaler/10);
			setZPos(getZPos()+scale*12);
			glRotatef(objScaler*5,0,0,1);
			glRotatef(-90,1,0,0);
		    glScalef(25,25,25);
		    drawGlove();
			glPopMatrix();
			glColor4f(1,0,1,1);
			setObjRad(20.0);
			if(testMode)
				glutWireSphere(20,10,10);
		}
        else
        {

        }
	}

	if(objtype==SWORD)
	{
        if (!crash)
        {
            //glTranslatef(0.0, 0.0, -objSize);
			float scale=sin(objScaler/10);
			float scale2=cos(objScaler/10);
			glColor3f((rand() % 10) /10.0,(rand() % 10) /10.0,(rand() % 10)/10.0);
			setYPos(getYPos()+scale*2);
			setXPos(getXPos()+scale2*2);			
			glPushMatrix();
			glRotatef(objScaler*150,0,0,1);
			glRotatef(-90,1,0,0);		    
			glScalef(35,35,35);
		    drawSword();
			glPopMatrix();
			glPushMatrix();		
			glRotatef(objScaler*150+90,0,0,1);
			glRotatef(-90,1,0,0);
			glScalef(35,35,35);
		    drawSword();
			glPopMatrix();
			glColor4f(1,0,1,1);
			setObjRad(35.0);
			if(testMode)
				glutWireSphere(35,10,10);
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
