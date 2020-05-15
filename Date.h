#pragma once
#include <iostream>
struct Date
{

	int year;
	int month;
	int day;

	bool DateValidation();
	bool Same_date(Date d2);
	bool InPeriod(Date d1, Date d2);
	bool ExpiredDate(Date e1);
	bool DateCompare(Date d2);
	void Set_Date();
	void Show_Date() const;
};