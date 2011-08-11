/*
 * ObstacleList.h
 *
 * Description:
 * Linked List of Obstacles Nodes.
 *
 * Last Modified:   11/08/06
 * Changelog:       11/07/22 - Constructor, Accessors, Mutators
 *                  11/08/06 - Implemented as linked list
 */

#ifndef OBSTACLE_LIST_H
#define OBSTACLE_LIST_H

#include "Obstacle.h"
#include "Player.h"

class ObstacleList
{
	private:
		Obstacle* first;
		Obstacle* last;
        Obstacle* current;

	public:
		ObstacleList();       //Default constructor
		//~ObstacleList();
        
        Obstacle* getFirst();
        Obstacle* getCurrent();
        void setCurrent(Obstacle* obstacle);
		
        // Returns true if this list contains no elements.
		bool isEmpty();

		// Returns the number of elements in this LList.
		int size();

		// Insert new element at the end of this LList
		void insert(float xPos, float yPos, float zPos);

		float distance(float,float,float,float,float,float);

		bool CollidesAll(Player player);
		
        // Remove the first element in this LList
        void remove();
			
		void moveAll(int level);

        void drawAll(int level, bool testMode);
        void removeAll();
};

#endif
