#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Location.h"
using namespace std;

void Location::setStartLocation(const Location& l1)
{
	shelf = l1.shelf;
	section = l1.section;

	number = l1.number + 1;
	if (number > 10)
	{
		number = 1;
		shelf++;
	}

	if (shelf > 10)
	{
		shelf = 1;
		section++;
	}

}

void Location::setRandomLocation()
{
	srand(time(NULL));
	number = rand() % 10 + 1;
	shelf = rand() % 10 + 1;
	section = rand() % 100 + 1;
}

void Location::setEndLocation(const Location& loc_start, int amount)
{
	int section_space = amount / 1000;
	if (amount >= 1000)
		amount % 1000;

	int shelf_space = amount / 100;
	int number_space = amount % 100;

	number = loc_start.number + number_space / 10;
	if (number_space % 10 != 0)
		number++;

	if (number > 10)
	{
		shelf_space++;
		number %= 10;
	}

	shelf = loc_start.shelf + shelf_space;
	if (shelf > 10)
	{
		section_space++;
		shelf %= 10;
	}

	section = loc_start.section + section_space;
}
