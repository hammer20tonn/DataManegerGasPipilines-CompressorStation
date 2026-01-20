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

void Pipeline::resetGTN() const {
	InGTN = false;
	cs1 = 0;
	cs2 = 0;
}

void Pipeline::setMaxId(int maxid) {
	MaxID = maxid;
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
	//s.diameter = GetCorrectNumber(0, 1400);
	cout << "Type class repair: ";
	s.repair = GetCorrectNumber(0, 1);
	return in;
}