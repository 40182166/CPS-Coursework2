#include "stdafx.h"
#include "Algorithms.h"


Algorithms::Algorithms(int lim, int runs, bool print)
{
	thisLimit = lim;
	thisRuns = runs;
	thisPrint = print;
	execute();
}


Algorithms::~Algorithms()
{
}

void Algorithms::execute()
{

	for (int i = 0; i < thisRuns; ++i)
	{
		cout << endl << endl << "Run " << i + 1 << endl << endl;

		cout << "Calculating Eratosthenes..." << endl;
		SieveOfEratosthenes();
		cout << "Calculating Sundaram..." << endl;
		SieveOfSundaram();
		cout << "Calculating Atkin..." << endl;
		SieveOfAtkin();
	}
}

// From : http://www.geeksforgeeks.org/sieve-of-eratosthenes/
// Option 2 From: http://www.algolist.net/Algorithms/Number_theoretic/Sieve_of_Eratosthenes
void Algorithms::SieveOfEratosthenes() {

	int n = thisLimit;
	// Creating a vector of booleans and initializing values as true
	vector<bool> isPrime(n + 1, true);
	string file;

	if (thisPrint)
	{
		file = "Eratosthenes_serial_time.csv";
	}
	else
	{
		file = "Eratosthenes_serial_time_loopOnlytry.csv";
	}

	ofstream timings(file, ios_base::app);
	ofstream primes("Eratosthenes_primes.csv", ios_base::out);

	auto start = system_clock::now();
	// Setting i to 2, as it is the first prime number
	// Looping through all numbers up to n
	for (int i = 2; i * i <= n; i++)
	{
		// If prime[i] is true (unchanged), then the number is a prime
		// If prime[i] is false, it has been marked as not prime
		if (isPrime[i])
		{
			// Looping through multiples of i and marking them as false (non-prime)
			for (int j = i * 2; j <= n; j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	if (thisPrint)
	{
		// Print all prime numbers
		for (int i = 2; i <= n; i++)
		{
			//if bool for prime and toWrite are true, then print to file
			if (isPrime[i])
			{
				primes << i << endl;
			}
		}
	}

	auto end = system_clock::now();
	auto total = duration_cast<milliseconds>(end - start).count();
	timings << total / 1000.0 << endl;
	timings.close();
	primes.close();
}

// Mainly from : http://www.sanfoundry.com/cpp-program-generate-prime-numbers-between-given-range-using-sieve-sundaram/
void Algorithms::SieveOfSundaram()
{
	int n = thisLimit;

	// The algorithm produces prime numbers smaller than a given number n.
	// It also doesn't consider even numbers, so only n / 2 is needed
	int nNew = n / 2;

	// Creating a vector of booleans and initializing values as true
	vector<bool> isPrime(nNew + 1, true);


	string file;

	if (thisPrint)
	{
		file = "Sundaram_serial_time.csv";
	}
	else
	{
		file = "Sundaram_serial_time_loopOnlytry.csv";
	}

	ofstream timings(file, ios_base::app);
	ofstream primes("Sundaram_primes.csv", ios_base::out);

	auto start = system_clock::now();
	int l;
	for (int i = 1; i < nNew; ++i)
	{
		// from i + j + 2 * i * j <= nNew that can be solved as  j <= (nNew - i) / (2 * i + 1)
		l = (nNew - i) / (2 * i + 1);

		for (int j = i; j <= l; ++j)
		{
			// numbers of the form of i + j + 2 * i * j are not prime
			// E.g. i = 1, j = 2
			// 1 + 2 + 2 * 1 * 2 = 7
			// the boolean at isPrime[7] will be marked as false
			// when printing, this will be skipped as 2 * 7 + 1 = 15 --> not a prime
			int notPrime = i + j + 2 * i * j;
			isPrime[notPrime] = false;
		}
	}

	if (thisPrint)
	{
		// 2 is the only even prime number, so it will be printed separately
		if (n >= 2)
			primes << 2 << endl;

		// Print other primes. Remaining primes are of the form
		// 2*i + 1 such that marked[i] is false.
		for (int i = 1; i < nNew; i++)
			if (isPrime[i])
				primes << 2 * i + 1 << endl;
	}

	auto end = system_clock::now();
	auto total = duration_cast<milliseconds>(end - start).count();
	timings << total / 1000.0 << endl;
	timings.close();
	primes.close();
}

// From : http://www.sanfoundry.com/cpp-program-implement-sieve-atkins/
void Algorithms::SieveOfAtkin()
{
	int n = thisLimit;

	// Initialise the sieve array with false values
	vector<bool> isPrime(n + 1, false);

	string file;

	if (thisPrint)
	{
		file = "Atkin_serial_time.csv";
	}
	else
	{
		file = "Atkin_serial_time_loopOnlytry.csv";
	}

	ofstream timings(file, ios_base::app);
	ofstream primes("Atkin_primes.csv", ios_base::out);

	auto start = system_clock::now();

	// 2 and 3 are known to be prime
	isPrime[2] = true;
	isPrime[3] = true;

	// Rounding square root of n up to the nearest integer
	int lim = ceil(sqrt(n));

	// Looping through x and y, finding numbers that meet the conditions
	for (int x = 1; x <= lim; x++)
	{
		for (int y = 1; y <= lim; y++)
		{
			// First condition to be met
			// Having x = 1, y = 2 --> 4 * 1 * 1 + 2 * 2 = 8
			int num = (4 * x * x + y * y);

			// if num = 8, this condition won't be met, as 8 % 12 = 8.
			// if num = 13 for x = 1, y = 3, condition will be met and the number is prime, as 13 % 12 = 1
			if (num <= n && (num % 12 == 1 || num % 12 == 5))
			{
				isPrime[num] = true;
			}

			// If previous conditions are not met, this will be checked after
			num = (3 * x * x + y * y);
			if (num <= n && (num % 12 == 7))
			{
				isPrime[num] = true;
			}

			// Checking the last condition if none of the above have been met yet
			num = (3 * x * x - y * y);
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
			for (int j = i * i; j <= n; j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	if (thisPrint)
	{
		// Print values at isPrime[i], that will be true
		for (int i = 2; i <= n; i++)
		{
			if (isPrime[i])
			{
				primes << i << endl;
			}
		}
	}

	auto end = system_clock::now();
	auto total = duration_cast<milliseconds>(end - start).count();
	timings << total / 1000.0 << endl;
	timings.close();
	primes.close();

}