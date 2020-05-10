#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Product.h"
using namespace std;

class Storehouse
{
public:
	Storehouse();
	Storehouse(ifstream& in);

	void AddProduct(const Product& obj);
	bool AvailableLocation(const Location l1, int amount);
	void SaveData(ofstream& out) const;

	const int getCount() const;

private:
	vector <Product> products;
	int productsCount;
};

