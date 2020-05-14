#include "signalReader.h"

SignalReader::SignalReader(Rhd2000EvalBoard* evalBoard, 
    unsigned int runningTime, unsigned int samplingRate) {
    this->evalBoard = evalBoard;
    setConfig(runningTime, samplingRate);
}

void SignalReader::setConfig(unsigned int runningTime, unsigned int samplingRate) {
    if (runningTime == 0) {
        evalBoard->setContinuousRunMode(TRUE);
    }
    else {
        evalBoard->setMaxTimeStep((double)(samplingRate * runningTime) / (double)1000);
        evalBoard->setContinuousRunMode(FALSE);
    }
    evalBoard->setCableLengthFeet(Rhd2000EvalBoard::PortA, 3.0);
}

void SignalReader::run(string priority)
{
    queue<Rhd2000DataBlock> dataQueue;

    bool usbDataRead;
    evalBoard->run();
    do {
        usbDataRead = evalBoard->readDataBlocks(1, dataQueue);
        while (!dataQueue.empty()) {
            dataQueue.front().write(evalBoard->getNumEnabledDataStreams(), priority);
            dataQueue.pop();
        }
    } while (usbDataRead || evalBoard->isRunning());
}