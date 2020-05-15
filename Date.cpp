#include <iostream>
#include "Date.h"
using namespace std;
bool Date::DateValidation()
{
	if (day < 1)
	{
		cout << "Invalid date! The day cannot be a number lower than 1!" << endl;
		return false;
	}
	switch (month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
	{
		if (day > 31)
		{
			cout << "Invalid date! The selected month has 31 days!" << endl;
			return false;
		}
		return true;
	}
	case 2:
	{
		bool leapY = false;
		if (year % 4 == 0)
			leapY = true;
		if ((day > 28 && !leapY) || (day > 29 && leapY))
		{
			cout << "Invalid date! February has 28 days (29 if it is a leap year)!" << endl;
			return false;
		}
		return true;
	}
	default:
	{
		if (day > 30)
		{
			cout << "Invalid date! The selected month has 30 days!" << endl;
			return false;
		}
		return true;
	}
	}
}

bool Date::Same_date(Date d2)
{
	if (year == d2.year && month == d2.month && day == d2.day)
		return true;
	return false;
}

bool Date::InPeriod(Date d1, Date d2)
{
	int ProductDate = year * 10000 + month * 100 + day;
	int date1 = d1.year * 10000 + d1.month * 100 + d1.day;
	int date2 = d2.year * 10000 + d2.month * 100 + d2.day;

	if (ProductDate >= date1 && ProductDate <= date2)
		return true;
	return false;
}

bool Date::ExpiredDate(Date e1)
{
	int ProductEDate = year * 10000 + month * 100 + day;
	int eDate = e1.year * 10000 + e1.month * 100 + e1.day + 5;
	if (ProductEDate <= eDate)
		return true;

	return false;
}

bool Date::DateCompare(Date d2)
{
	int ProductDate = year * 10000 + month * 100 + day;
	int date2 = d2.year * 10000 + d2.month * 100 + d2.day;
	if (ProductDate < date2)
		return true;

	return false;
}

void Date::Set_Date()
{
	bool isOk = true;
	do
	{
		isOk = true;
		cout << "Year: ";
		cin >> year;
		if (year < 1980 || year > 2050)
		{
			cout << "Invalid date! Enter an year between 1980 - 2050!" << endl;
			isOk = false;
		}

	} while (!isOk);

	do
	{
		isOk = true;
		cout << "Month: ";
		cin >> month;
		if (month < 1 || month > 12)
		{
			cout << "Invalid date! The month must be a number between 1 - 12!" << endl;
			isOk = false;
		}

	} while (!isOk);

	do
	{
		isOk = true;
		cout << "Day: ";
		cin >> day;
		if (!DateValidation())
		{
			isOk = false;
		}

	} while (!isOk);
}

void Date::Show_Date() const
{	
	if (month > 9 && day > 9)
		cout << year << "." << month << "." << day;
	else
		if (month < 10 && day>9)
			cout << year << ".0" << month << "." << day;
		else
			if (month > 9 && day < 10)
				cout << year << "." << month << ".0" << day;
			else
				cout << year << ".0" << month << ".0" << day;
}

