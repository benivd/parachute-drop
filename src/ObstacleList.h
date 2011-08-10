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

class ObstacleList
{
	private:
		Obstacle* first;
		Obstacle* last;

	public:
		ObstacleList();       //Default constructor
		//~ObstacleList();
        
        Obstacle* getFirst();
		
        // Returns true if this list contains no elements.
		bool isEmpty();

		// Returns the number of elements in this LList.
		int size();

		// Insert new element at the end of this LList
		void insert(float xPos, float yPos, float zPos);
		
        // Remove the first element in this LList
        void remove();
			
		void moveAll(int level);

        void drawAll(int level);
        void removeAll();
};

#endif
