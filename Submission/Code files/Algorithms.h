#pragma once
#include <fstream>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Algorithms
{
public:
	Algorithms() {};
	~Algorithms() {};

	//execute the run loop
	virtual void execute();

	//variables set through Menu class, based on user input
	int thisLimit;
	int thisRuns;
	bool thisPrint;

	//Virtual methods that Serial and Parallel will inherit, one for each algorithm implemented
	virtual void SieveOfEratosthenes() {};
	virtual void SieveOfSundaram() {};
	virtual void SieveOfAtkin() {};

};

