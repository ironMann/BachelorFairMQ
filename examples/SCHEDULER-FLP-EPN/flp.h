
/*
 * flp.h
 *
 */

#ifndef FAIRMQEXAMPLESCHEDULERFLPEPNFLP_H
#define FAIRMQEXAMPLESCHEDULERFLPEPNFLP_H



#include "FairMQDevice.h"
#include <sstream>

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
    int schedNum;
    uint64_t startTime;
    uint64_t programTime;
    std::stringstream amountOfLostTfs1;



    virtual void Run();
    virtual void InitTask();
    uint64_t getHistKey();
};

}

#endif /* FAIRMQEXAMPLESCHEDULERFLPEPNFLP_H */
