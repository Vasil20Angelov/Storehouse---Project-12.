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

void System::ShowMenu(bool file_opened) const
{
	if (file_opened)
	{
		cout << "\nEnter a command" << endl;
		cout << "1. Add a product" << endl;
		cout << "2. Remove a product" << endl;
		cout << "3. Show all products in the storehouse" << endl;
		cout << "4. Check log info" << endl;
		cout << "5. Clear the storehouse" << endl;
		cout << "6. Save" << endl;
		cout << "7. Save as" << endl;
		cout << "8. Close the opened file" << endl;
		cout << "9. Help" << endl;
		cout << "0. Exit" << endl;
		cout << ">> ";
	}
	else
	{
		cout << "Enter a command" << endl;
		cout << "1. Open a file" << endl;
		cout << "2. Help" << endl;
		cout << "0. Exit" << endl;
		cout << ">> ";
	}
}

void System::ShowHelp(bool file_opened) const
{
	cout << "\nHelp menu" << endl;
	if (!file_opened)
	{
		cout << "1. Opens a file by entered file name and loads the information from the file." << endl;
		cout << "2. Shows help information" << endl;
		cout << "0. Exists the program" << endl;
		cout << "\nNote: \n-> After you open a file, the other options will be unlocked" << endl;
	}
	else
	{
		cout << "1. Adds a product to the storehouse" << endl;
		cout << "2. Removes a certain amount from selected product" << endl;
		cout << "3. Shows information about the products in the storehouse" << endl;
		cout << "4. Shows all products that have been ever added or removed in the selected time piriod" << endl;
		cout << "5. Removes all expired products and all products which will expire in the next 5 days. Also calculates loses" << endl;
		cout << "6. Saves all changes";
		cout << "7. Saves all changes in another file" << endl;
		cout << "8. Closes the opened file" << endl;
		cout << "9. Shows help information" << endl;
		cout << "0. Exists the program" << endl;
		cout << "\nNotes:" << endl;
		cout << "-> After a file is closed, you have to open another to continue your work in the storehouse" << endl;
		cout << "-> The storehouse contains 100 sections, 10 shelfs in 1 section and each shelf has 10 columns(numbers)" << endl;
		cout << "-> In 1 column(number) can be contained 10kg/l of any product" << endl;
	}

	cout << "\nEnter any symbol to go back to the main menu... ";
	string s;
	cin >> s;
}

bool System::OpenFile()
{
	cout << "Enter file name (without the extension)\n>> ";
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
	ofstream logfile(Lfile, ios::binary | ios::app);
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
	logfile.close();
	return true;
}

bool System::RemoveProduct()
{
	if (storehouse.getCount() == 0)
	{
		cout << "The storehouse is empty" << endl;
		return true;
	}

	Date d;
	string name;
	int amount, total_amount = 0, index;
	cout << "\nEnter date" << endl;
	d.Set_Date();
	cout << "\nEnter a product: ";
	cin.ignore();
	getline(cin, name);
	cout << "\nEnter the amount you want to remove: ";
	cin >> amount;
	if (amount <= 0)
	{
		cout << "Nothing has been removed" << endl;
		return true;
	}

	int count = storehouse.getCount();
	for (int i = 0; i < count; i++)
	{
		if (name.compare(storehouse.getName(i)) == 0)
			total_amount += storehouse.getAmount(i);
	}

	if (total_amount == 0)
	{
		cout << name << " hasn't been found in the storehouse" << endl;
		return true;
	}
	if (total_amount < amount) // removes all products
	{
		cout << "You have only " << total_amount << " kg/l of this product. Do you want to remove all?" << endl;

		bool remove = false;
		do
		{
			char s;
			cout << "[Y]es/[N]o\n>> ";
			cin >> s;
			if (s == 'y' || s == 'Y')
			{
				remove = true;
				break;
			}
			if (s == 'n' || s == 'N')
				break;

		} while (true);

		if (remove)
		{
			for (int i = 0; i < count; i++)
			{
				if (name.compare(storehouse.getName(i)) == 0)
				{
					if (!AddtoLogfile(d, name, storehouse.getAmount(i), '-'))
						return false;

					cout << name << ", " << storehouse.getAmount(i) << storehouse.getUnit(i) << " with expiry date: ";
					storehouse.getEdate(i).Show_Date();
					cout << "\nLocated from ";
					storehouse.getSLoc(i).showLocation();
					cout << " to ";
					storehouse.getELoc(i).showLocation();
					cout << "  has been removed from the storehouse" << endl;

					storehouse.RemoveProduct(i);
				}
			}
			return true;
		}
		else
		{
			cout << "Nothing has been removed from the storehouse" << endl;
			return true;
		}

	}

	while (amount > 0)
	{
		index = storehouse.RemoveProducts(name);
		if (amount - storehouse.getAmount(index) >= 0)
		{
			if (!AddtoLogfile(d, name, storehouse.getAmount(index), '-'))
				return false;

			cout << storehouse.getAmount(index) << storehouse.getUnit(index) << " have been removed from " << name << " with expiry date: ";
			storehouse.getEdate(index).Show_Date();
			cout << "\nLocated from ";
			storehouse.getSLoc(index).showLocation();
			cout << " to ";
			storehouse.getELoc(index).showLocation();
			cout << "  has been removed from the storehouse" << endl << endl;

			amount -= storehouse.getAmount(index);
			storehouse.RemoveProduct(index);
		}
		else
		{
			if (!AddtoLogfile(d, name, amount, '-'))
				return false;

			cout << amount << " kg/l have been removed from " << name << " with expiry date: ";
			storehouse.getEdate(index).Show_Date();
			cout << "\nLocated from ";
			storehouse.getSLoc(index).showLocation();
			cout << " to ";
			storehouse.getELoc(index).showLocation();
			cout << endl;

			storehouse.SetNewAmount(index, storehouse.getAmount(index) - amount);
			storehouse.SetNewELocation(index, amount);
			
			break;
		}

	}

	return true;
}

