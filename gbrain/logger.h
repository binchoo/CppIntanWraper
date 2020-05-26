#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Logger {
private:
	stringstream ss;
	static Logger* instance;

	Logger() {
		ss = stringstream();
	};

	Logger(const Logger& other);
	
	string currentDateTime();
	
public:
	static Logger& getInstance();
	void commit(string tag);
	friend ostream& operator<< (Logger& logger, const string s);
	friend ostream& operator<< (Logger& logger, const int s);
	friend ostream& operator<< (Logger& logger, bool val);
	friend ostream& operator<< (Logger& logger, short val);
	friend ostream& operator<< (Logger& logger, unsigned short val);
	friend ostream& operator<< (Logger& logger, int val);
	friend ostream& operator<< (Logger& logger, unsigned int val);
	friend ostream& operator<< (Logger& logger, long val);
	friend ostream& operator<< (Logger& logger, unsigned long val);
	friend ostream& operator<< (Logger& logger, float val);
	friend ostream& operator<< (Logger& logger, double val);
	friend ostream& operator<< (Logger& logger, long double val);
	friend ostream& operator<< (Logger& logger, void* val);
	friend ostream& operator<< (Logger& logger, ostream& (*pf)(ostream&));
	friend ostream& operator<< (Logger& logger, ios& (*pf)(ios&));
	friend ostream& operator<< (Logger& logger, ios_base& (*pf)(ios_base&));
};
