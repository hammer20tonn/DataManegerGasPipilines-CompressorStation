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
	int ClassStation;
	int id;
	int LengthOfStableWorkshop;
public:
	std::string getName() const;
	int getLengthOfWorkshop() const;
	int getLengthOfStableWorkshop() const;
	int getId() const;
	int getClassStation() const;


	void load(std::ifstream& fin);
	void save(std::ofstream& fout) const;


	void editLengthOfStableWorkshop(int command); // 1 - +1, 0 - -1


	static void SearchMaxId(std::set<Compressedstation>& s);

	Compressedstation();
	bool operator<(const Compressedstation& other) const {
		return id < other.id;
	}

	friend std::ostream& operator << (std::ostream& out, const Compressedstation& s);
	friend std::istream& operator >> (std::istream& in, Compressedstation& s);
};