/**
 * epn.h
 *
 *
 *
 */

#ifndef FAIRMQEXAMPLESCHEDULERFLPEPNEPN_H
#define FAIRMQEXAMPLESCHEDULERFLPEPNEPN_H

#include "FairMQDevice.h"
#include "Message.h"
#include <time.h>
#include <iostream>
#include <string>
#include <random>
#include <thread>




namespace example_SCHEDULER_FLP_EPN
{

class epn : public FairMQDevice
{
  public:
    epn();
    virtual ~epn();
    void send(int* memory, uint64_t* numepns, int* id, uint64_t* start,const uint64_t* max);


  protected:
    int Id;
    int freeSlots;
    uint64_t maxSlots;
    uint64_t numEPNS;
    uint64_t numFLPS;
    std::map<unsigned long,int> rcvdSTFs;
    std::map<unsigned long,int>::iterator it;
    int sTF;

    const float procTime;
    const float procDev;

    uint64_t startTime;
    const uint64_t programTimeMsec; //the duration of the program.
    const unsigned intMs;






    virtual void InitTask();
    virtual bool ConditionalRun();

    std::string getChannel(char number);
    void receive();



    std::thread senderThread(int* memory, uint64_t* numepns, int* id, uint64_t* start,const uint64_t* max);


    static void MyDelayedFun(float delayWork, int* memory);
    float getDelay();

    uint64_t getHistKey();





};

}

#endif /* FAIRMQEXAMPLESCHEDULERFLPEPNEPN_H */
