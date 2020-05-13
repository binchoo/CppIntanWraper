


class signalReader
{
    signalReader();
    Rhd2000EvalBoard *evalBoard;

public:
    void run(char*priority);

//ms : running time (0=continuous run mode TRUE)
//sr : sampling rate
private:
    void init(int ms, int sr);
}