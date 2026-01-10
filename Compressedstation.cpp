#include "Compressedstation.h"

#include <fstream>


#include "utils.h"
using namespace std;

int Compressedstation::MaxID = 0;

Compressedstation::Compressedstation()
{
	id = MaxID++;
	name = "Unknown";
	LengthOfWorkshop = 0; // количетсво цехов
	LengthOfStableWorkshop = 0; // количество работающих цехов
	ClassStation = 0;
}


string Compressedstation::getName() const {
	return name;
}
int Compressedstation::getId() const {
	return id;
}
int Compressedstation::getLengthOfWorkshop() const {
	return LengthOfWorkshop;
}
int Compressedstation::getLengthOfStableWorkshop() const {
	return LengthOfStableWorkshop;
}
int Compressedstation::getClassStation() const {
	return ClassStation;
}



void Compressedstation::load(ifstream& fin) {
	fin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(fin, name);
	fin >> LengthOfWorkshop;
	fin >> LengthOfStableWorkshop;
	fin >> ClassStation;
}




void Compressedstation::save(ofstream& fout) const {
	fout << name << endl << LengthOfWorkshop << endl << LengthOfStableWorkshop << endl << ClassStation << endl;
}


void Compressedstation::editLengthOfStableWorkshop(int command) {
	if ((LengthOfStableWorkshop + 1 > LengthOfWorkshop && command == 1) || (LengthOfStableWorkshop - 1 < 0 && command == 0)) {
		cerr << "The number of operating workshops exceeds the total number." << endl;
		return;
	}
	if (command == 0) {
		LengthOfStableWorkshop -= 1;
	} else if (command == 1) {
		LengthOfStableWorkshop += 1;
	}
	else {
		cerr << "System error" << endl;
	}
}



ostream& operator << (ostream& out, const Compressedstation& s)
{
	PRINT_PARAM(cout, s.id);
	PRINT_PARAM(cout, s.name);
	PRINT_PARAM(cout, s.LengthOfWorkshop);
	PRINT_PARAM(cout, s.LengthOfStableWorkshop);
	PRINT_PARAM(cout, s.ClassStation);
	return out;
}
istream& operator >> (istream& in, Compressedstation& s)
{
	cout << "Type name: ";
	INPUT_LINE(in, s.name);
	cout << "Type length of workshop: ";
	s.LengthOfWorkshop = GetCorrectNumber(0, 1400);
	cout << "Type length of stable workshop: ";
	s.LengthOfStableWorkshop = GetCorrectNumber(0, s.LengthOfWorkshop);
	cout << "Type class station: ";
	s.ClassStation = GetCorrectNumber(0, 5);
	return in;
}