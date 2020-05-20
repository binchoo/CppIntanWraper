#include "logger.h"
#include <ctime>

Logger* Logger::instance = nullptr;

Logger& Logger::getInstance() {
	if (Logger::instance == nullptr) {
		Logger::instance = &Logger();
	}
	return *Logger::instance;
}

void Logger::commit(string tag) {
	ofstream file = ofstream("log.txt", ios::app);
	file << '[' << tag << '|' << currentDateTime() << ']' << ss.str() << endl;
	ss.clear();
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

ostream& operator<<(Logger& logger, const string s)
{
	logger.ss << s ;
	return logger.ss;
}

ostream& operator<<(Logger& logger, const int i)
{
	logger.ss << i;
	return logger.ss;
}

ostream& operator<<(Logger& logger, std::ios_base& base)
{
	logger.ss << base;
	return logger.ss;
}) 