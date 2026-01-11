 #include "Pipeline.h"


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
	cs1 = 0;
	cs2 = 0;
	InGTN = false;
}

void Pipeline::SearchMaxId(set<Pipeline>& s) {
	if (!s.empty()) {
		MaxID = (s.rbegin()->getId())+1;
	}
}



void Pipeline::resetGTN() const {
	InGTN = false;
	cs1 = 0;
	cs2 = 0;
}

void Pipeline::setMaxId(int maxid) {
	MaxID = maxid;
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
	fin >> cs1;
	fin >> cs2;
	fin >> InGTN;
	fin >> id;
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
	std::vector<int> diameters = { 500, 700, 1000, 1400 };
	cout << "Type name: ";
	INPUT_LINE(in, s.name);
	cout << "Type length: ";
	s.length = GetCorrectNumber(0, 1500);
	cout << "Type diameter [500, 700, 1000, 1400]: ";
	s.diameter = GetCorrectNumberAllowed(diameters);
	cout << "Type class repair: ";
	s.repair = GetCorrectNumber(0, 1);
	return in;
}