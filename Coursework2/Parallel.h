#pragma once
#include "Algorithms.h"

class Parallel : public Algorithms
{
public:
	Parallel(int lim, int runs, bool print);
	~Parallel();

	virtual void SieveOfEratosthenes();
	virtual void SieveOfSundaram();
	virtual void SieveOfAtkin();

};

