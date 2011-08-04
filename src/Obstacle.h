/*
 * Obstacle.h
 *
 * Description:
 * Main Obstacle Class.
 *
 * Last Modified:   11/07/22
 * Changelog:       11/07/22 - Constructor, Accessors, Mutators
 *                  11/08/02 - Adapted for helicopter
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <GL/glut.h>
#include "global.h"

class Obstacle
{
    private:
        Obstacle* next;
        float xPos;
        float yPos;
        float zPos;

    public:
        Obstacle();
        // ~Obstacle(); // Using default
        
        void setNext(Obstacle* next) { this->next = next; }
        void setXPos(float x)        { this->xPos = x; }
        void setYPos(float y)        { this->yPos = y; }
        void setZPos(float z)        { this->zPos = z; }
        
        Obstacle* getNext() { return this->next; }
        float getXPos()     { return this->xPos; }
        float getYPos()     { return this->yPos; }
        float getZPos()     { return this->zPos; }

        void draw();
};

#endif
