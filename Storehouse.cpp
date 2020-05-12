#include "Storehouse.h"
int Storehouse::CurIndex = 0;
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
	cout << "Products in the storehouse: " << endl;
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

}

const int Storehouse::getCount() const
{
	return productsCount;
}

const Location Storehouse::getELoc(int index) const
{
	return products[index].get_Elocation();
}
