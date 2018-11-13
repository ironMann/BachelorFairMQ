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


    virtual void Run();
    virtual void InitTask();
};

}

#endif /* FAIRMQEXAMPLESCHEDULERFLPEPNFLP_H */
