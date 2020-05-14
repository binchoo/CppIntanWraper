#pragma once

#include "../intan/rhd2000evalboard.h"
#include "../intan/rhd2000registers.h"
#include "../intan/rhd2000datablock.h"
#include "../intan/okFrontPanelDLL.h"
#include "../intan/rhd2000evalboard.h"
#include <map>

using namespace std;

class IntanWrapperMain {
public:

    IntanWrapperMain(Rhd2000EvalBoard* evalBoard);
    void* argumentParse(int argc, char** argv);
    void execute(void (*callback)());
    void printValues();
    unsigned int getTimeSteps();
    unsigned int getSamplingRate();
    string getPriority();
    string getDataStreams();
    

private:
    Rhd2000EvalBoard* evalBoard;

    unsigned int timeSteps;
    unsigned int samplingRate;
    string priority;
    string dataStreams;

    const map<unsigned int, Rhd2000EvalBoard::AmplifierSampleRate> samplingRateTable {
        { 1000, Rhd2000EvalBoard::AmplifierSampleRate::SampleRate1000Hz },
        { 1250, Rhd2000EvalBoard::AmplifierSampleRate::SampleRate1250Hz },
        { 1500, Rhd2000EvalBoard::AmplifierSampleRate::SampleRate1500Hz },
        { 2000, Rhd2000EvalBoard::AmplifierSampleRate::SampleRate2000Hz },
        { 2500, Rhd2000EvalBoard::AmplifierSampleRate::SampleRate2500Hz },
        { 3000, Rhd2000EvalBoard::AmplifierSampleRate::SampleRate3000Hz },
        { 3333, Rhd2000EvalBoard::AmplifierSampleRate::SampleRate3333Hz },
        { 4000, Rhd2000EvalBoard::AmplifierSampleRate::SampleRate4000Hz },
        { 5000, Rhd2000EvalBoard::AmplifierSampleRate::SampleRate5000Hz },
        { 6250, Rhd2000EvalBoard::AmplifierSampleRate::SampleRate6250Hz },
        { 8000, Rhd2000EvalBoard::AmplifierSampleRate::SampleRate8000Hz },
        { 10000,Rhd2000EvalBoard::AmplifierSampleRate::SampleRate10000Hz },
        { 12500,Rhd2000EvalBoard::AmplifierSampleRate::SampleRate12500Hz },
        { 15000,Rhd2000EvalBoard::AmplifierSampleRate::SampleRate15000Hz },
        { 20000,Rhd2000EvalBoard::AmplifierSampleRate::SampleRate20000Hz },
        { 25000,Rhd2000EvalBoard::AmplifierSampleRate::SampleRate25000Hz },
        { 30000,Rhd2000EvalBoard::AmplifierSampleRate::SampleRate30000Hz },
    };

    bool checkValidityForPriority(string priority);
    bool checkValidityForDataStreams(string dataStreams);

    void initIntanEvalBoard();

    void setIntanEvalBoardSamplingRate();
    void setIntanEvalBoardRegisters();
    void setIntanEvalBoardDataStreams();
};