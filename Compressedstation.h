#pragma once
#include <iostream>
#include <string>

class Compressedstation
{
public:
	static int MaxID;
	std::string name;
	int LengthOfWorkshop;
	int LengthOfStableWorkshop;
	int ClassStation;
	int id;

	static void setMaxId(int maxid);

	Compressedstation();
	bool operator<(const Compressedstation& other) const {
		return id < other.id;
	}

	friend std::ostream& operator << (std::ostream& out, const Compressedstation& s);
	friend std::istream& operator >> (std::istream& in, Compressedstation& s);
};