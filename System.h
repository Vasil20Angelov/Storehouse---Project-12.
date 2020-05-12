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

	void ShowMenu() const;
	bool OpenFile();
	bool Savetofile();
	bool AddtoLogfile(Date logDate, string product_name, int amount,const char sign);
	void AddProduct();

	int run();
private:
	System();
	Storehouse storehouse;
	string file_location;
};

