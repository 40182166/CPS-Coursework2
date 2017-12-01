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

	int numberRuns = 1;

	// Selecting mode of run (technique)
	// 1 --> default: serial
	// 2 --> OpenMP
	int technique = 2;
	int limit = 1000000000;

	bool toPrint = true;

	void mainMenu();
	void continueMenu();

private:

	void options();
	void techniqueMenu();
	void runsMenu();
	void printMenu();

	int getInput();

};

