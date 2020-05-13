#pragma once

#include "IntanWrapperMain.h"
#include "getopt.h"

#include <iostream>
using namespace std;

IntanWrapperMain::IntanWrapperMain(Rhd2000EvalBoard* evalBoard) {
	timeSteps = 1000;
	samplingRate = 12500;
	priority = "tsc";
	dataStreams = "0415";
	this->evalBoard = evalBoard;
}

void IntanWrapperMain::initIntanEvalBoard() {
	
	string bitFileName = "main.bit";

	evalBoard->open();
	evalBoard->uploadFpgaBitfile(bitFileName);
	evalBoard->initialize();

	evalBoard->setDataSource(0, Rhd2000EvalBoard::PortA1);

	setIntanEvalBoardSamplingRate();
	setIntanEvalBoardRegisters();
	setIntanEvalBoardDataStreams();
}

void IntanWrapperMain::setIntanEvalBoardSamplingRate() {
	try {
		evalBoard->setSampleRate(samplingRateTable.at(samplingRate));

	}
	catch (exception& e) {
		samplingRate = 12500;
		evalBoard->setSampleRate(samplingRateTable.at(samplingRate));
	}
}

void IntanWrapperMain::setIntanEvalBoardRegisters() {
	vector<int> commandList;
	int commandSequenceLength;
	
	Rhd2000Registers* chipRegisters = new Rhd2000Registers(evalBoard->getSampleRate());

	commandSequenceLength = chipRegisters->createCommandListZcheckDac(commandList, 1000.0, 128.0);
	evalBoard->uploadCommandList(commandList, Rhd2000EvalBoard::AuxCmd1, 0);
	evalBoard->selectAuxCommandLength(Rhd2000EvalBoard::AuxCmd1, 0, commandSequenceLength - 1);
	evalBoard->selectAuxCommandBank(Rhd2000EvalBoard::PortA, Rhd2000EvalBoard::AuxCmd1, 0);

	commandSequenceLength = chipRegisters->createCommandListTempSensor(commandList);
	evalBoard->uploadCommandList(commandList, Rhd2000EvalBoard::AuxCmd2, 0);
	evalBoard->selectAuxCommandLength(Rhd2000EvalBoard::AuxCmd2, 0, commandSequenceLength - 1);
	evalBoard->selectAuxCommandBank(Rhd2000EvalBoard::PortA, Rhd2000EvalBoard::AuxCmd2, 0);

	chipRegisters->setDspCutoffFreq(10.0);
	chipRegisters->setLowerBandwidth(1.0);
	chipRegisters->setUpperBandwidth(7500.0);

	commandSequenceLength = chipRegisters->createCommandListRegisterConfig(commandList, false);
	evalBoard->uploadCommandList(commandList, Rhd2000EvalBoard::AuxCmd3, 0);
	commandSequenceLength = chipRegisters->createCommandListRegisterConfig(commandList, true);
	evalBoard->uploadCommandList(commandList, Rhd2000EvalBoard::AuxCmd3, 1);
	evalBoard->selectAuxCommandLength(Rhd2000EvalBoard::AuxCmd3, 0, commandSequenceLength - 1);
	evalBoard->selectAuxCommandBank(Rhd2000EvalBoard::PortA, Rhd2000EvalBoard::AuxCmd3, 1);
}

void IntanWrapperMain::setIntanEvalBoardDataStreams() {
	for (char& ch : dataStreams) {
		int dataStream = ch - '0';
		evalBoard->enableDataStream(dataStream, true);
	}
}

bool IntanWrapperMain::checkValidityForPriority(string priority) {
	static const string validCharacters = "tsc";
	bool result = true;
	for (char& ch : priority) {
		if (validCharacters.find(ch) == string::npos) {
			result = false;
			break;
		}
	}
	return result;
}

bool IntanWrapperMain::checkValidityForDataStreams(string dataStreams) {
	static const string validCharacters = "0415";
	int result = true;
	for (char& ch : dataStreams) {
		if (validCharacters.find(ch) == string::npos) {
			result = false;
			break;
		}
	}
	return result;
}

void* IntanWrapperMain::argumentParse(int argc, char** argv) {
	char opt;
	while ((opt = getopt(argc, argv, "s:t:p:P:a")) != -1) {
		switch (opt) {
			case 's':
				samplingRate = atoi(optarg);
				break;
			case 't':
				timeSteps = atoi(optarg);
				break;
			case 'p':
				if (checkValidityForPriority(string(optarg)))
					priority = string(optarg);
				else
					cout << "invalid value is set to priority: " << optarg << endl
						<< "default priority is: " << priority << endl;
				break;
			case 'P':
				if (checkValidityForDataStreams(string(optarg)))
					dataStreams = string(optarg);
				else
					cout << "invalid value is set to datastreams: " << optarg << endl
					<< "default datastremas are: " << dataStreams << endl;
				break;
			case 'a':
				break;
		}
	}

	initIntanEvalBoard();
	return nullptr;
}

void IntanWrapperMain::execute(void (*callback)()) {
	callback();
}

void IntanWrapperMain::printValues() {
	cout << "Time Steps = " << timeSteps << endl;
	cout << "Sampling Rate = " << samplingRate << endl;
	cout << "Priority = " << priority << endl;
	cout << "DataStreams = " << dataStreams << endl;
}

unsigned int IntanWrapperMain::getTimeSteps()
{
	return timeSteps;
}

unsigned int IntanWrapperMain::getSamplingRate()
{
	return samplingRate;
}

string IntanWrapperMain::getPriority()
{
	return priority;
}

string IntanWrapperMain::getDataStreams()
{
	return dataStreams;
}
