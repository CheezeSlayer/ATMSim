/*
 * ATM.h
 *
 */

#include "Customer.h"
#include "ATMQueue.h"
#ifndef ATM_H_
#define ATM_H_

class ATM {
  // TO DO:: Fill in.
public:
  ATM();
  //~ATM();

  void insertCustomer( Customer * newUser );
  void processCustomer ( int currentMinute );
  int lineSize();
  int ttimeLeft();

  //int customerTtime;
  int customersProcessed;
  bool isOpen;
  int lineWaitTime;
  ATMQueue line;
};

#endif /* ATM_H_ */
