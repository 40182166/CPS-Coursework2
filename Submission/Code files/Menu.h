#pragma once
#include <cstdlib>
#include <iostream>
#include "Algorithms.h"
#include "Parallel.h"
#include "Serial.h"

using namespace std;

class Menu
{
public:
	Menu();
	~Menu();

	void executeEverything();

	//default number of runs
	int numberRuns = 1;

	// Selecting mode of run (technique)
	// 1 --> default: serial
	// 2 --> OpenMP
	// 3 --> Threads
	int technique = 1;
	int limit = 1000000000; //1000000000

	bool toPrint = true;

	void mainMenu();
	void continueMenu();

private:

	// Menu options functions
	void options();
	void techniqueMenu();
	void runsMenu();
	void printMenu();

	//get input from cmd
	int getInput();

};

