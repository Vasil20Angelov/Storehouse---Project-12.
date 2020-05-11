#include "Storehouse.h"

Storehouse::Storehouse()
{
	productsCount = 0;
}

Storehouse::Storehouse(ifstream& in)
{
	in.read((char*)&productsCount, sizeof(int));

	for (int i = 0; i < productsCount; i++)
	{
		products[i].load_info(in);
	}
}

void Storehouse::AddProduct(const Product& obj)
{
	products.push_back(obj);
	productsCount++;
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

bool Storehouse::Name_date_Match(const string& name, const Date expiryD, int amount)
{
	for (int i = 0; i < productsCount; i++)
	{
		if (products[i].checkName_Date(name, expiryD))
		{

		}
	}
}

void Storehouse::SaveData(ofstream& out) const
{
	out.write((const char*)&productsCount, sizeof(int));
	
	for (int i = 0; i < productsCount; i++)
	{
		products[i].save_info(out);
	}
}

const int Storehouse::getCount() const
{
	return productsCount;
}
