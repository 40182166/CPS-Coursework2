#pragma once
#include "Algorithms.h"

//inheriting from algorithm
class Serial : public Algorithms
{
public:
	//constructor that passes values from menu to class
	Serial(int lim, int runs, bool print);
	~Serial();

	//overriding virtual methods
	virtual void SieveOfEratosthenes();
	virtual void SieveOfSundaram();
	virtual void SieveOfAtkin();
};

