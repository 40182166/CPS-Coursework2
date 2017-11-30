#pragma once
#include "Algorithms.h"

class Serial : public Algorithms
{
public:
	Serial(int lim, int runs, bool print);
	~Serial();

	virtual void SieveOfEratosthenes();
	virtual void SieveOfSundaram();
	virtual void SieveOfAtkin();
};

