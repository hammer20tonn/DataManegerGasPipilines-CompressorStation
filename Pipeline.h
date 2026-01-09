#pragma once
#include <iostream>
#include <string>
#include <fstream>
class Pipeline
{
	int id;
	static int MaxID;
	std::string name;
	int length; // длина газопровода
	int diameter; // Диаметр
public:
	bool repair = false; // в ремонте (true/false)
	int getId() const;
	std::string getName() const;
	int getLength() const;
	int getDiameter() const;



	//void setId(int id_);
	void setName(std::string& name_);
	void setLength(int length_);

	//void setDiameter(int diameter_);
	void load(std::ifstream& fin);


	Pipeline();
	bool operator<(const Pipeline& other) const {
		return id < other.id;
	}
	friend std::ostream& operator << (std::ostream& out, const Pipeline& s);
	friend std::istream& operator >> (std::istream& in, Pipeline& s);
};