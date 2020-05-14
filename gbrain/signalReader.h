#include "../intan/rhd2000evalboard.h"
#include "../intan/rhd2000datablock.h"
#include "../intan/okFrontPanelDLL.h"
#include "intanInitializer.h"
#include "logger.h"

class SignalReader {

public:
    SignalReader(Rhd2000EvalBoard* evalBoard, 
        unsigned int runningTime, unsigned int samplingRate);
    void run(string priority);

private:
    Rhd2000EvalBoard* evalBoard;
    //runningTime : ms
    void setConfig(unsigned int runningTime, unsigned int samplingRate);
};