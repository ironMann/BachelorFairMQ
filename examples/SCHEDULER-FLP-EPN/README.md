Constants in the program that can be modified:

  1. Class Scheduler:

    - const historyMaxMs : the amount of time an update is present in the history
    - const aliveTimeMs : the time the program is running
    - const msBetweenSubtimeframes : the interval in ms between sending two subtimeframes
    - const intervalFLPs : the interval in ms in which the scheduler needs to send the schedule to all FLPs
    - numEPNS : number of EPNs
    - numFLPS : number of FLPs
    - amountEPNs : number of EPNs that are in the schedule

 2. Class Flp:

    - const msBetweenSubtimeframes : the interval in ms between sending two subtimeframes
    - amount EPNs : the amount of epns in the schedule
    - numEPNS : number of EPNS
    - const progTime : the time the program is running

 3.Class Epn:

    - maxSlots : maximum amount of free memory
    - numEPNS : number of EPNs
    - numFLPS : number of FLPs
    - const procTime : mean of processing time
    - const procDev : standard deviation of processing time
    - const programTimeMsec : the time the program is running
