#include "logger.h"
#include <ctime>

Logger* Logger::instance = nullptr;

Logger* Logger::getInstance() {
	if (Logger::instance == nullptr) {
		Logger::instance = &Logger();
	}
	return Logger::instance;
}

void Logger::log(string tag, string message) {
	ofstream file = ofstream("log.txt", ios::app);
	file << '[' << tag << '|' << currentDateTime() << ']' << message << endl;
	file.close();
}

string Logger::currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];

	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}