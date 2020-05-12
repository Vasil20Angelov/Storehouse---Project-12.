#pragma once
struct Location
{
	int section;
	int shelf;
	int number;

	void setStartLocation(const Location& l1); // Sets a location next to other product
	void setRandomLocation(); // Sets a random location in the storehouse
	void setEndLocation(const Location& l1, int amount); // Sets the ending location according to the starting possition and the amount
	void showLocation() const;

};