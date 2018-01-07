/*
 * ATM.cpp
 *
 */

#include "ATM.h"
//#include "ATMQueue.h"

// TO DO:: Fill in.
ATM::ATM()
{
  //customerTtime = -1;
  isOpen = 1;
  customersProcessed = 0;
  lineWaitTime = 0;
}

void ATM::insertCustomer( Customer * newUser )
{
  Node * tmp = new Node();
  tmp -> user.ttime = newUser -> ttime;
  tmp -> user.atime = newUser -> atime;

  line.enqueue( tmp );
  isOpen = 0;
  //customerTtime = line.front->user.ttime;
}

void ATM::processCustomer( int currentMinute )
{
  if ( isOpen == 1 )
  {
    return;
  }
  if ( line.front->user.ttime > 0 )
  {
    line.front->user.ttime--;
  }

  if ( line.front->user.ttime == 0 )
  {

    line.dequeue();
    /*if ( line.queueSize > 1 )
    {
      lineWaitTime = lineWaitTime + (currentMinute - line.front->user.atime);
    }*/
    customersProcessed++;
    if ( line.front == 0 )
    {
      isOpen = 1;
    }
  }
}

int ATM::lineSize()
{
  return line.queueSize;
}

int ATM::ttimeLeft()
{
  return line.front->user.ttime;
}
