#!/bin/bash

export FAIRMQ_PATH=/home/charlotte/fairmq/fairmq

exepntoschedulerconfig="/home/charlotte/fairmq/examples/epn-to-scheduler/ex-epn-to-scheduler.json"

file="/home/charlotte/fairmq/examples/epn-to-scheduler/file.txt"

EPN1="fairmq-ex-epn-to-scheduler-EPN"
EPN1+=" --id EPN1"
EPN1+=" --rate 31.25"
EPN1+=" --myid 4"
EPN1+=" --numEPNS 2"
EPN1+=" --interval 32"
EPN1+=" --mq-config $exepntoschedulerconfig"
EPN1+=" --config-key EPN"
#EPN1+=" --channel-config name=data,type=push,method=bind,address=tcp://localhost:5556,rateLogging=0"
xterm -geometry 80x23+0+0 -hold -e /home/charlotte/fairmq/examples/epn-to-scheduler/$EPN1 &

EPN2="fairmq-ex-epn-to-scheduler-EPN"
EPN2+=" --id EPN2"
EPN2+=" --rate 31.25"
EPN2+=" --myid 5"
EPN2+=" --numEPNS 2"
EPN2+=" --interval 32"
EPN2+=" --mq-config $exepntoschedulerconfig"
EPN2+=" --config-key EPN"
#EPN2+=" --channel-config name=data,type=push,method=bind,address=tcp://localhost:5555,rateLogging=5"
xterm -geometry 80x23+0+330 -hold -e /home/charlotte/fairmq/examples/epn-to-scheduler/$EPN2 &

SCHEDULER="fairmq-ex-epn-to-scheduler-scheduler"
SCHEDULER+=" --id scheduler1"
SCHEDULER+=" --rate 31.25"
SCHEDULER+=" --log-to-file $file"
SCHEDULER+=" --mq-config $exepntoschedulerconfig"
#SCHEDULER+=" --channel-config name=data,type=pull,method=connect,address=tcp://*:5555,rateLogging=5"
xterm -geometry 80x23+500+0 -hold -e /home/charlotte/fairmq/examples/epn-to-scheduler/$SCHEDULER &


