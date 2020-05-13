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

#include <fstream>
#include <vector>
#include <queue>
#include <time.h>
#include <assert.h>
#include "IntanWrapperMain.h"
#include <iostream>

using namespace std;

void initIntanEvalBoard(Rhd2000EvalBoard*);

int main(int argc, char *argv[])
{

    Rhd2000EvalBoard *evalBoard = new Rhd2000EvalBoard;
    IntanWrapperMain mainer = IntanWrapperMain(evalBoard);
    mainer.argumentParse(argc, argv);
}

void initIntanEvalBoard(Rhd2000EvalBoard* evalBoard) {

    queue<Rhd2000DataBlock> dataQueue;

    evalBoard->setMaxTimeStep(120000);
    evalBoard->setContinuousRunMode(FALSE);
    evalBoard->enableDataStream(4, true);
}