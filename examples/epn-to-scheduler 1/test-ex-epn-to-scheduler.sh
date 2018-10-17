#!/bin/bash

export FAIRMQ_PATH=/home/charlotte/fairmq/fairmq

transport="zeromq"

if [[ $1 =~ ^[a-z]+$ ]]; then
    transport=$1
fi

# setup a trap to kill everything if the test fails/timeouts
trap 'kill -TERM $EPN_PID; kill -TERM $SCHEDULER_PID; wait $EPN_PID; wait $SCHEDULER_PID;' TERM

EPN="fairmq-ex-epn-to-scheduler-EPN"
EPN+=" --id EPN1"
EPN+=" --rate 1"
EPN+=" --transport $transport"
EPN+=" --verbosity veryhigh"
EPN+=" --control static --color false"
EPN+=" --max-iterations 1"
EPN+=" --channel-config name=data,type=push,method=bind,address=tcp://*:5555,rateLogging=0"
/home/charlotte/fairmq/examples/epn-to-scheduler/$EPN &
EPN_PID=$!

SCHEDULER="fairmq-ex-epn-to-scheduler-scheduler"
SCHEDULER+=" --id scheduler1"
SCHEDULER+=" --transport $transport"
SCHEDULER+=" --verbosity veryhigh"
SCHEDULER+=" --control static --color false"
SCHEDULER+=" --max-iterations 1"
SCHEDULER+=" --channel-config name=data,type=pull,method=connect,address=tcp://localhost:5555,rateLogging=0"
/home/charlotte/fairmq/examples/epn-to-scheduler/$SCHEDULER &
SCHEDULER_PID=$!

# wait for EPN and scheduler to finish
wait $EPN_PID
wait $SCHEDULER_PID
