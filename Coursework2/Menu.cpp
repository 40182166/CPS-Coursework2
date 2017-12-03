#include "stdafx.h"
#include "Menu.h"


Menu::Menu()
{
	mainMenu();
}

Menu::~Menu()
{
}

void Menu::mainMenu()
{
	int input = 0;
	do
	{
		cout << endl << "********************************* ---- PRIME NUMBERS KINGDOM ---- *********************************" << endl << endl;
		cout << "INFO:" << endl;
		cout << "This program will execute 3 algorithms to generate prime numbers: Eratosthenes, Sundaram and Atkin" << endl;
		cout << "Executing the program without setting new options, will run the default settings:" << endl;
		cout << "- Serial (no technique)" << endl;
		cout << "- 1 run for each algorithm" << endl;
		cout << "- Writing to file prime numbers (only for first run)" << endl << endl << endl;

		cout << "---- MAIN MENU ----" << endl << endl;
		cout << "Select one of the following : " << endl;
		cout << "1 - Options" << endl;
		cout << "2 - Execute" << endl;
		cout << "3 - Exit" << endl;
		cout << endl << "Selection: ";

		input = getInput();

		switch (input)
		{
		case 1:
			options();
			break;
		case 2:
			cout << "Executing !" << endl << endl;
			Thread(limit, numberRuns, toPrint);

			//executeEverything();
			continueMenu();
			break;
		case 3:
			cout << "Exiting..." << endl << endl;
			exit(1);
			break;
		default:
			cout << "Invalid option!";
			break;
		}

	} while (input != 2);
}

void Menu::executeEverything()
{
	switch (technique)
	{
	case 1:
		Serial(limit, numberRuns, toPrint);
		break;
	case 2:
		Thread(limit, numberRuns, toPrint);
		break;
	default:
		Serial(limit, numberRuns, toPrint);
		break;
	}

}

void Menu::continueMenu()
{
	int input = 0;
	do
	{

		cout << endl << endl << "---- END ----" << endl << endl;
		cout << "What's next? : " << endl;
		cout << "1 - Start again (this will reset previous selected options)" << endl;
		cout << "2 - Exit program" << endl;
		cout << endl << "Selection: ";

		input = getInput();

		switch (input)
		{
		case 1:
		{
			numberRuns = 1;
			technique = 1;
			toPrint = true;
			mainMenu();
		}
		break;
		case 2:
			cout << "Exiting..." << endl << endl;
			exit(1);
			break;
		default:
			cout << endl << "Invalid option!" << endl << endl;
			break;
		}

	} while (input != 5);

}

void Menu::options()
{
	int input = 0;
	do
	{

		cout << endl << endl << "---- OPTIONS MENU ----" << endl << endl;
		cout << "Select an option : " << endl;
		cout << "1 - Techniques options" << endl;
		cout << "2 - Runs options" << endl;
		cout << "3 - Printing options" << endl;
		cout << "4 - Back to main" << endl;
		cout << endl << "Selection: ";

		input = getInput();

		switch (input)
		{
		case 1:
			techniqueMenu();
			break;
		case 2:
			runsMenu();
			break;
		case 3:
			printMenu();
			break;
		case 4:
			cout << endl << "Going back..." << endl << endl;
			break;
		default:
			cout << endl << "Invalid option!" << endl << endl;
			break;
		}

	} while (input != 4);

}

void Menu::techniqueMenu()
{
	int input = 0;
	do
	{

		cout << endl << endl << "---- TECHNIQUES MENU ----" << endl << endl;
		cout << "Current selected technique: ";
		if (technique == 1)
		{
			cout << "Serial" << endl << endl;
		}
		else if (technique == 2)
		{
			cout << "OpenMP" << endl << endl;
		}
		cout << "Select a technique : " << endl;
		cout << "1 - Serial" << endl;
		cout << "2 - OpenMP" << endl;
		cout << "3 - Back" << endl;
		cout << endl << "Selection: ";

		input = getInput();

		switch (input)
		{
		case 1:
			cout << endl << "Serial technique will be used..." << endl << endl;
			technique = 1;
			break;
		case 2:
			cout << endl << "OpenMP will be used..." << endl << endl;
			technique = 2;
			break;
		case 3:
			cout << endl << "Going back..." << endl << endl;
			break;
		default:
			cout << endl << "Invalid option!" << endl << endl;
			break;
		}

	} while (input != 3);

}

void Menu::runsMenu()
{
	//numberRuns = 1;
	int input = -1;
	do
	{

		cout << endl << endl << "---- RUNS MENU ----" << endl << endl;
		cout << "Current number of runs: " << numberRuns << endl << endl;
		cout << "How many runs for each algorithm? (0 or negative value to go back): ";

		input = getInput();

		while (cin.fail()) {
			cout << "Error" << std::endl;
			cin.clear();
			cin.ignore(256, '\n');
			cout << "How many runs for each algorithm? (0 to go back to main): ";
			input = getInput();
		}

		if (input >= 1)
		{
			numberRuns = input;
			if (numberRuns == 1)
			{
				cout << endl << "Executing 1 run of each algorithm... " << endl;
			}
			else
			{
				cout << endl << "Executing " << numberRuns << " runs of each algorithm... " << endl;
			}
			break;
		}

	} while (input > 0);
}

void Menu::printMenu()
{
	int input = -1;
	do
	{
		cout << endl << endl << "---- PRINTING MENU ----" << endl << endl;
		cout << "Is currently writing primes to file?: ";
		if (toPrint)
		{
			cout << "Yes" << endl << endl;
		}
		else
		{
			cout << "No" << endl << endl;
		}


		cout << "Writing primes to file? : " << endl;
		cout << "1 - Yes --> (NOTE: this option will only print results for the first run)" << endl;
		cout << "2 - No --> (NOTE: first run will be as fast as the following)" << endl;
		cout << "3 - Back" << endl;
		cout << endl << "Selection: ";

		input = getInput();

		switch (input)
		{
		case 1:
			cout << endl << "Writing results to file ..." << endl << endl;
			toPrint = true;
			break;
		case 2:
			cout << endl << "No results to file..." << endl << endl;
			toPrint = false;
			break;
		case 3:
			cout << endl << "Going back..." << endl << endl;
			break;
		default:
			cout << endl << "Invalid option!" << endl << endl;
			break;
		}

	} while (input != 3);

}

int Menu::getInput()
{
	int input;
	cin >> input;
	return input;
}
