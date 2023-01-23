program: main.cpp Sensor.o Person.o
	g++ -o $@ main.cpp Sensor.o Person.o

Sensor.o: Sensor.cpp
	g++ -o $@ -c Sensor.cpp

Person.o: Person.cpp
	g++ -o $@ -c Person.cpp
cl:
	rm -rf *.o
	rm -rf program
	rm -rf *.txt


cld:
	rm -rf *.dat
