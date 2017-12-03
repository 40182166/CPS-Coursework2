#include "stdafx.h"
#include "Parallel.h"
#include <thread>
#include <fstream>
#include <xmmintrin.h>  


OpenMP::OpenMP(int lim, int runs, bool print)
{
	thisLimit = lim;
	thisRuns = runs;
	thisPrint = print;
	execute();
}


OpenMP::~OpenMP()
{
}

void OpenMP::SieveOfEratosthenes() {

	int n = thisLimit;
	// Creating a vector of booleans and initializing values as true
	vector<bool> isPrime(n + 1, true);
	string file;

	file = "Eratosthenes_tryOMP_time_lab.csv";

	auto nThreads = thread::hardware_concurrency();

	ofstream timings(file, ios_base::app);


	auto start = system_clock::now();
	// Setting i to 2, as it is the first prime number
	// Looping through all numbers up to n
	

	for (int i = 2; i * i <= n; i++)
	{
		// If prime[i] is true (unchanged), then the number is a prime
		// If prime[i] is false, it has been marked as not prime
		if (isPrime[i])
		{
#pragma omp parallel for num_threads(nThreads)
			// Looping through multiples of i and marking them as false (non-prime)
			for (int j = i * 2; j <= n; j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	auto end = system_clock::now();
	auto total = duration_cast<milliseconds>(end - start).count();
	timings << total / 1000.0 << endl;
	timings.close();

	if (thisPrint)
	{
		ofstream primes("Eratosthenes_primesOMP.csv", ios_base::out);
		// Print all prime numbers
		for (int i = 2; i <= n; i++)
		{
			//if bool for prime and toWrite are true, then print to file
			if (isPrime[i])
			{
				primes << i << endl;
			}
		}
		primes.close();
	}

}

// Mainly from : http://www.sanfoundry.com/cpp-program-generate-prime-numbers-between-given-range-using-sieve-sundaram/
void OpenMP::SieveOfSundaram()
{
	int setPrime = 0; // variable used in the array that stores the prime numbers found
	int nPrimes = 0; // prime counter

					 // The algorithm produces prime numbers smaller than a given number n.
					 // It also doesn't consider even numbers, so only n / 2 is needed
	int n = thisLimit / 2;

	//// Creating a vector of int and initializing values as 1
	vector<int> isPrime(thisLimit, 1);

	string file;

	file = "Sundaram_OMP_time_lab.csv";

	ofstream timings(file, ios_base::app);

	auto nThreads = thread::hardware_concurrency();

	auto start = system_clock::now();

	//splitting the workload in chunks of 10
#pragma omp parallel for num_threads(nThreads) schedule(static, 10)
	for (int i = 1; i < n; i++)
	{
		// from i + j + 2 * i * j <= nNew that can be solved as  j <= (nNew - i) / (2 * i + 1)
		int l = (n - i) / (2 * i + 1);

		for (int j = i; j <= l; j++)
		{
			// numbers of the form i + j + 2 * i * j are not prime
			// E.g. i = 1, j = 2
			// 1 + 2 + 2 * 1 * 2 = 7
			// the boolean at isPrime[7] will be marked as 0
			isPrime[i + j + 2 * i * j] = 0;
		}
	}

	// 2 is the only even prime number, so it will be printed separately
	if (thisLimit >= 2)
	{
		isPrime[setPrime++] = 2;
	}

	for (int i = 1; i < n; i++)
	{
		// Number that were previously set to 0 are not prime, the others
		if (isPrime[i] != 0)
		{
			isPrime[setPrime++] = i * 2 + 1;
			nPrimes++;			//counting primes
		}
	}

	auto end = system_clock::now();
	auto total = duration_cast<milliseconds>(end - start).count();
	timings << total / 1000.0 << endl;
	timings.close();

	if (thisPrint)
	{
		ofstream primes("Sundaram_primesOMP.csv", ios_base::out);

		for (int x = 0; x <= nPrimes; x++)
		{
			// If the prime number does not equal zero then output - else then break
			if (isPrime[x] != 0)
			{
				primes << isPrime[x] << endl;
			}
			else
			{
				break;
			}
		}
		primes.close();
	}
}

// From : http://www.sanfoundry.com/cpp-program-implement-sieve-atkins/
void OpenMP::SieveOfAtkin()
{
	int n = thisLimit;

	// Initialise the sieve array with false values
	vector<bool> isPrime(n + 1, false);

	string file;

	file = "Atkin_OMP_time_lab.csv";

	ofstream timings(file, ios_base::app);

	auto nThreads = thread::hardware_concurrency();

	auto start = system_clock::now();

	// 2 and 3 are known to be prime
	isPrime[2] = true;
	isPrime[3] = true;

	// Rounding square root of n up to the nearest integer
	int lim = (int)ceil(sqrt(n));

	//int y;


	// Looping through x and y, finding numbers that meet the conditions
	for (int x = 1; x <= lim; x++)
	{
		//Parallelizing inner loop --> outer loop causes wrong output
#pragma omp parallel for num_threads(nThreads) 	
		for (int y = 1; y <= lim; y++)
		{
			// First condition to be met
			// Having x = 1, y = 2 --> 4 * 1 * 1 + 2 * 2 = 8
			int num = (4 * x * x) + (y * y);

			// if num = 8, this condition won't be met, as 8 % 12 = 8.
			// if num = 13 for x = 1, y = 3, condition will be met and the number is prime, as 13 % 12 = 1
			if (num <= n && (num % 12 == 1 || num % 12 == 5))
			{
				isPrime[num] = true;
			}

			// If previous conditions are not met, this will be checked after
			num = (3 * x * x) + (y * y);
			if (num <= n && (num % 12 == 7))
			{
				isPrime[num] = true;
			}

			// Checking the last condition if none of the above have been met yet
			num = (3 * x * x) - (y * y);
			if (x > y && num <= n && (num % 12 == 11))
			{
				isPrime[num] = true;
			}
		}
	}

	// Mark all multiples of squares as non-prime
	for (int i = 5; i <= lim; i++)
	{
		if (isPrime[i])
		{
			// all squares of i will be marked as false
			for (int j = i * i; j < n; j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	auto end = system_clock::now();
	auto total = duration_cast<milliseconds>(end - start).count();
	timings << total / 1000.0 << endl;
	timings.close();

	if (thisPrint)
	{
		ofstream primes("Atkin_primesOMP.csv", ios_base::out);

		// Print values at isPrime[i], that will be true
		for (int i = 2; i <= n; i++)
		{
			if (isPrime[i])
			{
				primes << i << endl;
			}
		}
		primes.close();
	}
}


Thread::Thread(int lim, int runs, bool print)
{
	thisLimit = lim;
	thisRuns = runs;
	thisPrint = print;
	execute();
}

Thread::~Thread()
{
}

// Base Algorithm for threads has been taken from a different source : http://www.algolist.net/Algorithms/Number_theoretic/Sieve_of_Eratosthenes 
void Thread::SieveOfEratosthenes()
{
	// Creating a vector of booleans and initializing values as true

	vector<bool> isPrime(thisLimit + 1, true);
	string file;

	file = "Eratosthenes_threads_time_lab.csv";

	auto nThreads = thread::hardware_concurrency();

	int n = (int)floor(sqrt((double)thisLimit));

	int range = n / nThreads;

	ofstream timings(file, ios_base::app);

	vector<thread> threads;

	auto start = system_clock::now();

	int startPoint = 2;
	int endPoint;

	for (int i = 1; i <= nThreads; i++)
	{
		//endPoint is the previous start point plus the range
		endPoint = (startPoint + 1) + range;

		if (endPoint > thisLimit)
		{
			endPoint = thisLimit;
		}
		//Creating and pushing Threads into a vector
		threads.push_back(thread(&Thread::threadedEratosthenes, this, startPoint, endPoint, i, ref(isPrime)));

		//setting start at end of previous thread + 1
		//this is because in the main loop of the algorithm the x is <= end.
		startPoint = endPoint + 1;
	}

	for (auto &t : threads)
	{
		t.join();
	}


	auto end = system_clock::now();
	auto total = duration_cast<milliseconds>(end - start).count();
	timings << total / 1000.0 << endl;
	timings.close();

	if (thisPrint)
	{
		ofstream primes("Eratosthenes_primesThreads.csv", ios_base::out);

		// Print values at isPrime[i], that will be true
		for (int i = 2; i <= thisLimit; i++)
		{
			if (isPrime[i])
			{
				primes << i << endl;
			}
		}
		primes.close();
	}

}

void Thread::threadedEratosthenes(int start, int end, int index, vector<bool>& primes)
{
	for (int i = start; i <= end; i++)
	{
		// If prime[i] is true (unchanged), then the number is a prime
		// If prime[i] is false, it has been marked as not prime
		if (primes[i])
		{
			// Looping through multiples of i and marking them as false (non-prime)
			for (int j = i * i; j <= thisLimit; j += i)
			{
				primes[j] = false;
			}
		}
	}

}


void Thread::SieveOfSundaram()
{
	int setPrime = 0; // variable used in the array that stores the prime numbers found
	int nPrimes = 0; // prime counter

	// The algorithm produces prime numbers smaller than a given number n.
	// It also doesn't consider even numbers, so only n / 2 is needed
	int n = thisLimit / 2;

	// Creating a vector of int and initializing values as 1
	vector<int> isPrime(thisLimit, 1);

	string file;

	file = "Sundaram_threads_time_lab.csv";

	ofstream timings(file, ios_base::app);

	auto nThreads = thread::hardware_concurrency();

	vector<thread> allThreads;

	auto start = system_clock::now();

	auto range = n / nThreads;

	int startPoint = 1;
	int endPoint = 1;

	for (int i = 1; i <= nThreads; i++)
	{
		//endPoint is the previous start point plus the range
		endPoint = startPoint + range;

		//Creating and pushing Threads into a vector
		allThreads.push_back(thread(&Thread::threadedSundaram, this, startPoint, endPoint, ref(isPrime)));

		//setting start at end of previous thread + 1
		//this is because in the main loop of the algorithm the x is <= end.
		startPoint = endPoint + 1;
	}

	for (auto &t : allThreads)
	{
		t.join();
	}

	// 2 is the only even prime number, so it will be printed separately
	if (thisLimit >= 2)
	{
		isPrime[setPrime++] = 2;
	}

	for (int i = 1; i < n; i++)
	{
		// Number that were previously set to 0 are not prime, the others
		if (isPrime[i] != 0)
		{
			isPrime[setPrime++] = i * 2 + 1;
			nPrimes++;			//counting primes
		}
	}

	auto end = system_clock::now();
	auto total = duration_cast<milliseconds>(end - start).count();
	timings << total / 1000.0 << endl;
	timings.close();

	if (thisPrint)
	{
		ofstream primes("Sundaram_primesThreads.csv", ios_base::out);

		for (int x = 0; x <= nPrimes; x++)
		{
			// If the prime number does not equal zero then output - else then break
			if (isPrime[x] != 0)
			{
				primes << isPrime[x] << endl;
			}
			else
			{
				break;
			}
		}
		primes.close();
	}
}

void Thread::threadedSundaram(int start, int end, vector<int>& primes)
{
	for (int i = start; i <= end; i++)
	{
		// from i + j + 2 * i * j <= nNew that can be solved as  j <= ((thisLimit / 2) - i) / (2 * i + 1)
		int l = ((thisLimit / 2) - i) / (2 * i + 1);

		for (int j = i; j <= l; j++)
		{
			// numbers of the form i + j + 2 * i * j are not prime
			// E.g. i = 1, j = 2
			// 1 + 2 + 2 * 1 * 2 = 7
			// the boolean at isPrime[7] will be marked as 0
			primes[i + j + 2 * i * j] = 0;
		}
	}

}


void Thread::SieveOfAtkin()
{
	int n = thisLimit;

	// Initialise the sieve array with false values
	vector<bool> isPrime(n + 1, false);

	string file;

	file = "Atkin_threads_time_lab.csv";

	ofstream timings(file, ios_base::app);

	auto nThreads = thread::hardware_concurrency();

	vector<thread> allThreads1;
	//vector<thread> allThreads2;
	auto start = system_clock::now();

	// 2 and 3 are known to be prime
	isPrime[2] = true;
	isPrime[3] = true;

	// Rounding square root of n up to the nearest integer
	int lim = (int)ceil(sqrt(n));

	auto range = lim / nThreads;

	int startPoint = 1;
	int endPoint = 1;

	//Loop for creating threads based on a start and an end point
	for (int i = 1; i <= nThreads; i++)
	{
		//endPoint is the previous start point plus the range
		endPoint = startPoint + range;

		//Creating and pushing Threads into a vector
		allThreads1.push_back(thread(&Thread::threadedAtkin, this, startPoint, endPoint, ref(isPrime)));
		//setting start at end of previous thread + 1
		//this is because in the main loop of the algorithm the x is <= end.
		startPoint = endPoint + 1;
	}

	for (auto &t : allThreads1)
	{
		t.join();
	}


	// Mark all multiples of squares as non-prime
	for (int i = 5; i <= lim; i++)
	{
		if (isPrime[i])
		{
			// all squares of i will be marked as false
			for (int j = i * i; j <= n; j += i)
			{
				isPrime[j] = false;
			}
		}
	}


	auto end = system_clock::now();
	auto total = duration_cast<milliseconds>(end - start).count();
	timings << total / 1000.0 << endl;
	timings.close();


	if (thisPrint)
	{
		ofstream primes("Atkin_primesThreads.csv", ios_base::out);

		// Print values at isPrime[i], that will be true
		for (int i = 2; i <= n; i++)
		{
			if (isPrime[i])
			{
				primes << i << endl;
			}
		}
		primes.close();
	}

}

void Thread::threadedAtkin(int start, int end, vector<bool>& primes)
{

	// Looping through x and y, finding numbers that meet the conditions
	for (int x = start; x <= end; x++)
	{
		for (int y = 1; y * y <= thisLimit; y++)
		{
			// First condition to be met
			// Having x = 1, y = 2 --> 4 * 1 * 1 + 2 * 2 = 8
			int num = (4 * x * x + y * y);

			// if num = 8, this condition won't be met, as 8 % 12 = 8.
			// if num = 13 for x = 1, y = 3, condition will be met and the number is prime, as 13 % 12 = 1
			if (num <= thisLimit && (num % 12 == 1 || num % 12 == 5))
			{
				primes[num] = true;
			}

			// If previous conditions are not met, this will be checked after
			num = (3 * x * x + y * y);
			if (num <= thisLimit && (num % 12 == 7))
			{
				primes[num] = true;
			}

			// Checking the last condition if none of the above have been met yet
			num = (3 * x * x - y * y);
			if (x > y && num <= thisLimit && (num % 12 == 11))
			{
				primes[num] = true;
			}
		}
	}
}


