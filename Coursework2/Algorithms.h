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

	virtual void execute();

	int thisLimit;
	int thisRuns;
	bool thisPrint;

	virtual void SieveOfEratosthenes() {};
	virtual void SieveOfSundaram() {};
	virtual void SieveOfAtkin() {};

};

