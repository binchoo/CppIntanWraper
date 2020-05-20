#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Logger {
private:
	Logger() {
		ss = stringstream();
	};
	Logger(const Logger& other);
	static Logger* instance;
	string currentDateTime();
	stringstream ss;
public:
	static Logger& getInstance();
	void commit(string tag);
	friend ostream& operator<<(Logger& logger, const string s);
	friend ostream& operator<<(Logger& logger, const int s);
	friend ostream& operator<<(Logger& logger, std::ios_base& );
};
