#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Storehouse.h"
#include "Product.h"
#include "Location.h"
#include "Date.h"
using namespace std;

class System
{
public:
	static string Lfile;
	static System& i();

	void ShowMenu(bool file_opened) const;
	void ShowHelp(bool file_opened) const;
	bool OpenFile();
	bool Savetofile();
	bool AddtoLogfile(Date logDate, string product_name, int amount, const char sign);
	bool RemoveProduct();
	bool Clear();
	bool ReadFromLogfile();
	void AddProduct();

	int run();
private:
	System();
	Storehouse storehouse;
	string file_location;
};

