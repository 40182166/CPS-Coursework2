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
	Algorithms(int lim, int runs, bool print);
	~Algorithms();

	void execute();

	int thisLimit;
	int thisRuns;
	bool thisPrint;


	void SieveOfEratosthenes();
	void SieveOfSundaram();
	void SieveOfAtkin();


};

