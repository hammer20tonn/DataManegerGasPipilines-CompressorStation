#include "Mainthread.h"
#include <vector>

#include "utils.h"




#include <iostream>
#include <fstream>

#include "Pipeline.h"

#include "Compressedstation.h"

#include "gtn.h"

#include <chrono>
#include <format>
#include <set>



using namespace std;


Mainthread::Mainthread() : Pipelines(), Compressedstations(), my_gtn(Pipelines, Compressedstations)
{
}



void Mainthread::EditPipeline(Pipeline& s, int num)
{
	s.repair = num;
}






void Mainthread::gtnMenu()
{
	while (1) {
		cout << "==== Gas transmission network ====" << endl
			<< "1. Create new network" << endl
			<< "2. Print information" << endl
			<< "3. Topologycal sort" << endl
			<< "4. Back" << endl
			<< "0. Exit" << endl
			<< "Choose action: ";
		switch (GetCorrectNumber(0, 4)) {
			case 0: {
				exit(0); // Exit
			}
			case 1: {
				cin >> my_gtn;
				break;
			}
			case 2: {
				cout << my_gtn;
				break;
			}
			case 3: {
				my_gtn.getTopologicalSort();
				break;
			}
			case 4: {
				return;
			}
		}
	}
}


void Mainthread::PipelineMenu()
{
	vector<reference_wrapper<Pipeline>> PipelineMask;
	int command;
	int num;
	while (1) {
		cout << "==== Pipeline menu ====" << endl
			<< "1. Create new pipeline" << endl
			<< "2. Edit repair('true' - 1/'false' - 0)" << endl
			<< "3. Print information about all" << endl
			<< "4. Filter by name" << endl
			<< "5. Filtering by feature in repair" << endl
			<< "6. Select by id" << endl
			<< "7. Back" << endl
			<< "0. Exit" << endl
			<< "Choose action: ";
		switch (GetCorrectNumber(0, 7)) {
		case 0: {
			exit(0); // Exit
		}
		case 1: {
			Pipeline pl;
			cin >> pl;
			Pipelines.insert(pl);
			break;
		}
		case 2: {
			cout << "['true' - 1, 'false' - 0]: ";
			command = GetCorrectNumber(0, 1);
			try {
				Pipeline& pl = Select<Pipeline, std::set>(Pipelines);
				EditPipeline(pl, command); // Edit
			}
			catch (const std::runtime_error& e) {
				cout << e.what() << endl;
			}
			break;
		}
		case 3: {
			// Print
			for (auto& st : Pipelines)
				cout << st << endl;
			break;
		}
		case 4: { // filtering by name
			PipelineMask.clear();
			string name = "Unknown";
			cout << "Type name: ";
			INPUT_LINE(cin, name);
			for (auto it = Pipelines.begin(); it != Pipelines.end(); ++it) {
				if (CheckByName<Pipeline>(*it, name)) {
					cout << *it;
					PipelineMask.push_back(std::ref(const_cast<Pipeline&>(*it)));
				}
			}
			if (!PipelineMask.empty()) {
				editPipeline(PipelineMask);
			}
			else {
				cerr << "Not found" << endl;
			}
			break;
		}
		case 5: {
			PipelineMask.clear();
			cout << "Type ('true' - 1, 'false' - 0): ";
			num = GetCorrectNumber(0, 1);

			for (auto it = Pipelines.begin(); it != Pipelines.end(); ++it) {
				if (CheckByRepair<Pipeline>(*it, num)) {
					cout << *it;
					PipelineMask.push_back(std::ref(const_cast<Pipeline&>(*it)));
				}
			}
			if (!PipelineMask.empty()) {
				editPipeline(PipelineMask);
			}
			else {
				cerr << "Not found" << endl;
			}
			break;
		}
		case 6: {
			cout << "=== Batch editing ===" << endl << "Enter the IDs one by one. When you feel it's time to stop, type 'stop'." << endl;
			PipelineMask.clear();
			
			for (size_t i = 0; i < Pipelines.size(); i++)
			{
				try {
					Pipeline& pl = Select<Pipeline, std::set>(Pipelines, GetMax<Pipeline, std::set>(Pipelines)+1);
					cout << pl;
					PipelineMask.push_back(std::ref(pl));
				}
				catch (const runtime_error& e) {
					break;
				}
			}
			if (!PipelineMask.empty()) {
				editPipeline(PipelineMask);
			}
			break;
		}
		case 7: {
			// Back
			return;
		}
		default:
		{
			cout << "Wrong action" << endl;
			break;
		}
		}
	}
}








