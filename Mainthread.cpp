#include "Mainthread.h"
#include <vector>

#include "utils.h"




#include <iostream>
#include <fstream>

#include "Pipeline.h"

#include "Compressedstation.h"

#include <chrono>
#include <format>
#include <set>



using namespace std;




Mainthread::Mainthread() {
	set<Pipeline> Pipelines;
	set<Compressedstation> Compressedstations;
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
			Select<Pipeline>(Pipelines).repair = command; // Edit
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
					Pipeline& pl = Select<Pipeline>(Pipelines, GetMax(Pipelines)+1);
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











void Mainthread::editCompressedstation(vector<reference_wrapper<Compressedstation>>& CompressedstationMask) {
	int num;
	cout << "['+1' - 1, '-1' - 0, stop - 2, delete - 3]: ";
	num = GetCorrectNumber(0, 3);
	if (num == 2) {
		return;
	}
	else if (num == 3) {
		for (size_t i = 0; i < CompressedstationMask.size(); ++i) {
			const Compressedstation& station = CompressedstationMask[i].get();
			Compressedstations.erase(station);
		}
		return;
	}
	for (reference_wrapper<Compressedstation>& ref : CompressedstationMask) {
		ref.get().editLengthOfStableWorkshop(num);
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
		for (size_t i = 0; i < PipelineMask.size(); ++i) {
			const Pipeline& pl = PipelineMask[i].get();
			Pipelines.erase(pl);
		}
		return;
	}
	for (reference_wrapper<Pipeline>& ref : PipelineMask) {
		ref.get().repair = num;
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
			Select<Compressedstation>(Compressedstations).editLengthOfStableWorkshop(num);
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
					CompressedstationMask.push_back(std::ref(const_cast<Compressedstation&>(*it)));
				}
			}
			if (!CompressedstationMask.empty()) {
				editCompressedstation(CompressedstationMask);
			}
			else {
				cout << "Not found" << endl;
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
					CompressedstationMask.push_back(std::ref(const_cast<Compressedstation&>(*it)));
				}
			}
			if (!CompressedstationMask.empty()) {
				editCompressedstation(CompressedstationMask);
			}
			else {
				cout << "Not found" << endl;
			}
			break;
		}
		case 6: {
			cout << "=== Batch editing ===" << endl << "Enter the IDs one by one. When you feel it's time to stop, type 'stop'." << endl;
			CompressedstationMask.clear();

			for (size_t i = 0; i < Compressedstations.size(); i++)
			{
				try {
					Compressedstation& pl = Select<Compressedstation>(Compressedstations, GetMax(Compressedstations)+1);
					CompressedstationMask.push_back(std::ref(pl));
				}
				catch (const runtime_error& e) {
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
	s.load(fin);
	return s;
}

Compressedstation Mainthread::LoadCompressedstation(ifstream& fin)
{
	Compressedstation s;
	s.load(fin);
	return s;
}


void Mainthread::SavePipeline(ofstream& fout, const Pipeline& s)
{
	s.save(fout);
}

void Mainthread::SaveCompressedstation(ofstream& fout, const Compressedstation& s)
{
	s.save(fout);
}












void Mainthread::saveFunction() {
	string file_string;
	cout << "Type file name: ";
	INPUT_LINE(cin, file_string);
	ofstream fout;
	fout.open(file_string, ios::out);
	if (fout.is_open())
	{
		fout << Pipelines.size() << endl;
		fout << Compressedstations.size() << endl;
		for (Pipeline st : Pipelines)
			SavePipeline(fout, st);
		for (Compressedstation st : Compressedstations)
			SaveCompressedstation(fout, st);
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
		fin >> countPipeline;
		fin >> countCompressedstation;
		while (countPipeline--)
		{
			Pipelines.insert(LoadPipeline(fin));
		}
		while (countCompressedstation--)
		{
			Compressedstations.insert(LoadCompressedstation(fin));
		}
		fin.close();
	}
	else {
		cerr << "The file cannot be opened." << endl;
	}
}
