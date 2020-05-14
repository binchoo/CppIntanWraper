#include "logger.h"
#include <ctime>

Logger* Logger::instance = nullptr;

Logger* Logger::getInstance() {
	if (Logger::instance == nullptr) {
		Logger::instance = &Logger();
	}
	return Logger::instance;
}

void Logger::log(string tag, string message)
{
	ofstream file("log.txt");
	file << '[' << tag << '|' << currentDateTime() << ']' << message << endl;
	file.close();
}

string Logger::currentDateTime() {
	time_t now = time(0); //현재 시간을 time_t 타입으로 저장
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct); // YYYY-MM-DD.HH:mm:ss 형태의 스트링
	return buf;
}