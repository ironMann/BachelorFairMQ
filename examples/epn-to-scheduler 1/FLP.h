/* FLP.h */

#ifndef FLP_H
#define FLP_H

#include <string>

#include "/home/charlotte/fairmq/fairmq/FairMQDevice.h"

namespace epn_to_scheduler
{

class FLP : public FairMQDevice
{
  public:
    FLP();
    virtual ~FLP();



  protected:
    bool ConditionalRun() override;


    void InitTask() override;
    void receive();


};

} // namespace epn_to_scheduler

#endif
