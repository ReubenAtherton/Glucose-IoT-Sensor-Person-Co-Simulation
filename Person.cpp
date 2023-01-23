#include "Person.hpp"
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <fstream>
#include <stdlib.h>
#include <iomanip> 
#include <string>
#include <sstream>

using namespace std;

void Person::setAge(unsigned int A){
	age = A;
}
unsigned int Person::getAge(){
	return age;
}

void Person::initPerson() {
cout << "Person Data is initialising:" << endl;
	float progress = 0.0;
	while (progress <= 1.0) {
		int barWidth = 70;

		cout << "[";
	    	int pos = barWidth * progress;
	    	for (int i = 0; i < barWidth; ++i) {
	        	if (i < pos) std::cout << "=";
	        	else if (i == pos) std::cout << ">";
	        	else std::cout << " ";
			usleep(50);
	    	}
	    	cout << "] " << (int(progress * 100.0) == 99 ? 100 : int(progress * 100.0)) << " %\r";
	    	cout.flush();
	
	    progress += 0.01; // for progress demonstration only
	}	
	cout << endl;
}

unsigned int Person::generateID(){ //generates random ID number
	srand(time(NULL));
	ID = rand() % 10000;
	return ID;
}
const string Person::getAgeRange(){ //passes the inputted age and provides general age range 
	if(age <= 6)
		return "(0-6 years)";
	else if(7 <= age && age <= 16)
		return "(7-16 years)";
	else if(17<= age && age <= 55)
		return "(17-38 years)";
	else if(55 < age)
		return "(55+ years)";
	return "";
}

void Person::showPersonInfo(){ //

	string date;
	int sampleTime, timeWindow;
	double sampleValue;
	string line;
	int count_input;

	double NC = 0; // night critical count 
	double NNC = 0; // night non-critical count
	double MC = 0; // morning critical count
	double MNC = 0; // morning non-critical count 
	double DC = 0; // day critical count
	double DNC = 0; // day non_critical count 
	double EC = 0; // evening critical count 
	double ENC = 0; // evening non-critical count 

	ifstream sensorFile("sensorA.dat", ios::app);

	while(getline(sensorFile, line)) {
		stringstream linestream(line);
		linestream >> date >> sampleValue >> sampleTime;

		timeWindow = passToTime(date);
		count_input = analyseSensedData(timeWindow, sampleValue);

		switch(count_input) {
			// add to critical and non critical counts 
			case 0: NC++;
					break;
			case 1: NNC++;
					break;
			case 2: MC++;
					break;
			case 3: MNC++;
					break; 
			case 4: DC++;
					break;
			case 5: DNC++;
					break;
			case 6: EC++;
					break;
			case 7: ENC++;
					break;
		}
	}
	ofstream personFile;
	personFile.open("analysis.txt", ios::app);
	string error_msg = "No samples recorded within this time window";

	ofstream file("analysis.txt", ios::trunc); // clears all contents of analysis file

	personFile << "---------------------------------------------------------" << endl;
	personFile << "Person 1: " << getAgeRange() << "\t\t\t\t\t\t\tID " << ID << endl;
	personFile << "---------------------------------------------------------" << endl;

	if((NC+NNC) > 0)
		personFile << "Night:\t\t" << setprecision(2) << (NC)*100/(NC+NNC) << "% critical samples" << endl;
	else 
		personFile << "Night\t\t" << error_msg << endl;
	if((MC+MNC) > 0)
		personFile << "Morning:\t" << setprecision(2) << (MC)*100/(MC+MNC) << "% critical samples" << endl;
	else 
		personFile << "Morning:\t" << error_msg << endl;
	if((DC+DNC) > 0)
		personFile << "Daytime:\t" << setprecision(2) << (DC)*100/(DC+DNC) << "% critical samples" << endl;
	else 
		personFile << "Daytime:\t" << error_msg << endl;
	if((EC+ENC) > 0)
		personFile << "Evening:\t" << setprecision(2) << (EC)*100/(EC+ENC) << "% critical samples" << endl;
	else 
		personFile << "Evening:\t" << error_msg << endl;
	personFile << "---------------------------------------------------------" << endl;
}

