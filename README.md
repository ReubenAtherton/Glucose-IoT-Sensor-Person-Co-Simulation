# Glucose-IoT-Sensor-Person-Co-Simulation

This project simulates the behaviour of a glucose sensing IoT device. Data is created by initialising the sensor using the command:

'./program --sensorOnly --sampleTime VALUE --numberOfSimulatedSamples VALUE --PrecisionBits VALUE' 

where VALUE is the the your integer entry for that parameter. This must be done at different times of the day as each data point is time stamped, improving the realness of simulation. A person is then created using the command:

'./program --personOnly VALUE' 

where VALUE is the age entry for the person being created. 

A file analysis.txt will then be created showing the persons age range, their randomly generated ID number and finally a table inlcluding the times at which person was experiencing critical or non-critical levels of glucose.

This project part of my Electrical Engineering degree coursework, intended as an introduction to OOP programming. I achieved an 82% grade for this work. 
