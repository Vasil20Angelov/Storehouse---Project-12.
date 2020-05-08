#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Date.h"
#include "Location.h"
using namespace std;
class Product
{
public:
	Product();
	Product(const string& product_name, const string& unit, const string& producer, const string& comment, int amount, Date expiry, Date placed_date, Location loc_start);
	
	void load_info(ifstream& in);
	void save_info(ofstream& out) const;

	void setEndLoc();
	bool checkLocation(Location l1, int amount);

	const string get_productname() const;
	const string get_unit() const;
	const int get_amount() const;
	const Date get_expiryDate() const;
	const Date get_placedDate() const;
	const Location get_Slocation() const;
	const Location get_Elocation() const;

private:
	string product_name;
	string producer;
	string unit;
	string comment;
	int amount;
	Date expiry;
	Date placed_date;
	Location loc_start;
	Location loc_end;
};

