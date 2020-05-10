#include <iostream>
#include <fstream>
#include <string>
#include "Storehouse.h"
#include "Product.h"
#include "Location.h"
#include "Date.h"
#include "System.h"

System::System()
{

}

System& System::i()
{
	static System sys;
	return sys;
}

void System::ShowMenu() const
{

}

bool System::OpenFile()
{
	cout << "Enter file location..." << endl;
	cin >> file_location;
	file_location + ".bin";
	ofstream file(file_location, ios::binary | ios::app);
	if (!file)
	{
		cout << "Error! Couldn't open the file!" << endl;
		return false;
	}
	file.close();
	ifstream fread(file_location, ios::binary);
	if (!fread)
	{
		cout << "Error! Couldn't open the file!" << endl;
		return false;
	}
	fread.seekg(0, ios::end);
	if (fread.tellg() == 0)
		cout << "The file is opened. The storehouse is empty." << endl;
	else
	{
		fread.seekg(0, ios::beg);
		storehouse = Storehouse(fread);
		cout << "Information has been loaded successfully!" << endl;
	}
	fread.close();

}

void System::AddProduct()
{
	string product_name, unit, producer, comment;
	int amount;
	Date expiry_date, log_date;
	Location start_loc, end_loc;
	Product product;
	cout << "Enter date:";
	log_date.Set_Date();

	cout << "Product: ";
	cin.ignore();
	getline(cin, product_name);
	cout << "Unit (kg/l): ";
	do
	{
		cin >> unit;
		if (unit.compare("kg") == 0 || unit.compare("l") == 0)
			break;
		else
			cout << "Enter kg or l." << endl;
	} while (true);

	cout << "Amount: ";
	cin >> amount;
	cout << "Producer: ";
	cin.ignore();
	getline(cin, producer);
	cout << "Expiry date:" << endl;
	expiry_date.Set_Date();
	cout << "Comment: ";
	cin.ignore();
	getline(cin, comment);

	if (storehouse.getCount() == 0)
	{
		start_loc.section = 1;
		start_loc.shelf = 1;
		start_loc.number = 1;
		product = Product(product_name, unit, producer, comment, amount, expiry_date, log_date, start_loc);
		storehouse.AddProduct(product);
	}
	else
	{

	}

}

void System::run()
{
	OpenFile();
}
