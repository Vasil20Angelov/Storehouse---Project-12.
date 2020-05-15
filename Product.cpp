#include <iostream>
#include <string>
#include "Product.h"
using namespace std;

Product::Product()
{
	product_name = "";
	unit = "";
	producer = "";
	comment = "";
	amount = 0;

	expiry.year = 0;
	expiry.month = 0;
	expiry.day = 0;

	placed_date.year = 0;
	placed_date.month = 0;
	placed_date.day = 0;

	loc_start.number = 1;
	loc_start.section = 1;
	loc_start.shelf = 1;

	loc_end.number = 1;
	loc_end.section = 1;
	loc_end.shelf = 1;

}

Product::Product(const string& product_name, const string& unit, const string& producer, const string& comment, int amount, Date expiry, Date placed_date, Location loc_start)
{
	this->product_name = product_name;
	this->unit = unit;
	this->producer = producer;
	this->comment = comment;
	this->amount = amount;

	this->expiry.year = expiry.year;
	this->expiry.month = expiry.month;
	this->expiry.day = expiry.day;

	this->placed_date.year = placed_date.year;
	this->placed_date.month = placed_date.month;
	this->placed_date.day = placed_date.day;
	
	this->loc_start.section = loc_start.section;
	this->loc_start.shelf = loc_start.shelf;
	this->loc_start.number = loc_start.number;

	this->loc_end.setEndLocation(loc_start, amount);
}

void Product::load_info(ifstream& in)
{
	size_t len;
	in.read((char*)&len, sizeof(size_t));
	product_name.resize(len);
	in.read((char*)&product_name[0], len);

	in.read((char*)&len, sizeof(size_t));
	unit.resize(len);
	in.read((char*)&unit[0], len);

	in.read((char*)&amount, sizeof(int));

	in.read((char*)&expiry, sizeof(Date));

	in.read((char*)&len, sizeof(size_t));
	producer.resize(len);
	in.read((char*)&producer[0], len);

	in.read((char*)&placed_date, sizeof(Date));

	in.read((char*)&loc_start, sizeof(Location));;

	in.read((char*)&loc_end, sizeof(Location));

	in.read((char*)&len, sizeof(size_t));
	comment.resize(len);
	in.read((char*)&comment[0], len);

}

void Product::save_info(ofstream& out) const
{
	size_t len = product_name.size();
	out.write((const char*)&len, sizeof(size_t));
	out.write((const char*)&product_name[0], len);

	len = unit.size();
	out.write((const char*)&len, sizeof(size_t));
	out.write((const char*)&unit[0], len);

	out.write((const char*)&amount, sizeof(int));

	out.write((const char*)&expiry, sizeof(Date));

	len = producer.size();
	out.write((const char*)&len, sizeof(size_t));
	out.write((const char*)&producer[0], len);

	out.write((const char*)&placed_date, sizeof(Date));

	out.write((const char*)&loc_start, sizeof(Location));

	out.write((const char*)&loc_end, sizeof(Location));

	len = comment.size();
	out.write((const char*)&len, sizeof(size_t));
	out.write((const char*)&comment[0], len);
}

void Product::newAmount(int amount)
{
	this->amount = amount;
}

void Product::newELocation(int amount)
{
	loc_end.setEndLocation(loc_start, amount);
}


bool Product::checkLocation(Location lstart, Location lend)
{
	int newStartspace = lstart.section * 10000 + lstart.shelf * 100 + lstart.number;
	int newEndspace = lend.section * 10000 + lend.shelf * 100 + lend.number;
	int Startspace = loc_start.section * 10000 + loc_start.shelf * 100 + loc_start.number;
	int Endspace = loc_end.section * 10000 + loc_end.shelf * 100 + loc_end.number;

	if (newEndspace<Startspace || newStartspace>Endspace)
		return true;

	return false;
}

bool Product::checkName_Date(const string& name, const Date expiryD)
{
	if (name.compare(product_name) == 0 && expiry.Same_date(expiryD))
		return true;
	
	return false;
}

bool Product::expired_date(const Date e1)
{
	if (expiry.ExpiredDate(e1))
		return true;

	return false;
}

bool Product::compareEdate(const Date d2)
{
	if (expiry.DateCompare(d2))
		return true;

	return false;
}

const string Product::get_productname() const
{
	return product_name;
}

const string Product::get_unit() const
{
	return unit;
}

const string Product::get_producer() const
{
	return producer;
}

const string Product::get_comment() const
{
	return comment;
}

const int Product::get_amount() const
{
	return amount;
}

const Date Product::get_expiryDate() const
{
	return expiry;
}

const Date Product::get_placedDate() const
{
	return placed_date;
}

const Location Product::get_Slocation() const
{
	return loc_start;
}

const Location Product::get_Elocation() const
{
	return loc_end;
}
