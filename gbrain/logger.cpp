#pragma once
#include "logger.h"
#include <ctime>

Logger* Logger::instance = instance;
stringstream Logger::ss;

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

	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

ostream& operator<<(Logger& logger, const char* val)
{
	logger.ss << val;
	return logger.ss;
}

ostream& operator<<(Logger& logger, streambuf* sb)
{
	logger.ss << sb;
	return logger.ss;
}

ostream& operator<<(Logger& logger, const int i)
{
	logger.ss << i;
	return logger.ss;
}

ostream& operator<<(Logger& logger, unsigned int val)
{
	logger.ss << val;
	return logger.ss;
}

ostream& operator<<(Logger& logger, long val)
{
	logger.ss << val;
	return logger.ss;
}

ostream& operator<<(Logger& logger, unsigned long val)
{
	logger.ss << val;
	return logger.ss;
}

ostream& operator<<(Logger& logger, float val)
{
	logger.ss << val;
	return logger.ss;
}

ostream& operator<<(Logger& logger, double val)
{
	logger.ss << val;
	return logger.ss;
}

ostream& operator<<(Logger& logger, long double val)
{
	logger.ss << val;
	return logger.ss;
}

ostream& operator<<(Logger& logger, void* val)
{
	logger.ss << val;
	return logger.ss;
}

ostream& operator<<(Logger& logger, ostream& (*pf)(ostream&))
{
	logger.ss << pf;
	return logger.ss;
}

ostream& operator<<(Logger& logger, ios& (*pf)(ios&))
{
	logger.ss << pf;
	return logger.ss;
}

ostream& operator<<(Logger& logger, ios_base& (*pf)(ios_base&))
{
	logger.ss << pf;
	return logger.ss;
}

ostream& operator<<(Logger& logger, bool val)
{
	logger.ss << val;
	return logger.ss;
}

ostream& operator<<(Logger& logger, short val)
{
	logger.ss << val;
	return logger.ss;
}

ostream& operator<<(Logger& logger, unsigned short val)
{
	logger.ss << val;
	return logger.ss;
}