bool System::Clear()
{	
	if (storehouse.getCount() == 0)
	{
		cout << "The storehouse is empty." << endl;
		return true;
	}

	Date Edate;
	int index, total_amount = 0;
	double price;
	bool newproduct = true;
	string name = "";
	cout << "\nEnter a date to remove all expired products and all products that will expire in the next 5 days" << endl;
	Edate.Set_Date();
	while (storehouse.CurIndex != storehouse.getCount())
	{
		index = storehouse.ClearStorehouse(Edate);
		if (index == -1)
			break;
		if (!AddtoLogfile(Edate, storehouse.getName(index), storehouse.getAmount(index), '-'))
			return false;

		if (name.compare(storehouse.getName(index)) != 0)
		{
			if (!newproduct)
				cout << "Loses: " << price * total_amount << endl;
			
			name = storehouse.getName(index);
			cout << "\nEnter price for 1 kg/l " << name << endl << ">> ";
			cin >> price;
			total_amount = storehouse.getAmount(index);
		}
		else
			total_amount += storehouse.getAmount(index);

		cout << storehouse.getName(index) << ", " << storehouse.getAmount(index) << storehouse.getUnit(index) << ", Expiry date: ";
		storehouse.getEdate(index).Show_Date();
		cout << endl;
		storehouse.RemoveProduct(index);
		newproduct = false;
	}

	if (newproduct)
		cout << "No products have been removed" << endl;
	else
		cout << "Loses: " << price * total_amount <<" leva" << endl;
	storehouse.resetCurIndex();

	return true;
}

bool System::ReadFromLogfile()
{
	string product_name;
	Date dFrom, dTo, logDate;
	int amount;
	char sign;
	cout << "Enter date from" << endl;
	dFrom.Set_Date();
	cout << "Enter date to" << endl;
	dTo.Set_Date();

	ifstream logfileR(Lfile, ios::binary);
	if (!logfileR)
	{
		cout << "Error! Couldn't open the log file!" << endl;
		return false;
	}
	while (!logfileR.eof())
	{
		logfileR.read((char*)&logDate, sizeof(Date));
		size_t len;
		logfileR.read((char*)&len, sizeof(size_t));
		product_name.resize(len);
		logfileR.read(&product_name[0], len);
		logfileR.read((char*)&amount, sizeof(int));
		logfileR.read((char*)&sign, 1);
		if (sign == '.')
			break;
		if (logDate.InPeriod(dFrom, dTo))
		{
			logDate.Show_Date();
			cout << " " << product_name << " " << amount << " ";
			if (sign == '+')
				cout << "Added" << endl;
			else
				cout << "Removed" << endl;
		}
		sign = '.';
	}
	logfileR.close();
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
		if (end_loc.section >= 100)
			cout << "Not enough space in the storehouse" << endl;
		else
		{
			storehouse.AddProduct(product);
			placed = true;
		}
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
				if (end_loc.section < 100)
				{
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
				if (end_loc.section < 100)
				{
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
		{
			for (int i = 0; i < count; i++)
			{
				start_loc.setStartLocation(storehouse.getELoc(i));
				end_loc.setEndLocation(start_loc, amount);
				if (end_loc.section < 100)
				{
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
	}

	if (!placed)
		cout << "The product couldn't be added in the storehouse!" << endl;
	else
	{
		if (AddtoLogfile(log_date, product_name, amount, '+'))
		{ 
		cout << "The product has been added in the storehouse at location: ";
		start_loc.showLocation();
		cout << " to ";
		end_loc.showLocation();
		cout << endl;
		}
	}
}

int System::run()
{
	bool file_opened = false;
	int option;
	do
	{
		if (!file_opened)
		{
			ShowMenu(file_opened);
			cin >> option;
			switch (option)
			{
			case 1:
			{	
				if (!OpenFile())
					return -1;
				file_opened = true;
				break;
			}
			case 2:
			{
				ShowHelp(file_opened);
				break;
			}
			case 0:
			{
				cout << "Exiting the program..." << endl;
				break;
			}
			default:
			{
				cout << "Invalid command!" << endl;
				break;
			}
			}
		}
		else
		{
			ShowMenu(file_opened);
			cin >> option;
			switch (option)
			{
			case 1: // add a product
			{
				AddProduct();
				break;
			}
			case 2: // remove
			{
				if (!RemoveProduct())
					return -1;
				break;
			}
			case 3: // show all products
			{
				storehouse.ProductsList();
				break;
			}
			case 4: // log info
			{
				ReadFromLogfile();
				break;
			}
			case 5: // clear
			{
				if (!Clear())
					return -1;
				break;
			}
			case 6: // save
			{
				if (!Savetofile())
					return -1;
				cout << "The information has been saved!" << endl;
				break;
			}
			case 7: // save as
			{
				string tempLoc = file_location;
				cout << "Enter the name of the file where you want to save the information (without the extension)\n>> ";
				cin >> file_location;
				file_location + ".bin";
				if (!Savetofile())
					return -1;
				file_location = tempLoc;
				cout << "The information has been saved!" << endl;
				break;
			}
			case 8: // close
			{
				file_opened = false;
				cout << "The opened file has been closed." << endl << endl;
				break;
			}
			case 9: // help
			{
				ShowHelp(file_opened);
				break;
			}
			case 0: // exit
			{
				cout << "Exiting the program..." << endl;
				break;
			}
			default:
			{
				cout << "Invalid option!" << endl;
				break;
			}
			}
		}

	} while (option != 0);

	return 0;
}
