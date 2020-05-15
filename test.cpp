#include "test.h"
#include "./gbrain/intanInitializer.h"
#include "./gbrain/signalReader.h"

void test_arguments_injection();
void test_wrong_arguments_injection();
void test_valid_arguments_injection();

void test_signal_values();

void test_suite() {
	test_arguments_injection();
	test_signal_values();
	exit(1);
}

void test_arguments_injection() {
	test_wrong_arguments_injection();
	test_valid_arguments_injection();
}

void test_wrong_arguments_injection() {
	char* argv[10] = { "dummy.exe", "-s", "1", "-t", "-300", "-p", "abc", "-P", "9876"};
	int argc = 9;
	Rhd2000EvalBoard* evalBoard = new Rhd2000EvalBoard;
	IntanInitializer initializer(evalBoard);
	initializer.argumentParse(argc, (char**)argv);

	should_not_equal(initializer.samplingRateTable.at(12500), initializer.getSamplingRate());
	should_equal(0, initializer.getRuningTime());
	should_not_equal("abc", initializer.getPriority());
	should_not_equal("9876", initializer.getDataStreams());

	delete evalBoard;
}

void test_valid_arguments_injection() {

}

void test_signal_values() {

}