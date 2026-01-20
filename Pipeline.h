#pragma once
#include <iostream>
#include <string>

class Pipeline
{
public:
	int id;
	static int MaxID;
	std::string name;
	int length; // длина газопровода
	int diameter; // Диаметр
	bool repair = false; // в ремонте (true/false)
	mutable int cs1;
	mutable int cs2;
	mutable bool InGTN = false; // Включена ли в проект газотранспортной сети
	static void setMaxId(int maxid);
	Pipeline();

	void resetGTN() const;

	bool operator<(const Pipeline& other) const {
		return id < other.id;
	}
	friend std::ostream& operator << (std::ostream& out, const Pipeline& s);
	friend std::istream& operator >> (std::istream& in, Pipeline& s);
};