#include <iostream>
#include <fstream>
#include <string>
#include "Storehouse.h"
#include "Product.h"
#include "Location.h"
#include "Date.h"
#include "System.h"
using namespace std;

string System::Lfile = "Logfile.bin";

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
	cout << "Enter file name..." << endl;
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
	return true;
}

bool System::Savetofile()
{
	ofstream file(file_location, ios::binary);
	if (!file)
	{
		cout << "Error! Couldn't open the file!" << endl;
		return false;
	}
	storehouse.SaveData(file);
	return true;
}

bool System::AddtoLogfile(Date logDate, string product_name, int amount, const char sign)
{
	ofstream logfile(Lfile, ios::binary, ios::app);
	if (!logfile)
	{
		cout << "Error! Couldn't open the log file!" << endl;
		return false;
	}
	logfile.write((const char*)&logDate, sizeof(Date));
	size_t len = product_name.size();
	logfile.write((const char*)&len, sizeof(size_t));
	logfile.write((const char*)&product_name[0], len);
	logfile.write((const char*)&amount, sizeof(int));
	logfile.write(&sign, 1);

	return true;
}

void System::AddProduct()
{
	string product_name, unit, producer, comment;
	int amount;
	int count = storehouse.getCount();
	Date expiry_date, log_date;
	Location start_loc, end_loc;
	Product product;
	cout << "\nEnter date" << endl;
	log_date.Set_Date();

	cout << "\nProduct: ";
	cin.ignore();
	getline(cin, product_name);
	cout << "\nUnit (kg/l): ";
	do
	{
		cin >> unit;
		if (unit.compare("kg") == 0 || unit.compare("l") == 0)
			break;
		else
			cout << "Enter kg or l." << endl;
	} while (true);

	cout << "\nAmount: ";
	cin >> amount;
	cout << "\nProducer: ";
	cin.ignore();
	getline(cin, producer);
	cout << "\nExpiry date:" << endl;
	expiry_date.Set_Date();
	cout << "\nComment: ";
	cin.ignore();
	getline(cin, comment);

	bool placed = false;
	if (count == 0)
	{
		start_loc.section = 1;
		start_loc.shelf = 1;
		start_loc.number = 0;
		product = Product(product_name, unit, producer, comment, amount, expiry_date, log_date, start_loc);
		end_loc = product.get_Elocation();
		storehouse.AddProduct(product);
		placed = true;
	}
	else
	{
		int CurIndex = -1, curIndex2 = -2;
		do
		{
			CurIndex = storehouse.Name_date_Match(product_name, expiry_date);
			if (CurIndex != -1 && curIndex2 != CurIndex)
			{
				start_loc.setStartLocation(storehouse.getELoc(CurIndex));
				end_loc.setEndLocation(start_loc, amount);
				if (storehouse.AvailableLocation(start_loc, end_loc))
				{
					product = Product(product_name, unit, producer, comment, amount, expiry_date, log_date, start_loc);
					storehouse.AddProduct(product);
					placed = true;
					storehouse.resetCurIndex();
					break;
				}
				curIndex2 = CurIndex;
			}
			else
				break;
		} while (true);

		if (!placed)
		{
			for (int i = 0; i < 10; i++)
			{
				start_loc.setRandomLocation();
				end_loc.setEndLocation(start_loc, amount);
				if (storehouse.AvailableLocation(start_loc, end_loc))
				{
					product = Product(product_name, unit, producer, comment, amount, expiry_date, log_date, start_loc);
					storehouse.AddProduct(product);
					placed = true;
					break;
				}
			}
		}

		if (!placed)
		{
			for (int i = 0; i < count; i++)
			{
				start_loc.setStartLocation(storehouse.getELoc(i));
				end_loc.setEndLocation(start_loc, amount);
				if (storehouse.AvailableLocation(start_loc, end_loc))
				{
					product = Product(product_name, unit, producer, comment, amount, expiry_date, log_date, start_loc);
					storehouse.AddProduct(product);
					placed = true;
					break;
				}
			}
		}
	}

	if (!placed)
		cout << "The product couldn't be added in the storehouse!" << endl;
	else
	{
		cout << "The product has been added in the storehouse at location: ";
		start_loc.showLocation();
		cout << " to ";
		end_loc.showLocation();
		cout << endl;
	}

}

int System::run()
{
	if (!OpenFile())
		return 0;
	//storehouse.ProductsList();
	AddProduct();
	AddProduct();
	AddProduct();
	if (!Savetofile())
		return 0;
	
	storehouse.ProductsList();
	return 0;
}