// takes the sample date stamp as a string and parses for the time, giving the hour as an integer
unsigned int Person::getTimeWindow(string time) { 

	tm timeH;
	stringstream stringdate(time);
	int time_hour;
	int time_H;

	stringdate >> get_time(&timeH,"%Y-%m-%d.%T");
	time_hour = timeH.tm_hour;

	if(time_hour < 7) //checks the sample time against parameters given 
		time_H = 0;
	if(7 <= time_hour && time_hour < 10)
		time_H = 1;
	if(10 <= time_hour && time_hour < 18)
		time_H = 2;
	if(18 <= time_hour && time_hour <= 23)
		time_H = 3;
	
	return time_H; //returns the time window value assigned for tat time stamp
}

unsigned int Person::passToTime(string hour){ // the string is passed to getTimeWindow()
	int time_H = getTimeWindow(hour);
	return time_H;
}

//compares the age and the sampleValue against the parameters using the time window value generated
unsigned int Person::analyseSensedData(int timeWindow, double sampleValue) {

	//NIGHT: 0 = critical 1 = non-critical 
	if(timeWindow == 0) {
		if(age <= 6) {
			if(20 <= sampleValue && sampleValue <= 30.2)
				return 1;
			else
				return 0;
		}
		else if(7 <= age && age <= 16) {
			if(22 <= sampleValue && sampleValue <= 35.9)
				return 1;
			else
				return 0;
		}
		else if (17 <= age && age <= 38) {
			if(22.7 <= sampleValue && sampleValue  <= 37.3) 
				return 1;
			else
				return 0;
		}
		else if (39 <= age && age <= 55) {
			if(25.7 <= sampleValue && sampleValue <= 38.3)
				return 1;
			else
				return 0;
		}
		else 
			return 0;
	}
	//MORNING: 2 = critical 3 = non-critical
	else if(timeWindow == 1) {
		if(age <= 6){
			if(30 <= sampleValue && sampleValue <= 52)
				return 3;
			else
				return 2;
		}
		else if(7 <= age && age <= 16) {
			if(30 <= sampleValue && sampleValue <= 55)
				return 3;
			else
				return 2;
		}
		else if(17 <= age && age <= 55) {
			if(32 <= sampleValue && sampleValue <= 57.8)
				return 3;
			else
				return 2;
		}
		else if(55 < age) {
			if(30 <= sampleValue && sampleValue <= 50)
				return 3;
			else
				return 2;
		}
		else 
			return 2;
	}
	//DAYTIME: 4 = critical 5 = non-critical
	else if(timeWindow == 2){
		if(age <= 6){
			if(20 <= sampleValue && sampleValue <= 40)
				return 5;
			else
				return 4;
		}
		else if(7 <= age && age <= 16){
			if(22 <= sampleValue && sampleValue <= 39)
				return 5;
			else
				return 4;
		}
		else if(17 <= age && age <= 55){
			if(22.7 <= sampleValue && sampleValue <= 41)
				return 5;
			else
				return 4;
		}
		else if(55 < age){
			if(25.7 <= sampleValue && sampleValue <= 37)
				return 5;
			else
				return 4;
		}
		else
			return 4;
	}
	//NIGHTIME: 6 = critical 7 = non-critical
	else if(timeWindow == 3){
		if(age <= 6){
			if(25 <= sampleValue && sampleValue <= 52)
				return 7;
			else
				return 6;
		}
		else if(7 <= age && age <= 16){
			if(25 <= sampleValue && sampleValue <= 55)
				return 7;
			else
				return 6;
		}
		else if(17 <= age && age <= 55){
			if(25 <= sampleValue && sampleValue <= 57.8)
				return 7;
			else
				return 6;
		}
		else if(55 < age){
			if(25 <= sampleValue && sampleValue <= 40)
				return 7;
			else
				return 6;
		}
		else 
			return 6;
	}
	return 0;
}

Person::Person(unsigned int A): age(A){}