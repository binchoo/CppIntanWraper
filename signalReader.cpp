// #include <QtCore> // used for Qt applications
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <time.h>
#include <assert.h>

using namespace std;

#include "rhd2000evalboard.h"
#include "rhd2000registers.h"
#include "rhd2000datablock.h"
#include "okFrontPanelDLL.h"

#include "signalReader.h"

SignalReader::signalReader()
{
    init();
}

void SignalReader::init(int ms, int sr)
{
    evalBoard = new Rhd2000EvalBoard;
    evalBoard->open();

    // Load Rhythm FPGA configuration bitfile (provided by Intan Technologies).
    string bitfilename;
    bitfilename = "main.bit";  // Place main.bit in the executable directory, or add a complete path to file.
    evalBoard->uploadFpgaBitfile(bitfilename);

    // Initialize board.
    evalBoard->initialize();
    evalBoard->setDataSource(0, Rhd2000EvalBoard::PortA1);

    //SampleRate1000Hz,SampleRate1250Hz,SampleRate1500Hz,SampleRate2000Hz,SampleRate2500Hz,SampleRate3000Hz,
    //SampleRate3333Hz,SampleRate4000Hz,SampleRate5000Hz,SampleRate6250Hz, SampleRate8000Hz, SampleRate10000Hz, 
    //SampleRate12500Hz, SampleRate15000Hz, SampleRate20000Hz,SampleRate25000Hz, SampleRate30000Hz
    // Select per-channel amplifier sampling rate.
    switch (sr)
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
    evalBoard->setSampleRate(Rhd2000EvalBoard::SampleRate20000Hz);

    // Now that we have set our sampling rate, we can set the MISO sampling delay
    // which is dependent on the sample rate.  We assume a 3-foot cable.
    evalBoard->setCableLengthFeet(Rhd2000EvalBoard::PortA, 3.0);

    // Let's turn one LED on to indicate that the program is running.
    int ledArray[8] = {1, 0, 0, 0, 0, 0, 0, 0};
    evalBoard->setLedDisplay(ledArray);

    // Set up an RHD2000 register object using this sample rate to optimize MUX-related
    // register settings.
    Rhd2000Registers *chipRegisters;
    chipRegisters = new Rhd2000Registers(evalBoard->getSampleRate());

    // Create command lists to be uploaded to auxiliary command slots.
    int commandSequenceLength;
    vector<int> commandList;

    // First, let's create a command list for the AuxCmd1 slot.  This command
    // sequence will create a 1 kHz, full-scale sine wave for impedance testing.
    commandSequenceLength = chipRegisters->createCommandListZcheckDac(commandList, 1000.0, 128.0); // 1000.0, 128.0
    evalBoard->uploadCommandList(commandList, Rhd2000EvalBoard::AuxCmd1, 0);
    evalBoard->selectAuxCommandLength(Rhd2000EvalBoard::AuxCmd1, 0, commandSequenceLength - 1);
    evalBoard->selectAuxCommandBank(Rhd2000EvalBoard::PortA, Rhd2000EvalBoard::AuxCmd1, 0);
    // evalBoard->printCommandList(commandList); // optionally, print command list

    // Next, we'll create a command list for the AuxCmd2 slot.  This command sequence
    // will sample the temperature sensor and other auxiliary ADC inputs.
    commandSequenceLength = chipRegisters->createCommandListTempSensor(commandList);
    evalBoard->uploadCommandList(commandList, Rhd2000EvalBoard::AuxCmd2, 0);
    evalBoard->selectAuxCommandLength(Rhd2000EvalBoard::AuxCmd2, 0, commandSequenceLength - 1);
    evalBoard->selectAuxCommandBank(Rhd2000EvalBoard::PortA, Rhd2000EvalBoard::AuxCmd2, 0);
    // evalBoard->printCommandList(commandList); // optionally, print command list

    // For the AuxCmd3 slot, we will create two command sequences.  Both sequences
    // will configure and read back the RHD2000 chip registers, but one sequence will
    // also run ADC calibration.

    // Before generating register configuration command sequences, set amplifier
    // bandwidth paramters.

    double dspCutoffFreq;
    dspCutoffFreq = chipRegisters->setDspCutoffFreq(10.0);
    cout << "Actual DSP cutoff frequency: " << dspCutoffFreq << " Hz" << endl;

    chipRegisters->setLowerBandwidth(1.0);
    chipRegisters->setUpperBandwidth(7500.0);

    commandSequenceLength = chipRegisters->createCommandListRegisterConfig(commandList, false);
    // Upload version with no ADC calibration to AuxCmd3 RAM Bank 0.
    evalBoard->uploadCommandList(commandList, Rhd2000EvalBoard::AuxCmd3, 0);

    chipRegisters->createCommandListRegisterConfig(commandList, true);
    // Upload version with ADC calibration to AuxCmd3 RAM Bank 1.
    evalBoard->uploadCommandList(commandList, Rhd2000EvalBoard::AuxCmd3, 1);

    evalBoard->selectAuxCommandLength(Rhd2000EvalBoard::AuxCmd3, 0, commandSequenceLength - 1);
    // Select RAM Bank 1 for AuxCmd3 initially, so the ADC is calibrated.
    evalBoard->selectAuxCommandBank(Rhd2000EvalBoard::PortA, Rhd2000EvalBoard::AuxCmd3, 1);
    // evalBoard->printCommandList(commandList); // optionally, print command list

    if(ms == 0){
        evalBoard->setMaxTimeStep(1000);
        evalBoard->setContinuousRunMode(TRUE);
    } else {
        evalBoard->setMaxTimeStep((sr*ms)/1000);
        evalBoard->setContinuousRunMode(FALSE);
    }

}

void SignalReader::run(char*priority)
{
    //cout << "Reading RHD2000 data..." << endl;
    evalBoard->run();

    bool usbDataRead;
    do {
        usbDataRead = evalBoard->readDataBlocks(100, dataQueue);
        while (!dataQueue.empty()) {
            dataQueue.front().write(cout, evalBoard->getNumEnabledDataStreams(),&priority)       
        }
  
    } while (usbDataRead || evalBoard->isRunning());

}