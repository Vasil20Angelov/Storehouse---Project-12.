#pragma once
struct Date
{

	int year;
	int month;
	int day;

	bool DateValidation();
	bool Same_date(Date d2);
	void Set_Date();
	
};