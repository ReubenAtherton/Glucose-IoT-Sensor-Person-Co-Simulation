#include "Person.hpp"
#include "Sensor.hpp"
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	bool argFlag = false;
	bool sampleFlag = false;
	bool precisionFlag = false;
	bool simulatedFlag = false;
	bool sensorFlag = false;

	unsigned int samplingTimeA;
	unsigned int decimalPrecisionA;
	unsigned int numberOfSamples;

	unsigned int age;

	if (std::string(argv[1]) == "--sensorOnly" ||
		std::string(argv[1]) ==
			"--personOnly") { // checks the mode of operation

		if (std::string(argv[1]) ==
			"--sensorOnly") { // set variables in sensor mode
			sensorFlag = true;
			for (int argcountX = 1; argcountX < argc; argcountX++) {
				if (argc < 2) {
					argFlag = true;
					cerr << "Usage: " << argv[0]
						 << " <sampleTime> <precisionBits> "
							"<numberOfSimulatedSamples>"
						 << std::endl;
				}
				if (std::string(argv[argcountX]) == "--sampleTime") {
					sampleFlag = true;
					samplingTimeA = atoi(argv[argcountX + 1]);
				}
				if (std::string(argv[argcountX]) == "--PrecisionBits") {
					precisionFlag = true;
					decimalPrecisionA = atoi(argv[argcountX + 1]);
				}

				if (std::string(argv[argcountX]) ==
					"--numberOfSimulatedSamples") {
					simulatedFlag = true;
					numberOfSamples = atoi(argv[argcountX + 1]);
				}
			}
		}
		if (std::string(argv[1]) ==
			"--personOnly") { // sets the variables in person mode
			age = atoi(argv[2]);
		}
	} else if (std::string(argv[1]) != "--sensorOnly") {
		cerr << "Sensor Only mode not active, please enter correct parameters:"
			 << endl;
		cout << "Sample Time: ";
		cin >> samplingTimeA;
		cout << "Precision Bits: ";
		cin >> decimalPrecisionA;
		cout << "Number Of Simulated Samples: ";
		cin >> numberOfSamples;

		sampleFlag = true;
		precisionFlag = true;
		simulatedFlag = true;
		sensorFlag = true;
	} else {
		cout << "No parameters were entered, exitting..."
			 << endl; // error message
		return 0;
		EXIT_FAILURE;
	}

	// SENSOR MODE
	if (sensorFlag == true) {
		if (sampleFlag == false || precisionFlag == false ||
			simulatedFlag == false) {
			cout << "You passed the following arguments: ";
			for (int argcount = 1; argcount < argc; argcount++) {
				cout << argv[argcount] << " ";
			}
			cout << endl;
			cout << "Not all system requirements were met, please restart with "
					"correct parameters."
				 << endl;
			cout << endl << "Exitting..." << endl;
			return 0;
			EXIT_FAILURE;
		}
		cout << endl;
		// creates object in Sensor class and calls the object functions
		Sensor A("A", samplingTimeA, decimalPrecisionA);
		A.showInfo();
		A.generateSamples(numberOfSamples);
	}

	// PERSON MODE
	if (std::string(argv[1]) == "--personOnly") {
		// creates object in Person class and calls the object functions
		Person C(age);
		C.initPerson();
		C.showPersonInfo();
	}
	// EXIT_SUCCESS;
	return 0;
}