void Mainthread::EditCompressedstation(Compressedstation& s, int num)
{
	int LengthOfStableWorkshop = s.LengthOfStableWorkshop;
	if (LengthOfStableWorkshop + 1 > s.LengthOfWorkshop || LengthOfStableWorkshop - 1 < 0) {
		cout << "The number of operating workshops exceeds the total number." << endl;
		return;
	}
	s.LengthOfStableWorkshop += (num == 1) ? 1 : -1;
}











void Mainthread::editCompressedstation(vector<reference_wrapper<Compressedstation>>& CompressedstationMask) {
	int num;
	cout << "['+1' - 1, '-1' - 0, stop - 2, delete - 3]: ";
	num = GetCorrectNumber(0, 3);
	if (num == 2) {
		return;
	} else if (num == 3) {
		set<Compressedstation> Compressedstations_new;
		int i = 0;
		for (const Compressedstation cs : Compressedstations) {
			if (cs.id != CompressedstationMask[i].get().id) {
				Compressedstations_new.insert(cs);
			}
			i++;
			if (i >= CompressedstationMask.size()) {
				break;
			}
		}
		Compressedstations = Compressedstations_new;
		return;
	}
	for (auto& ref : CompressedstationMask) {
		EditCompressedstation(ref, num);
	}
}





void Mainthread::editPipeline(vector<reference_wrapper<Pipeline>>& PipelineMask) {
	int num;
	cout << "['true' - 1, 'false' - 0, stop - 2, delete - 3]: ";
	num = GetCorrectNumber(0, 3);
	if (num == 2) {
		return;
	}
	else if (num == 3) {
		set<Pipeline> Pipelines_new;
		int i = 0;
		for (const Pipeline pl : Pipelines) {
			if (pl.id != PipelineMask[i].get().id) {
				Pipelines_new.insert(pl);
			}
			i++;
			if (i >= PipelineMask.size()) {
				break;
			}
		}
		Pipelines = Pipelines_new;
		return;
	}
	for (auto& ref : PipelineMask) {
		EditPipeline(ref, num);
	}
}






void Mainthread::CompressedstationMenu()
{
	vector<reference_wrapper<Compressedstation>> CompressedstationMask;
	int command;
	int num;
	while (1) {
		cout << "==== Compressed station menu ====" << endl
			<< "1. Create new compressed station" << endl
			<< "2. Edit length Of workshop('-1' - 0/'+1' - 1)" << endl
			<< "3. Print information about all" << endl
			<< "4. Filter by name" << endl
			<< "5. Filter by percentage of idle workshops" << endl
			<< "6. Select by id" << endl
			<< "7. Back" << endl
			<< "0. Exit" << endl
			<< "Choose action: ";
		switch (GetCorrectNumber(0, 7)) {
		case 0: {
			exit(0); // Exit
		}
		case 1: {
			Compressedstation cs;
			cin >> cs;
			Compressedstations.insert(cs);
			break;
		}
		case 2: {
			cout << "['+1' - 1, '-1' - 0]: ";
			command = GetCorrectNumber(0, 1);
			try {
				Compressedstation& cs = Select<Compressedstation, std::set>(Compressedstations);
				EditCompressedstation(cs, command); // Edit
			}
			catch (const std::runtime_error& e) {
				cerr << e.what() << endl;
			}
			break;
		}
		case 3: {
			// Print
			for (auto& st : Compressedstations)
				cout << st << endl;
			break;
		}
		case 4: {
			CompressedstationMask.clear();
			string name = "Unknown";
			cout << "Type name: ";
			INPUT_LINE(cin, name);
			for (auto it = Compressedstations.begin(); it != Compressedstations.end(); ++it) {
				if (CheckByName<Compressedstation>(*it, name)) {
					cout << *it;
					CompressedstationMask.push_back(std::ref(const_cast<Compressedstation&>(*it)));
				}
			}
			if (!CompressedstationMask.empty()) {
				editCompressedstation(CompressedstationMask);
			}
			else {
				cerr << "Not found" << endl;
			}
			break;
		}
		case 5: {
			CompressedstationMask.clear();
			cout << "1. 100 - 80" << endl
				<< "2. 79 - 59" << endl
				<< "3. 58 - 38" << endl
				<< "4. 37 - 17" << endl
				<< "5. 16 - 0" << endl;
			num = GetCorrectNumber(1, 5);
			for (auto it = Compressedstations.begin(); it != Compressedstations.end(); ++it) {
				if (CheckByPercentage<Compressedstation>(*it, num)) {
					cout << *it;
					CompressedstationMask.push_back(std::ref(const_cast<Compressedstation&>(*it)));
				}
			}
			if (!CompressedstationMask.empty()) {
				editCompressedstation(CompressedstationMask);
			}
			else {
				cerr << "Not found" << endl;
			}
			break;
		}
		case 6: {
			cout << "=== Batch editing ===" << endl << "Enter the IDs one by one. When you feel it's time to stop, type 'stop'." << endl;

			CompressedstationMask.clear();

			for (size_t i = 0; i < Compressedstations.size(); i++)
			{
				try {
					Compressedstation& pl = Select<Compressedstation, std::set>(Compressedstations, GetMax<Compressedstation, std::set>(Compressedstations)+1);
					CompressedstationMask.push_back(std::ref(pl));
				}
				catch (const runtime_error& e) {
					cerr << e.what() << endl;
					break;
				}
			}
			if (!CompressedstationMask.empty()) {
				editCompressedstation(CompressedstationMask);
			}
			break;
		}
		case 7: {
			return;
		}
		default:
		{
			cerr << "Wrong action" << endl;
			break;
		}
		}
	}
}






