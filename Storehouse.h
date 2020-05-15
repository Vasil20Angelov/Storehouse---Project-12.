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
	static int CurIndex2;

	Storehouse();
	Storehouse(ifstream& in);

	void SaveData(ofstream& out) const;
	void ProductsList() const;
	void resetCurIndex();
	void SetNewAmount(int index, int amount);
	void SetNewELocation(int index, int amount);
	void AddProduct(const Product& obj);
	void RemoveProduct(int index);
	int RemoveProducts(const string& name);
	int ClearStorehouse(const Date expiryD);
	bool AvailableLocation(const Location l1, const Location l2);
	int Name_date_Match(const string& name, const Date expiryD);
	

	const int getCount() const;
	const int getAmount(int index) const;
	const string getName(int index) const;
	const string getUnit(int index) const;
	const Date getEdate(int index) const;
	const Location getSLoc(int index) const;
	const Location getELoc(int index) const;
private:
	vector <Product> products;
	int productsCount;
};

