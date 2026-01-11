#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Pipeline
{
private:
	int id;
	static int MaxID;
	std::string name;
	int length; // длина газопровода
	int diameter; // Диаметр
public:
	bool repair = false; // в ремонте (true/false)
	mutable int cs1;
	mutable int cs2;
	mutable bool InGTN = false; // Включена ли в проект газотранспортной сети
	static void setMaxId(int maxid);




	int getId() const;
	std::string getName() const;
	int getLength() const;
	int getDiameter() const;
	void resetGTN() const;

	void load(std::ifstream& fin);
	void save(std::ofstream& fout) const;


	static void SearchMaxId(std::set<Pipeline>& s);

	Pipeline();



	bool operator<(const Pipeline& other) const {
		return id < other.id;
	}
	friend std::ostream& operator << (std::ostream& out, const Pipeline& s);
	friend std::istream& operator >> (std::istream& in, Pipeline& s);
};