Pipeline Mainthread::LoadPipeline(ifstream& fin)
{
	Pipeline s;
	fin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(fin, s.name);
	fin >> s.length;
	fin >> s.diameter;
	fin >> s.repair;
	fin >> s.cs1;
	fin >> s.cs2;
	fin >> s.InGTN;
	fin >> s.id;
	return s;
}

Compressedstation Mainthread::LoadCompressedstation(ifstream& fin)
{
	Compressedstation s;
	fin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(fin, s.name);
	fin >> s.LengthOfWorkshop;
	fin >> s.LengthOfStableWorkshop;
	fin >> s.ClassStation;
	fin >> s.id;
	return s;
}


void Mainthread::SavePipeline(ofstream& fout, const Pipeline& s)
{
	fout << s.name << endl << s.length << endl << s.diameter << endl << s.repair << endl << s.cs1 << endl << s.cs2 << endl << s.InGTN << endl << s.id << endl;
}

void Mainthread::SaveCompressedstation(ofstream& fout, const Compressedstation& s)
{
	fout << s.name << endl << s.LengthOfWorkshop << endl << s.LengthOfStableWorkshop << endl << s.ClassStation << endl << s.id << endl;
}












void Mainthread::saveFunction() {
	string file_string;
	cout << "Type file name: ";
	INPUT_LINE(cin, file_string);
	ofstream fout;
	fout.open(file_string, ios::out);
	if (fout.is_open())
	{
		fout << Compressedstations.size() << endl;
		fout << Pipelines.size() << endl;
		for (Compressedstation st : Compressedstations)
			SaveCompressedstation(fout, st);
		for (Pipeline st : Pipelines)
			SavePipeline(fout, st);
		fout.close();
	}
	else {
		cerr << "The file cannot be opened." << endl;
	}
}







void Mainthread::loadFunction() {
	Pipelines.clear();
	Compressedstations.clear();
	ifstream fin;
	string file_string;
	cout << "Type file name: ";
	INPUT_LINE(cin, file_string);
	fin.open(file_string, ios::in);
	if (fin.is_open())
	{
		int countPipeline;
		int countCompressedstation;
		fin >> countCompressedstation;
		fin >> countPipeline;
		while (countCompressedstation--)
		{
			Compressedstations.insert(LoadCompressedstation(fin));
		}
		while (countPipeline--)
		{
			Pipelines.insert(LoadPipeline(fin));
		}
		fin.close();
	}
	else {
		cerr << "The file cannot be opened." << endl;
	}
	int MaxIdPipelines;
	int MaxIdCompressedstations;
	if (!Pipelines.empty()) {
		MaxIdPipelines = Pipelines.rbegin()->id;
		Pipeline::setMaxId(MaxIdPipelines+1);
	}
	if (!Compressedstations.empty()) {
		MaxIdCompressedstations = Compressedstations.rbegin()->id;
		Compressedstation::setMaxId(MaxIdCompressedstations + 1);
	}
	for (const Pipeline& i_ : Pipelines) {
		if (i_.InGTN) {
			Compressedstation* foundCs1 = nullptr;
			Compressedstation* foundCs2 = nullptr;
			for (const Compressedstation& i : Compressedstations) {
				if (i.id == i_.cs1) {
					foundCs1 = const_cast<Compressedstation*>(&i);
				}
				if (i.id == i_.cs2) {
					foundCs2 = const_cast<Compressedstation*>(&i);
				}
				if (foundCs1 && foundCs2) {
					break;
				}
			}
			if (foundCs1 && foundCs2) {
				Compressedstation& cs1 = *foundCs1;
				Compressedstation& cs2 = *foundCs2;
				Connection cn(cs1, i_, cs2);
				my_gtn.Connections.push_back(cn);
			}
		}
	}
}

