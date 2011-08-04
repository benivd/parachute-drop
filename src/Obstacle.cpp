#include "Obstacle.h"
#include <stdlib.h>
#include <time.h>

Obstacle::Obstacle()
{
    srand( time(NULL) );
    setXPos( rand() % GAME_WIDTH  );
    setYPos( rand() % GAME_HEIGHT );
    setZPos(GAME_DEPTH);
}

// Obstacle::~Obstacle() // Using default
        
void Obstacle::draw()
{
    glPushMatrix();
    glTranslatef(getXPos(), getYPos(), getZPos());
    glutWireTeapot(1.0);
    glPopMatrix();
}
