#pragma once
#include <iostream>
#include <string>
#include <fstream>
class Compressedstation
{
private:
	static int MaxID;
	std::string name;
	int LengthOfWorkshop;
	int LengthOfStableWorkshop;
	int ClassStation;
	int id;
public:
	std::string getName() const;
	int getLengthOfWorkshop() const;
	int getLengthOfStableWorkshop() const;
	int getId() const;
	int getClassStation() const;

	//void setName(std::string name_);
	//void setLengthOfWorkshop(int LengthOfWorkshop_);
	void setLengthOfStableWorkshop(int LengthOfStableWorkshop_);
	//void setId(int id_);
	//void setClassStation(int ClassStation_);

	void load(std::ifstream& fin);
	Compressedstation();
	bool operator<(const Compressedstation& other) const {
		return id < other.id;
	}

	friend std::ostream& operator << (std::ostream& out, const Compressedstation& s);
	friend std::istream& operator >> (std::istream& in, Compressedstation& s);
};