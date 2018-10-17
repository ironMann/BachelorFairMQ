#include "/home/charlotte/fairmq/fairmq/runFairMQDevice.h"
#include "Scheduler.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    

}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new epn_to_scheduler::Scheduler();
}
