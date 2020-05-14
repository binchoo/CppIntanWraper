#pragma once
#include "intanInitializer.h"
#include "../getopt/getopt.h"

using namespace std;

const map<unsigned int, Rhd2000EvalBoard::AmplifierSampleRate> IntanInitializer::samplingRateTable = {
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

IntanInitializer::IntanInitializer(Rhd2000EvalBoard* evalBoard) {
	runningTime = 1000;
	samplingRate = 12500;
	priority = "tsc";
	dataStreams = "04";
	this->evalBoard = evalBoard;
}

void IntanInitializer::initIntanEvalBoard() {	
	evalBoard->open();

	string bitFileName = "main.bit";
	evalBoard->uploadFpgaBitfile(bitFileName);
	
	evalBoard->initialize();

	evalBoard->setDataSource(0, Rhd2000EvalBoard::PortA1);

	setIntanEvalBoardSamplingRate();
	setIntanEvalBoardRegisters();
	setIntanEvalBoardDataStreams();
}

void IntanInitializer::setIntanEvalBoardSamplingRate() {
	if (samplingRateTable.find(samplingRate) == samplingRateTable.end())
		samplingRate = 12500;
	evalBoard->setSampleRate(samplingRateTable.at(samplingRate));
}

void IntanInitializer::setIntanEvalBoardRegisters() {
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

void IntanInitializer::setIntanEvalBoardDataStreams() {
	for (char& ch : dataStreams) {
		int dataStream = ch - '0';
		evalBoard->enableDataStream(dataStream, true);
	}
}

bool IntanInitializer::checkValidityForPriority(string priority) {
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

bool IntanInitializer::checkValidityForDataStreams(string dataStreams) {
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

void IntanInitializer::argumentParse(int argc, char** argv) {
	char opt;
	while ((opt = getopt(argc, argv, "s:t:p:P:a")) != -1) {
		switch (opt) {
			case 's':
				samplingRate = atoi(optarg);
				break;
			case 't':
				runningTime = atoi(optarg);
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
}

void IntanInitializer::printParameters() {
	cout << "Time Steps = " << runningTime << endl;
	cout << "Sampling Rate = " << samplingRate << endl;
	cout << "Priority = " << priority << endl;
	cout << "DataStreams = " << dataStreams << endl;
}

unsigned int IntanInitializer::getTimeSteps() {
	return runningTime;
}

unsigned int IntanInitializer::getSamplingRate() {
	return samplingRate;
}

string IntanInitializer::getPriority() {
	return priority;
}

string IntanInitializer::getDataStreams() {
	return dataStreams;
}