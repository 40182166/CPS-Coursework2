#pragma once
#include "Algorithms.h"

class OpenMP : public Algorithms
{
public:
	OpenMP(int lim, int runs, bool print);
	~OpenMP();

	virtual void SieveOfEratosthenes();
	virtual void SieveOfSundaram();
	virtual void SieveOfAtkin();

};

class Thread : public Algorithms
{
public:
	Thread(int lim, int runs, bool print);
	~Thread();

	virtual void SieveOfEratosthenes();
	virtual void SieveOfSundaram();
	virtual void SieveOfAtkin();

	void threadedEratosthenes(int start, int end, vector<bool>& primes);

};