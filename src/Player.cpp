#include "Player.h"

#include <cstdlib>
#include <iostream>

#if defined _WIN32
# include <Windows.h>
#endif

#include <GL/glut.h>

#include "objLoader/glm.c"


//model
GLMmodel* pmodel;

Player::Player()
{
    setLives(3);
    setLives(3);
    setPoints(0);
    setXPos( GAME_WIDTH  /2 );
    setYPos( GAME_HEIGHT /2 );
	setZPos( -5);
	setSpinout(false);
	ySpin=0;
	setRad(.6);
	hittable=true;
}

// Player::~Player(); // Using default

void drawmodel(void)
{
    if (!pmodel) {
		//http://www.oyonale.com/modeles.php?lang=en&page=53 for the .obj, made the .mtl myself
        pmodel = glmReadOBJ("obj/ducky.obj");
        if (!pmodel) exit(0);
        glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel, 90.0);
	 }
    
    glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
}

void Player::explode()
{
#if defined _WIN32
	PlaySound(L"snd/cardboard_box_impact_hard1.wav", NULL, SND_FILENAME | SND_ASYNC);
#endif
	if(health!=1) {
		setSpinout(true);
	}
	else
	{
		flash=true;
		flashcount=10;
		hittable=false;
	}
}

void Player::draw(bool testMode)
{
    glPushMatrix();
	glTranslated(xPos, yPos,zPos);
	glRotatef(180,0,1,0);
	glRotatef(xLean,1,0,0);
	glRotatef(zLean,0,0,1);	
	if(spinout)
	{
		setYspin(getYSpin()+25);
		if(getYSpin()>=360)
		{
			ySpin=0;
			spinout=false;
		}
	}
	glRotatef(ySpin,0,1,0);
	if(flash)
	{
		flashcount=flashcount-1;
		if(flashcount==0)
		{
			flash=false;
			hittable=true;
		}
	}
	if(flashcount%2==0)
		drawmodel();	
	if(testMode)
		glutWireSphere(.6,10,10);
    glPopMatrix();
}

void Player::Move(float stepX, float stepY) {
	xPos += stepX;
	yPos += stepY;	
}

void Player::Lean() {
	xLean=xLean*.9;
	zLean=zLean*.9;
}

