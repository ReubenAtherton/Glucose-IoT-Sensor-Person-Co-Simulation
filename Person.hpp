#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include<ctime>
#include<string>
#include<fstream>
#include <string>

using namespace std;

struct PersonStructure{ // inside structures you can only have variables 
	std::string time_stamp;
};

class Person {

	public:
		void setAge(unsigned int);
		unsigned int getAge();

		void initPerson();
		unsigned int generateID();
		const string getAgeRange();
		unsigned int getSampleValue();
		unsigned int getTimeWindow(string date);
		unsigned int passToTime(string hour);
		unsigned int analyseSensedData(int timeWindow, double sampleValue);

		void showPersonInfo();

		Person(unsigned int A);

	private: 
		std::ofstream personFile;
		std::ifstream sensorFile;
		std::string name;
		
		unsigned int age;
		unsigned int ID;
		unsigned int time_hour;
		int sampleValue;
		std::string time_window;
		std::string age_range;
		std::string date;
		std::string hour;
};

#endif