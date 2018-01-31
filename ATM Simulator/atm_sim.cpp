#include <iostream>
#include "ATM.h"
//#include "ATMQueue.h"
//#include "Customer.h"
//#include "Node.h"

using namespace std;

int getSimParameters(int &M, int &N, int &C, int *&atime_list, int *&ttime_list);
void displaySimResults(int wait, int C);

void printLine ( ATM machine )
{
  Node * printNode = new Node();
  printNode = machine.line.front;

  while ( printNode != NULL )
  {
    cout << printNode -> user.atime << " " << printNode -> user.ttime << endl;
    printNode = printNode -> next;
  }
}

int shortestATM ( ATM * ATMarray , int arraySize )
{
  int index = 0;
  int shortestATM = 0;
  for ( index = 0; index < arraySize; index++ )
  {
    if ( ATMarray[index].lineSize() == 0 )
    {
      shortestATM = index;
      return shortestATM;
    }
    if ( ATMarray[index].lineSize() < ATMarray[shortestATM].lineSize() )
    {
      shortestATM = index;
    }
  }
  return shortestATM;
}

void printTimes( int *atime_list , int *ttime_list , int size )
{
  int index = 0;
  for ( index = 0; index < size; index++ )
  {
    cout << "atime: " << atime_list[index] << " ttime: " << ttime_list[index] << endl;
  }
}

void listATMs ( ATM * ATMarray , int size , int currentMinute )
{
  int index = 0;
  for ( index = 0; index < size; index++ )
  {
    cout << "ATM: " << index << endl;
    //cout << "Status: " << ATMarray[index].isOpen << endl;
    //cout << "Queue Size: " << ATMarray[index].line.queueSize << endl;
    if ( ATMarray[index].line.front != NULL )
    {
      cout << "Front atime: " << ATMarray[index].line.front->user.atime << endl;
    //cout << "Line Wait Time: " << ATMarray[index].lineWaitTime << endl;//<< currentMinute - ( ATMarray[index].line.front->user.atime) << endl;
      printLine ( ATMarray[index] );
    }
    cout << endl;
  }
}
int main () {
  // TO DO:: Rename these
  int simMinutes;
  int numATMs;
  int numCustomers;
  int *atime_list, *ttime_list;

  // Total wait time for all customers in the simulation.
  int total_wait_time = 0;

  // Input code to read simulation parameters
  int param_err = getSimParameters(simMinutes, numATMs, numCustomers, atime_list, ttime_list);
  if (param_err) {
    cerr << "Error in simulation parameters." << endl;
    return -1;
  }
  // TO DO:: Your simulation code goes here.

  int customersInLine = 0;

  ATM * ATMarray;
  ATMarray = new ATM[numATMs];
  int atmIndex = 0;

  int currentMinutes = 0;
  int customersProcessed = 0;
  int timeIndex = 0;
  int listIndex = 0;
  int shortestLine = 0;

  int queueSizes[numATMs];

  while ( (currentMinutes < simMinutes) || (customersProcessed < numCustomers) )
  {
    if ( currentMinutes < simMinutes && customersProcessed < numCustomers )
    {
      for ( timeIndex = 0; timeIndex < numCustomers; timeIndex++ )
      {
          if ( atime_list[timeIndex] == currentMinutes )
          {
            Customer * newUser = new Customer();
            newUser -> atime = atime_list[timeIndex];
            newUser -> ttime = ttime_list[timeIndex];

            shortestLine = shortestATM( ATMarray , numATMs );
            ATMarray[shortestLine].insertCustomer( newUser );
          }
      }
      //cout << "Iteration: " << timeIndex << " at time " << currentMinutes << endl;
      //listATMs( ATMarray , numATMs );
    }

    //cout << "Time " << currentMinutes << " Pre-Process" << endl;
    //listATMs( ATMarray , numATMs , currentMinutes );

    //cout << "Time: " << currentMinutes << " Queue Sizes" << endl;
    for ( atmIndex = 0; atmIndex < numATMs; atmIndex++ )
    {
      queueSizes[atmIndex] = ATMarray[atmIndex].line.queueSize;
      //cout << queueSizes[atmIndex] << " ";
    }
    //cout << endl;

    for ( atmIndex = 0; atmIndex < numATMs; atmIndex++ )
    {
      //cout << "Process: " << atmIndex << endl;
      ATMarray[atmIndex].processCustomer( currentMinutes );
      //customersProcessed = 0;
      //ATMarray[atmIndex].customersProcessed = 0;
    }

    currentMinutes++;

    for ( atmIndex = 0; atmIndex < numATMs; atmIndex++ )
    {
      if ( ATMarray[atmIndex].line.queueSize > 0 )
      {
        //cout << "Updated Total Wait Time at Time: " << currentMinutes << endl;
        if (  ATMarray[atmIndex].line.queueSize != queueSizes[atmIndex] )
        {
          total_wait_time = total_wait_time + (currentMinutes - ATMarray[atmIndex].line.front->user.atime);
        }
      }
    }
    //cout << endl;
    //cout << "Time: " << currentMinutes << " Total Wait Time: " << total_wait_time << endl;

/*
    cout << "Time: " << currentMinutes << endl;
    for ( atmIndex = 0; atmIndex < numATMs; atmIndex++ )
    {
      cout << "ATM: " << atmIndex << " Queue Size: " << ATMarray[atmIndex].line.queueSize << endl;//total_wait_time = total_wait_time + ATMarray[atmIndex].lineWaitTime;
    }
*/
    for ( atmIndex = 0; atmIndex < numATMs; atmIndex++ )
    {
      customersProcessed = customersProcessed + ATMarray[atmIndex].customersProcessed;
    }
    //cout << "Time: " << currentMinutes << " Processed: "<< customersProcessed << endl;
    //cout << "Time: " << currentMinutes << " Post-Process" << endl;
    //listATMs( ATMarray , numATMs , currentMinutes );
    //cout << "Customers Processed: " << customersProcessed << endl;

    if ( customersProcessed >= numCustomers )
    {
      break;
    }
    customersProcessed = 0;

    //customersProcessed++;

  }

  //total_wait_time = total_wait_time * numCustomers;
  // Display statistics on the simulation.
  displaySimResults(total_wait_time, numCustomers);
  // Return total_wait_time, will be used by test script.
  return total_wait_time;
}



