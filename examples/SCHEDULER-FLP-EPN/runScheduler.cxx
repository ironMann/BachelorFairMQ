

#include "runFairMQDevice.h"
#include "scheduler.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
    ("numEPNS", bpo::value<uint64_t>()->default_value(43), "number of EPNs")
    ("amountFlps", bpo::value<uint64_t>()->default_value(0), "number of Flps");

}


FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new example_SCHEDULER_FLP_EPN::scheduler();
}
