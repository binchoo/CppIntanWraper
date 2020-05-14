// #include <QtCore> // used for Qt applications
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <time.h>
#include <assert.h>

using namespace std;

#include "../intan/rhd2000evalboard.h"
#include "../intan/rhd2000registers.h"
#include "../intan/rhd2000datablock.h"
#include "../intan/okFrontPanelDLL.h"

#include "signalReader.h"

SignalReader::SignalReader(Rhd2000EvalBoard* evalBoard, unsigned int runningTime, unsigned int samplingRate)
{
    this->evalBoard = evalBoard;
    setConfig(runningTime, samplingRate);
}

void SignalReader::setConfig(unsigned int runningTime, unsigned int samplingRate)
{
    switch (samplingRate)
    {
        case 1000:
            evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate1000Hz);
            break;
        case 2000:
            evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate2000Hz);
            break;
        case 2500:
            evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate2500Hz);
            break;
        case 3333:
            evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate3333Hz);
            break;
        case 5000:
            evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate5000Hz);
            break;
        case 8000:
            evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate8000Hz);
            break;
        case 10000:
            evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate10000Hz);
            break;
        case 12500:
            evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate12500Hz);
            break;
        case 15000:
            evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate15000Hz);
            break;
        case 20000:
            evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate20000Hz);
            break;
        case 25000:
            evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate25000Hz);
            break;
        default:
            evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate5000Hz);
            break;
    }

    evalBoard->setCableLengthFeet(Rhd2000EvalBoard::PortA, 3.0);
    if (runningTime == 0){
        evalBoard->setContinuousRunMode(TRUE);
    } else {
        evalBoard->setMaxTimeStep((samplingRate * runningTime) / 1000);
        evalBoard->setContinuousRunMode(FALSE);
    }
}

void SignalReader::run(string priority)
{
    bool usbDataRead;
    queue<Rhd2000DataBlock> dataQueue;
    evalBoard->run();
    do {
        usbDataRead = evalBoard->readDataBlocks(100, dataQueue);
        while (!dataQueue.empty()) {
            dataQueue.front().write(evalBoard->getNumEnabledDataStreams(), priority);
            dataQueue.pop();
        }
    } while (usbDataRead || evalBoard->isRunning());

}