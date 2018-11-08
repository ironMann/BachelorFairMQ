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
    int counter;


    virtual void Run();
    virtual void InitTask();
};

}

#endif /* FAIRMQEXAMPLESCHEDULERFLPEPNFLP_H */
