#include "Player.h"

#include <cstdlib>
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

void Player::draw(bool testMode)
{
    glPushMatrix();
	glTranslated(xPos, yPos,zPos);
	glRotatef(180,0,1,0);
	glRotatef(xLean,1,0,0);
	glRotatef(zLean,0,0,1);
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

