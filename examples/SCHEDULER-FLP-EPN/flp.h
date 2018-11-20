/*
 * flp.h
 *
 */

#ifndef FAIRMQEXAMPLESCHEDULERFLPEPNFLP_H
#define FAIRMQEXAMPLESCHEDULERFLPEPNFLP_H



#include "FairMQDevice.h"

namespace example_SCHEDULER_FLP_EPN
{

class flp : public FairMQDevice
{
  public:
    flp();
    virtual ~flp();

  protected:
    int* arrayofEpns; //just declare a pointer



    const unsigned msBetweenSubtimeframes;
    int amountEPNs; //amount of epns in scheduler
    uint64_t numEPNS;
    int socket;
    int myId;
    int sTF;
    uint64_t startTime;
    const uint64_t progTime;


    virtual void Run();
    virtual void InitTask();
    uint64_t getHistKey();
};

}

#endif /* FAIRMQEXAMPLESCHEDULERFLPEPNFLP_H */
