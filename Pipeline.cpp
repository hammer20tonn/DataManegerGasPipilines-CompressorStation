 #include "Pipeline.h"

#include <fstream>
#include <vector>

#include "utils.h"
using namespace std;

int Pipeline::MaxID = 0;

Pipeline::Pipeline()
{
	id = MaxID++;
	name = "Unknown";
	length = 0;
	diameter = 0;
	repair = false;
}

int Pipeline::getId() const {
	return id;
}

string Pipeline::getName() const {
	return name;
}

int Pipeline::getLength() const {
	return length;
}

int Pipeline::getDiameter() const {
	return diameter;
}

void Pipeline::load(ifstream& fin) {
	fin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(fin, name);
	fin >> length;
	fin >> diameter;
	fin >> repair;
}


void Pipeline::setName(std::string& name_) {
	name = name_;
}

void Pipeline::setLength(int length_) {
	length = length_;
}


void Pipeline::save(ofstream& fout) const {
	fout << name << endl << length << endl << diameter << endl << repair << endl;
}








ostream& operator << (ostream& out, const Pipeline& s)
{
	PRINT_PARAM(cout, s.id);
	PRINT_PARAM(cout, s.name);
	PRINT_PARAM(cout, s.length);
	PRINT_PARAM(cout, s.diameter);
	PRINT_PARAM(cout, s.repair);
	return out;
}
istream& operator >> (istream& in, Pipeline& s)
{
	cout << "Type name: ";
	INPUT_LINE(in, s.name);
	cout << "Type length: ";
	s.length = GetCorrectNumber(0, 1500);
	cout << "Type diameter: ";
	s.diameter = GetCorrectNumber(0, 1400);
	cout << "Type class repair: ";
	s.repair = GetCorrectNumber(0, 1);
	return in;
}