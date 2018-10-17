/* EPN.h */

#ifndef EPN_H
#define EPN_H

#include <string>

#include "/home/charlotte/fairmq/fairmq/FairMQDevice.h"


namespace epn_to_scheduler
{

class EPN : public FairMQDevice
{
  public:
    EPN();
    virtual ~EPN();



  protected:
    bool ConditionalRun() override;

    int Id;
    uint64_t freeSlots;
    //time of sent messages in milliseconds
    float interval;
    uint64_t numEPNs;
    //float a;

    void InitTask() override;
    void sender();
    //float convert(float intervall);


};

} // namespace epn_to_scheduler

#endif
