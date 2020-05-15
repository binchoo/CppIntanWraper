#pragma once

#include "../intan/rhd2000evalboard.h"
#include "../intan/rhd2000registers.h"
#include "../intan/rhd2000datablock.h"
#include "../intan/okFrontPanelDLL.h"
#include "../intan/rhd2000evalboard.h"
#include <map>
#include <iostream>
#include <sstream>
#include "logger.h"
using namespace std;

class IntanInitializer {

public:
    IntanInitializer(Rhd2000EvalBoard* evalBoard);
    void argumentParse(int argc, char** argv);
    void printParameters();
    unsigned int getRuningTime();
    unsigned int getSamplingRate();
    string getPriority();
    string getDataStreams();
    const static map<unsigned int, Rhd2000EvalBoard::AmplifierSampleRate> samplingRateTable;


private:

    Rhd2000EvalBoard* evalBoard;

    unsigned int runningTime;
    unsigned int samplingRate;
    string priority;
    string dataStreams;

    bool checkValidityForRunningTime(string runningTime);
    bool checkValidityForPriority(string priority);
    bool checkValidityForDataStreams(string dataStreams);

    void initIntanEvalBoard();
    void setIntanEvalBoardSamplingRate();
    void setIntanEvalBoardRegisters();
    void setIntanEvalBoardDataStreams();
};