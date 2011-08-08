#include "Player.h"

#include <GL/glut.h>



Player::Player()
{
    setLives(3);
    setLives(3);
    setPoints(0);
    setXPos( GAME_WIDTH  /2 );
    setYPos( GAME_HEIGHT /2 );

}

// Player::~Player(); // Using default

void Player::draw()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
	glTranslated(xPos, yPos,-5);
    glutWireCube(1.0);
    glPopMatrix();
}

void Player::Move(float stepX, float stepY) {
	xPos += stepX;
	yPos += stepY;
}
