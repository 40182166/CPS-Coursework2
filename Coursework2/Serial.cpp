#include "stdafx.h"
#include "Serial.h"


Serial::Serial(int lim, int runs, bool print)
{
	thisLimit = lim;
	thisRuns = runs;
	thisPrint = print;
	execute();
}


Serial::~Serial()
{

}

// From : http://www.geeksforgeeks.org/sieve-of-eratosthenes/
void Serial::SieveOfEratosthenes() {

	int n = thisLimit;
	// Creating a vector of booleans and initializing values as true
	vector<bool> isPrime(n + 1, true);

	string file;

	file = "Eratosthenes_serial_time.csv";

	// file to output timings
	ofstream timings(file, ios_base::app);

	//starting clock
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

	//ending clock and calculate time. Output it to file
	auto end = system_clock::now();
	auto total = duration_cast<milliseconds>(end - start).count();
	timings << total / 1000.0 << endl;
	timings.close();

	//if thisPrint is true, outputs primes to file
	if (thisPrint)
	{
		ofstream primes("Eratosthenes_primes.csv", ios_base::out);

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

// From : http://www.sanfoundry.com/cpp-program-generate-prime-numbers-between-given-range-using-sieve-sundaram/
void Serial::SieveOfSundaram()
{
	int setPrime = 0; // variable used in the array that stores the prime numbers found
	int nPrimes = 0; // prime counter

	// The algorithm produces prime numbers smaller than a given number n.
	// It also doesn't consider even numbers, so only n / 2 is needed
	int n = thisLimit / 2;

	//// Creating a vector of int and initializing values as 1
	vector<int> isPrime(thisLimit, 1);

	string file;

	file = "Sundaram_serial_time.csv";

	// file to output timings
	ofstream timings(file, ios_base::app);

	//starting clock
	auto start = system_clock::now();


	for (int i = 1; i < n; i++)
	{
		// from i + j + 2 * i * j <= nNew that can be solved as  j <= (nNew - i) / (2 * i + 1)
		for (int j = i; j <= (n - i) / (2 * i + 1); j++)
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

	//ending clock
	auto end = system_clock::now();
	auto total = duration_cast<milliseconds>(end - start).count();
	timings << total / 1000.0 << endl;
	timings.close();

	//if true, output to file
	if (thisPrint)
	{
		ofstream primes("Sundaram_primes.csv", ios_base::out);

		for (int x = 0; x <= nPrimes; x++)
		{
			// If the prime number does not equal zero then output then break
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
void Serial::SieveOfAtkin()
{
	int n = thisLimit;

	// Initialise the sieve array with false values
	vector<bool> isPrime(n + 1, false);

	string file;

	file = "Atkin_serial_time.csv";

	// file to output timings
	ofstream timings(file, ios_base::app);

	//starting clock
	auto start = system_clock::now();

	// 2 and 3 are known to be prime
	isPrime[2] = true;
	isPrime[3] = true;

	// Rounding square root of n up to the nearest integer
	int lim = (int)ceil(sqrt(n));

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

	auto end = system_clock::now();
	auto total = duration_cast<milliseconds>(end - start).count();
	timings << total / 1000.0 << endl;
	timings.close();

	if (thisPrint)
	{
		ofstream primes("Atkin_primes.csv", ios_base::out);

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