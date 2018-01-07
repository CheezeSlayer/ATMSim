/*
 * ATMQueue.cpp
 *
 */

#include "ATMQueue.h"
#include "Node.h"
ATMQueue::ATMQueue()
{
  front = 0;
  rear = 0;
  queueSize = 0;
}

void ATMQueue::enqueue( Node * newUser )
{
  if ( front == 0 && rear == 0 )
  {
    front = newUser;
    rear = newUser;
  }
  else
  {
      rear->next = newUser;
      rear = rear->next;
  }
  queueSize++;
}

void ATMQueue::dequeue()
{
  Node * tmp = new Node();

  if ( front != 0 )
  {
    tmp = front;
    front = front -> next;
    delete tmp;
    if ( front == 0 )
    {
      rear = 0;
    }
    queueSize--;
  }

}
