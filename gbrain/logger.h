#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Logger {
private:
	Logger() {};
	Logger(const Logger& other);
	static Logger* instance;

public:
	static Logger* getInstance();
	void log(string tag, string message);
	string currentDateTime();
};
