#include "Date.h"

bool Date::DateValidation()
{
	return false;
}

bool Date::Same_date(Date d2)
{
	if (year == d2.year && month == d2.month && day == d2.day)
		return true;
	return false;
}

void Date::Set_Date()
{
}