// Read the simulation parameters from standard input (cin).
// Parameters:
// M: minutes to run simulation
// N: number of ATMs
// C: number of customers
// atime_list: array of customer arrival times
// ttime_list: array of customer transaction times
//    customer i arrives at time atime_list[i] and performs a transaction that takes ttime_list[i] minutes
//
// All parameters are pass-by-reference (note & character).  This means assignments in this function will affect value from calling function
//
// Return value:
// returns 0 if successful read of input
// non-zero values used to denote failure
//   1: simulation time < 1
//   2: number of ATMs < 1
//   3: number of customers < 1
//   4: a customer's transaction time < 1
//   5: customer list is not sorted by arrival time
//   6: customer arrival time later than simulation end time
int getSimParameters(int &simMinutes, int &numATMs, int &numCustomers, int *&atime_list, int *&ttime_list) {
  // Code to read simulation parameters.
  cout << "Run an ATM simulation" << endl;

  cout << "Enter the number of minutes" << endl;
  cin >> simMinutes;
  // Check input validity.
  if (simMinutes < 1) {
    cerr << "Simulation for invalid length of time." << endl;
    return 1;
  }


  cout << "Enter the number of ATMs" << endl;
  cin >> numATMs;
  // Check input validity.
  if (numATMs < 1) {
    cerr << "Simulation for invalid number of ATMs." << endl;
    return 2;
  }


  // Read customer list
  cout << "Enter the number of customers" << endl;
  cin >> numCustomers;
  if (numCustomers < 1) {
    cerr << "Simulation for invalid number of customers." << endl;
    return 3;
  }
  // Allocate memory for customer list.
  atime_list = new int [numCustomers];
  ttime_list = new int [numCustomers];

  // Read C customers
  int atime = -1;
  int prevatime = -1;
  int ttime = 0;
  for (int i=0; i<numCustomers; i++) {
    cout << "Enter customer arrival and transaction time." << endl;
    cin >> atime;
    cin >> ttime;

    // Check input validity.
    if (ttime < 1) {
      cerr << "Invalid transaction time." << endl;
      return 4;
    }
    if (atime < prevatime) {
      cerr << "Arrival times not sorted." << endl;
      return 5;
    }
    if (atime >= simMinutes) {
      cerr << "Arrival time later than simulation end time." << endl;
      return 6;
    }
    prevatime = atime;

    atime_list[i] = atime;
    ttime_list[i] = ttime;
  }

  // All went well, return 0.
  return 0;
}


// Display statistics on the simulation.
// wait: Total wait time of all customers in simulation.
// C: total number of customers in simulation.
void displaySimResults(int wait, int numCustomers) {
  cout << "Simulation results" << endl;
  cout << "Number of customers: " << numCustomers << endl;
  cout << "Total wait time: " << wait << endl;
  cout << "Average wait time: " << ((double) wait)/((double) numCustomers) << endl;
}
