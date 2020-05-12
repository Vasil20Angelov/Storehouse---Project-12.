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
	static int CurIndex;

	Storehouse();
	Storehouse(ifstream& in);

	void SaveData(ofstream& out) const;
	void ProductsList() const;
	void resetCurIndex();
	void AddProduct(const Product& obj);
	bool AvailableLocation(const Location l1, const Location l2);
	int Name_date_Match(const string& name, const Date expiryD);
	

	const int getCount() const;
	const Location getELoc(int index) const;
private:
	vector <Product> products;
	int productsCount;
};

