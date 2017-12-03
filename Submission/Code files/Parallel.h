#pragma once
#include "Algorithms.h"
#include <mutex>

// File holding both parallelization techniques classes

//inheriting form algorithms
class OpenMP : public Algorithms
{
public:
	OpenMP(int lim, int runs, bool print);
	~OpenMP();

	//overriding virtual methods
	virtual void SieveOfEratosthenes();
	virtual void SieveOfSundaram();
	virtual void SieveOfAtkin();

};

//inheriting form algorithms
class Thread : public Algorithms
{
public:
	Thread(int lim, int runs, bool print);
	~Thread();

	//overriding virtual methods
	virtual void SieveOfEratosthenes();
	virtual void SieveOfSundaram();
	virtual void SieveOfAtkin();

	//methods containing main loops of the algorithms --> will be used to create threads
	void threadedEratosthenes(int start, int end, vector<bool>& primes);
	void threadedAtkin(int start, int end, vector<bool>& primes);
	void threadedSundaram(int start, int end, vector<int>& primes);
};