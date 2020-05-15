#include <iostream>
#include <string>
#include "Storehouse.h"
using namespace std;

int Storehouse::CurIndex = 0;
int Storehouse::CurIndex2 = 0;

Storehouse::Storehouse()
{
	productsCount = 0;
}

Storehouse::Storehouse(ifstream& in)
{
	in.read((char*)&productsCount, sizeof(int));
	Product temp;
	for (int i = 0; i < productsCount; i++)
	{
		temp.load_info(in);
		products.push_back(temp);
	}
}

void Storehouse::resetCurIndex()
{
	CurIndex = 0;
	CurIndex2 = 0;
}

void Storehouse::SetNewAmount(int index, int amount)
{
	products[index].newAmount(amount);
}

void Storehouse::SetNewELocation(int index, int amount)
{
	products[index].newELocation(amount);
}

void Storehouse::AddProduct(const Product& obj)
{
	products.push_back(obj);
	productsCount++;
}

void Storehouse::RemoveProduct(int index)
{
	products.erase(products.begin() + index);
	productsCount--;
}

int Storehouse::RemoveProducts(const string& name)
{
	int minindex;
	for (int i = 0; i < productsCount; i++)
	{
		if(products[i].get_productname().compare(name)==0)
		{
			minindex = i;
			break;
		}
	}

	for (int i = minindex + 1; i < productsCount; i++)
	{
		if (products[i].get_productname().compare(name) == 0)
		{
			if (products[i].compareEdate(products[minindex].get_expiryDate()))
				minindex = i;
		
		}
	}

	return minindex;
}

int Storehouse::ClearStorehouse(const Date expiryD)
{
	for (int i = CurIndex; i < productsCount; i++)
	{
		if (products[i].expired_date(expiryD))
		{
			for (int CurIndex2 = i + 1; CurIndex2 < productsCount; CurIndex2++)
			{
				if (products[i].get_productname().compare(products[CurIndex2].get_productname()) == 0)
				{
					if (products[CurIndex2].expired_date(expiryD))
					{					
						return CurIndex2;
					}
				}
			}
			return i;
		}
		CurIndex++;
	}

	return -1;
}

bool Storehouse::AvailableLocation(const Location l1, const Location l2)
{
	for (int i = 0; i < productsCount; i++)
	{
		if (!products[i].checkLocation(l1, l2))
			return false;
	}
	return true;
}

int Storehouse::Name_date_Match(const string& name, const Date expiryD)
{
	for (int i = CurIndex; i < productsCount; i++)
	{
		if (products[i].checkName_Date(name, expiryD))
		{
			CurIndex = i + 1;
			return i;
		}
	}

	return -1;
}

void Storehouse::SaveData(ofstream& out) const
{
	out.write((const char*)&productsCount, sizeof(int));
	
	for (int i = 0; i < productsCount; i++)
	{
		products[i].save_info(out);
	}
}

void Storehouse::ProductsList() const
{
	cout << "\nProducts in the storehouse: " << endl;
	if (productsCount == 0)
		cout << "There aren't any products in the storehouse!" << endl;
	else
	{
		int pcount = productsCount;
		vector <Product> temp;
		temp = products;
		if (pcount == 1)
			cout << temp[0].get_productname() << " " << temp[0].get_amount() << "/" << temp[0].get_unit() << endl;
		else
		{
			for (int i = 0; i < pcount; i++)
			{
				int total_amount = temp[i].get_amount();
				for (int j = i + 1; j < pcount; j++)
				{
					if (temp[i].get_productname().compare(temp[j].get_productname()) == 0)
					{
						total_amount += temp[j].get_amount();
						swap(temp[j], temp[pcount - 1]);
						pcount--;
						j--;
					}

				}
				cout << temp[i].get_productname() << " " << total_amount << "/" << temp[i].get_unit() << endl;
			}
		}
	}

	cout << "\nDo you want to see more detailed list?" << endl;
	do
	{
		char s;
		cout << "[Y]es/[N]o\n>> ";
		cin >> s;
		if (s == 'n' || s == 'N')
			break;
		if (s == 'y' || s == 'Y')
		{
			for (int i = 0; i < productsCount; i++)
			{
				cout << "\n"<< i+1 <<". " << products[i].get_productname() << ", " << products[i].get_amount() << products[i].get_unit() << ", Added on: ";
				products[i].get_placedDate().Show_Date();
				cout << ", with expiry date: ";
				products[i].get_expiryDate().Show_Date();
				cout << "\nProduced by: " << products[i].get_producer() << ", Located at: ";
				products[i].get_Slocation().showLocation();
				cout << " to ";
				products[i].get_Elocation().showLocation();
				cout << "\nComment: " << products[i].get_comment() << endl;				
			}
			break;
		}
	} while (true);

}

const int Storehouse::getCount() const
{
	return productsCount;
}

const int Storehouse::getAmount(int index) const
{
	return products[index].get_amount();
}

const string Storehouse::getName(int index) const
{
	return products[index].get_productname();
}

const string Storehouse::getUnit(int index) const
{
	return products[index].get_unit();
}

const Date Storehouse::getEdate(int index) const
{
	return products[index].get_expiryDate();
}

const Location Storehouse::getSLoc(int index) const
{
	return products[index].get_Slocation();
}

const Location Storehouse::getELoc(int index) const
{
	return products[index].get_Elocation();
}
