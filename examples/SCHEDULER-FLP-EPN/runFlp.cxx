#include "runFairMQDevice.h"
#include "flp.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
      ("amountEPNs", bpo::value<unsigned>()->default_value(0), "number of the EPNs in the schedule");

}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new example_SCHEDULER_FLP_EPN::flp();
}
