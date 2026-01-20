#include "Compressedstation.h"




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


void Compressedstation::setMaxId(int maxid) {
	MaxID = maxid;
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