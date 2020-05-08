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
}

void System::run()
{
	OpenFile();
}
