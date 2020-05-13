class SignalReader
{
public:
    SignalReader(Rhd2000EvalBoard* evalBoard, unsigned int runningTime, unsigned int samplingRate);
    void run(string priority);

    //ms : running time (0=continuous run mode TRUE)
    //sr : sampling rate
private:
    Rhd2000EvalBoard* evalBoard;
    void setConfig(unsigned int runningTime, unsigned int samplingRate);
};