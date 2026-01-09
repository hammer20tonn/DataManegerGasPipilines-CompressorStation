#include <iostream>
#include <vector>
#include <fstream>
#include "utils.h"

#include "Pipeline.h"

#include "Compressedstation.h"


#include "Mainthread.h"







#include <chrono>
#include <format>

using namespace std;
using namespace chrono;

int main()
{
	redirect_output_wrapper cerr_out(cerr);
	string time = std::format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time);
	if (logfile)
		cerr_out.redirect(logfile);


	Mainthread mainthread;


	while (1) {
		cout << "1. Pipeline menu" << endl
			<< "2. Compressed station menu" << endl
			<< "3. Save to file" << endl
			<< "4. Load from file" << endl
			<< "0. Exit" << endl
			<< "Choose action: ";
		switch (GetCorrectNumber(0, 4))
		{
			case 1: { // Pipelines
				mainthread.PipelineMenu();
				break;
			}
			case 2: {
				mainthread.CompressedstationMenu();
				break;
			}
			case 3: {
				mainthread.saveFunction();
				break;
			}
			case 4: {
				mainthread.loadFunction();
				break;
			}
			case 0: {
				return 0; // Exit
			}
			default:
			{
				cerr << "Wrong action" << endl;
				break;
			}
		}
	}
	return 0;
}
