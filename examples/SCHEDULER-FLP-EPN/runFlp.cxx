#include "runFairMQDevice.h"
#include "flp.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options();

}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new example_SCHEDULER_FLP_EPN::flp();
}
