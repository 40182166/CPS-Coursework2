#include "stdafx.h"
#include "Algorithms.h"

void Algorithms::execute()
{

	//executing 0 to n runs
	for (int i = 0; i < thisRuns; ++i)
	{
		//if thisPrint is true, checks if it is run number 0. If so, set isPrint to false as printing will only happen on first run
		if (thisPrint) 
		{
			if (i != 0)
			{
				thisPrint = false;
			}
		}
		cout << endl << endl << "Run " << i + 1 << endl << endl;

		//calling algorithms methods
		cout << "Calculating Eratosthenes..." << endl;
		SieveOfEratosthenes();
		cout << "Calculating Sundaram..." << endl;
		SieveOfSundaram();
		cout << "Calculating Atkin..." << endl;
		SieveOfAtkin();
	}
}