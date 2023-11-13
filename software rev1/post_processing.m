%{
	Created:    November 13, 2023
	Modified:   December 13, 2023
	Version:    1.0
	GitHub: https://github.com/danielandinh/EEG-Project
	
	Description:
	Implementation of analog data sampler.
	Recieves serial data from nano and saves it to text file;
	
	Modification History:
	- Version 1.0 (November 13, 2023): Initial commit
	- 
%}

close all; clear all; clc;

% Read the text file into a matrix
dataMatrix = readmatrix('data.txt');

% Extract the value and time vectors
sensorData = dataMatrix(:, 1);  
time = dataMatrix(:, 2);  

% normalise data
normalised_Data = sensorData/1024;

% Display the vectors
plot(time, normalised_Data, Marker=".");