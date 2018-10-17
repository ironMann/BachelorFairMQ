

#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <string>
#include "/home/charlotte/fairmq/fairmq/FairMQDevice.h"
#include "Message.h"

namespace epn_to_scheduler
{

class Scheduler : public FairMQDevice
{
  public:
    Scheduler();
    virtual ~Scheduler();



  protected:
    bool HandleData(FairMQMessagePtr&, int);
    void receive();
    //void sender(EPNtoScheduler receivedMsg);


};

} // namespace epn_to_scheduler

#endif /* SCHEDULER_H */
