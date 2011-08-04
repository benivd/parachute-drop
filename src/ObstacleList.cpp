#include "ObstacleList.h"

// Add a random obstacle at the head
void ObstacleList::add()
{
    Obstacle *temp;
    temp = new Obstacle;
    last->setNext(temp);
    if (first != NULL);
        setFirst(temp);

    //Obstacle newObs(last);
    //setLast(&newObs);
    //if (first != NULL)
    //    setFirst(&newObs);
}

// Remove the tail
void ObstacleList::remove()
{
    //setFirst( first->getNext() );

    Obstacle *temp;
    temp = (Obstacle*)malloc(sizeof(Obstacle));
    temp = first;
    first = temp->getNext();
    free(temp);
}

// Draw all obstacles
void ObstacleList::draw()
{
    Obstacle* temp = first;
    while (temp != NULL)
    {
        temp->draw();
        temp = temp->getNext();
    }
}
