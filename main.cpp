//----------------------------------------------------------------------------------
// main.cpp
//
// Intan Technoloies RHD2000 Rhythm Interface API
// Version 1.2 (23 September 2013)
//
// Copyright (c) 2013 Intan Technologies LLC
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any applications that
// use Intan Technologies integrated circuits, and to alter it and redistribute it
// freely.
//
// See http://www.intantech.com for documentation and product information.
//----------------------------------------------------------------------------------

#include <fcntl.h>
#include <io.h>
#include "./gbrain/intanInitializer.h"
#include "./gbrain/signalReader.h"
#include "./gbrain/logger.h"

extern void test_suite();
int main(int argc, char* argv[]) {

	_setmode(fileno(stdout), O_BINARY);
	_setmode(fileno(stdin), O_BINARY);
	
	//test_suite();

	Rhd2000EvalBoard* intanBoard = new Rhd2000EvalBoard;
	IntanInitializer intanInitializer = IntanInitializer(intanBoard);

	intanInitializer.argumentParse(argc, argv);
	unsigned int timeSteps = intanInitializer.getRuningTime();
	unsigned int samplingRate = intanInitializer.getSamplingRate();
	string priority = intanInitializer.getPriority();

	SignalReader signalReader = SignalReader(intanBoard, timeSteps, samplingRate);
	signalReader.run(priority);
}