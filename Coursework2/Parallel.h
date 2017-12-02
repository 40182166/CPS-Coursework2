#pragma once
#include "Algorithms.h"
#include <mutex>

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

	mutex mut;

	virtual void SieveOfEratosthenes();
	virtual void SieveOfSundaram();
	virtual void SieveOfAtkin();

	void threadedEratosthenes(int start, int end, vector<bool>& primes);
	void threadedAtkin(int start, int end, vector<bool>& primes);
	void threadedSundaram(int start, int end, vector<int>& primes);


};