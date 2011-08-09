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

}

// Player::~Player(); // Using default

void drawmodel(void)
{
    if (!pmodel) {
		//http://www.oyonale.com/modeles.php?lang=en&page=53 for the .obj, made the .mtl myself
        pmodel = glmReadOBJ("ducky.obj");
        if (!pmodel) exit(0);
        glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel, 90.0);
    }
    
    glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
}

void Player::draw()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
	glTranslated(xPos, yPos,-5);
    drawmodel();
    glPopMatrix();
}

void Player::Move(float stepX, float stepY) {
	xPos += stepX;
	yPos += stepY;
}

