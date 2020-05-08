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
	static System& i();
	
	void ShowMenu() const;
	bool OpenFile();
	void AddProduct();

	void run();
private:
	System();
	Storehouse storehouse;
	string file_location;
};

