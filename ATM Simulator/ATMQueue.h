/*
 * ATMQueue.h
 *
 */
#include "Node.h"

#ifndef ATMQUEUE_H_
#define ATMQUEUE_H_

class ATMQueue {
  // TO DO:: Fill in.
public:
  ATMQueue();
  //~ATMQueue();

  void enqueue( Node * newUser );
  void dequeue();

  Node * front;
  Node * rear;
  int queueSize;

};

#endif /* ATMQUEUE_H_ */
