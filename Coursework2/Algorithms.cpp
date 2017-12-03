#include "stdafx.h"
#include "Algorithms.h"

void Algorithms::execute()
{

	for (int i = 0; i < thisRuns; ++i)
	{
		if (thisPrint) 
		{
			if (i != 0)
			{
				thisPrint = false;
			}
		}
		cout << endl << endl << "Run " << i + 1 << endl << endl;

		//cout << "Calculating Eratosthenes..." << endl;
		//SieveOfEratosthenes();
		//cout << "Calculating Sundaram..." << endl;
		//SieveOfSundaram();
		cout << "Calculating Atkin..." << endl;
		SieveOfAtkin();
	}
}