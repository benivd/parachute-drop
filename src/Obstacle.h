/*
 * Obstacle.h
 *
 * Description:
 * Main Obstacle Class.
 *
 * Last Modified:   11/07/22
 * Changelog:       11/07/22 - Constructor, Accessors, Mutators
 *                  11/08/02 - Adapted for helicopter
 *                  11/08/06 - Implemented as Linked List Node
 */

#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle
{

	private:
		float xPos, yPos, zPos;                 // Object coordinates
		Obstacle* next;                         // A pointer to the next node

	public:
		Obstacle();                             //default constructor is added
		Obstacle(float,float,float,Obstacle*);  // Regular constructor
		//~Obstacle();                          // Destructor

		void setXPos(float);
		float getXPos();

		void setYPos(float);
		float getYPos();

		void setZPos(float);
		float getZPos();

		void setNext(Obstacle*); // Changes next
		Obstacle* getNext();     // Returns next

        void draw(int level);
        void move(int level);

};

#endif
