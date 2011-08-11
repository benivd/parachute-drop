#include "ObstacleList.h"
#include "Obstacle.h"

#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

// Default constructor
ObstacleList::ObstacleList() 
{
	first = 0;
	last = 0;
    current = 0;
}

/*
//Destructor
ObstacleList::~ObstacleList()
{

}
*/

Obstacle* ObstacleList::getFirst()
{
    return first;
}

Obstacle* ObstacleList::getCurrent()
{
    return current;
}

void ObstacleList::setCurrent(Obstacle* obstacle)
{
    current = obstacle;
}

//Boolean function returns tru id the link list is empty
bool ObstacleList::isEmpty()
{
	if(first == 0)
		return true;
	else
		return false;
}


// Returns the number of elements in this LList
int ObstacleList::size()
{
	Obstacle* temp;
	int i = 1;
	
	if(isEmpty())
		return 0;
	
	else
	{
		for(temp = first; temp != last ; temp = temp->getNext() )
			i++;
		return i;
	}

}

// Insert an element at the end of the ObstacleList 
void ObstacleList::insert(float xPos, float yPos, float zPos)
{
	int randObj = rand() % 7;	
	Obstacle* MyNode = new Obstacle(xPos, yPos, zPos, NULL);
	if (randObj==0)
	{
		MyNode->setObjType(SUN);
	}
	if (randObj==1)
		MyNode->setObjType(CUBE);
	if (randObj==2)
		MyNode->setObjType(VMASK);
	if (randObj==3)
		MyNode->setObjType(ICOSA);
	if (randObj==4)
		MyNode->setObjType(CONE);
	if (randObj==5)
		MyNode->setObjType(TORUS);

	if(last != 0)
	{
		last->setNext(MyNode);
		last = MyNode;
	}
    // First element ?
	else								
	{
		last = MyNode;
		first = last;
        current = first;
	}
}


void ObstacleList::remove()
{
    if (isEmpty())
    {
        return;
    }
    else if (first == last)
	{
		first = 0;
		last = 0;
        current = 0;
	}
	else
	{
		if (current == first) current = first->getNext();
        first = first->getNext();
    }
}


void ObstacleList::moveAll(int level)
{
	float zparameter = 0;

    if (isEmpty()) return;
	if (first!=0)			//Verify first if the link list is not empty
	{

		if(first ==last)	//If only one obstacle in the link List, set its Z coordinates
		{
            first->move(level);
		}
		else						//If multiple obstacle in the link List then loop through the link list		
		{
			Obstacle * temp = first;

			do{
                temp->move(level);
       			temp = temp->getNext();

			}while(temp!= last);

			//For the last node in the link list
            last->move(level);

		}
	}

}

void ObstacleList::drawAll(int level)
{
    

    if (isEmpty()) return;
	if (first!=0)			//Verify first if the link list is not empty
	{

		if(first ==last)	//If only one obstacle in the link List, set its Z coordinates
		{
            first->draw(level);
		}
		else						//If multiple obstacle in the link List then loop through the link list		
		{
			Obstacle * temp = first;

			do{
                temp->draw(level);
			temp = temp->getNext();

			}while(temp!= last);

			//For the last node in the link list
            last->draw(level);

		}
	}

}

void ObstacleList::removeAll()
{
    first = 0;
    current = 0;
    last = 0;
}
