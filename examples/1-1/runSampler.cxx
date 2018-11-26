/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runFairMQDevice.h"
#include "Sampler.h"
//wir benutzen den namespace boost, um auf die program_options von boost zugreifen zu können.
namespace bpo = boost::program_options;

//die Methode addCustomOptions erhält als Eingabe die Adresse?? eines option_description datentyps mit dem Namen options. In dem Funktionsbody wird über die add_options Methode, die wahrscheinlich in boost implementiert wird, der text bzw. die anzahl der Iterationen festgelegt. 
void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
        ("text", bpo::value<std::string>()->default_value("Hello there"), "Text to send out")
        ("max-iterations", bpo::value<uint64_t>()->default_value(0), "Maximum number of iterations of Run/ConditionalRun/OnData (0 - infinite)");
}


//es wird ein FairMQDevicePtr Objekt zurückgeliefert. Als Eingabe erhält es keine ahnung was???
FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new example_1_1::Sampler();
}
