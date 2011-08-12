#include "ObstacleList.h"
#include "Obstacle.h"


#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

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

int ObstacleList::getSunNumb()
{
	if(sun1==false){
		sun1=true;
		return 1;
	}
	else if(sun2==false){
		sun2=true;
		return 2;
	}
	else if(sun3==false)
	{
		sun3=true;
		return 3;
	}
	else 
		return 0;
}

// Insert an element at the end of the ObstacleList 
void ObstacleList::insert(float xPos, float yPos, float zPos)
{
	int sunsauce;
	int randObj = rand() % 7;	
	Obstacle* MyNode = new Obstacle(xPos, yPos, zPos, NULL);
	if (randObj==0)
	{
		sunsauce = getSunNumb();
		if (sunsauce!=0)
		{
			MyNode->setSunNum(sunsauce);
			MyNode->setObjType(SUN);
		}
	}
	if (randObj==1)
		MyNode->setObjType(CUBE);
	if (randObj==2)
		MyNode->setObjType(VMASK);
	if (randObj==3)
		MyNode->setObjType(BALL);
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
		int sunNumb = first->getSunNum();
		if(sunNumb==1)
		{
			sun1=false;
			glDisable(GL_LIGHT1);
		}
		if(sunNumb==2)
		{
			sun2=false;
			glDisable(GL_LIGHT2);
		}
		if(sunNumb==3)
		{
			sun3=false;
			glDisable(GL_LIGHT3);
		}
		first = 0;
		last = 0;
        current = 0;
	}
	else
	{
		//if (current == first) 
		//current = first->getNext();
		int sunNumb = first->getSunNum();
		if(sunNumb==1)
			sun1=false;
		if(sunNumb==2)
			sun2=false;
		if(sunNumb==3)
			sun3=false;
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

float ObstacleList::distance(float x, float y, float z, float x2, float y2, float z2)
{
	return sqrtf((x2-x)*(x2-x)+(y2-y)*(y2-y)+(z2-z)*(z2-z));
}



bool ObstacleList::CollidesAll(Player* player)
{
    if (isEmpty()) return false;
	if (first!=0)			//Verify first if the link list is not empty
	{

		if(first ==last)	//If only one obstacle in the link List, set its Z coordinates
		{
			if( (!first->getCrash()) &&
                distance(player->getXPos(),
                         player->getYPos(),
                         player->getZPos(),
                         first->getXPos(),
                         first->getYPos(),
                         first->getZPos()) <
                player->getRad() + first->getObjRad() )
            {
				first->explode();
				player->explode();
				return true;
			}
		}
		else						//If multiple obstacle in the link List then loop through the link list		
		{
			Obstacle * temp = first;

			 do{
				 if( (!temp->getCrash()) &&
                     distance(player->getXPos(),
                              player->getYPos(),
                              player->getZPos(),
                              temp->getXPos(),
                              temp->getYPos(),
                              temp->getZPos()) <
                     player->getRad() + temp->getObjRad() )
					{
						//obstacle reacts
						temp->explode();
						player->explode();
						return true;
					}
       				temp = temp->getNext();

				}while(temp!= last);

				//last obj
				if( (!last->getCrash()) &&
                    distance(player->getXPos(),
                             player->getYPos(),
                             player->getZPos(),
                             last->getXPos(),
                             last->getYPos(),
                             last->getZPos()) <
                    player->getRad()+last->getObjRad())
				{
					//obstacle reacts
					last->explode();
					player->explode();
					return true;
				}
		}

	}
	return false;
}

void ObstacleList::drawAll(int level, bool testMode)
{
    

    if (isEmpty()) return;
	if (first!=0)			//Verify first if the link list is not empty
	{

		if(first ==last)	//If only one obstacle in the link List, set its Z coordinates
		{
            first->draw(level,testMode);
		}
		else						//If multiple obstacle in the link List then loop through the link list		
		{
			Obstacle * temp = first;

			do{			
            temp->draw(level,testMode);

			temp = temp->getNext();

			}while(temp!= last);

			//For the last node in the link list
            last->draw(level,testMode);

		}
	}

}

void ObstacleList::removeAll()
{
	sun1=false;	
	sun2=false;
	sun3=false;
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
    first = 0;
    current = 0;
    last = 0;
}
