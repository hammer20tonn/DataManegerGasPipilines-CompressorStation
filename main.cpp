#include "ObjectTemplate.h"
#include <fstream>
#include <iostream>


// Вариант 2: Если структура другая
#include "cereal/archives/binary.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/variant.hpp"

using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <type_traits>

#include <variant>
#include <vector>


#include <cstdio>
#include <cstdlib>

#include <string>

#include <stdexcept>




template <typename T>
T DetectedInput(T& value, int up, int down) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cout << "input error. Try again." << endl;
        throw invalid_argument("Invalid argument. Try again.");
    } else if (up < value || down > value) {
	cout << "input error. Try again." << endl;
	throw invalid_argument("Invalid argument. Try again.");
    }
    return value;
}


struct FilesData {
    vector<string> NamesOfFiles;

    template <class Archive>
    void serialize(Archive& ar) {
        ar(NamesOfFiles);
    }
};



template <typename T>
void SavePipeLine(const T& pl, const string& filename) {
    ofstream os(filename, ios::binary);
    cereal::BinaryOutputArchive archive(os);
    archive(pl);
}

FilesData MainMenu(FilesData NamesOfFilesStructure, string prefix, string parametr[5], string metadata[5], int DesiredType[5]) {
    vector<string> NamesOfFiles = NamesOfFilesStructure.NamesOfFiles;
    ObjectTemplate CopiesOfClass[NamesOfFiles.size()];
    if (NamesOfFiles.size() == 0) {
        int DesiredNum;
        cout << "[Exit - Ctrl+C, Create a new - 0]: " << endl;
    	try {
    		int DesiredNum = DetectedInput<int>(DesiredNum, 0, 0);
    	} catch (const exception& e) {
		return NamesOfFilesStructure;
    	}
        if (DesiredNum == 0) {
	    try {
            	ObjectTemplate NewPipeLine(parametr, metadata, DesiredType);
            	NewPipeLine.create();
	    	      NewPipeLine.PrintData();
            	string FileName = "Data"+prefix+to_string(NamesOfFiles.size())+".bin";
            	SavePipeLine(NewPipeLine, FileName);
            	NamesOfFilesStructure.NamesOfFiles.push_back(FileName);
            	return NamesOfFilesStructure;
            } catch (const exception& e) {
		return NamesOfFilesStructure;
	    }
        } else {}
    }
    for (int i = 1; i < NamesOfFiles.size()+1; i++) {
        ObjectTemplate pipeline(parametr, metadata, DesiredType);
        try {
            ifstream is(NamesOfFiles[i-1], ios::binary);
            cereal::BinaryInputArchive archive(is);
            archive(pipeline);
        } catch (const exception& e) {
            cerr << "Error -- " << endl;
        }
        CopiesOfClass[i-1] = pipeline;
        visit([](const auto& value) {
            cout << value;
        }, pipeline.MainData[0]);
        cout << ": " << i << endl;
    }
    int DesiredNum;
    int DesiredNum_;
    cout << "[Desired number, Exit - Ctrl+C, Create a new - 0]: " << endl;
    //cin >> DesiredNum;
    try {
    	 DesiredNum_ = DetectedInput<int>(DesiredNum, NamesOfFiles.size(), 0);
    } catch (const exception& e) {
	     return NamesOfFilesStructure;
    }
    if (DesiredNum_ == 0) {
      try {
        	ObjectTemplate NewPipeLine(parametr, metadata, DesiredType);
        	NewPipeLine.create();
		      NewPipeLine.PrintData();
        	string FileName = "Data"+prefix+to_string(NamesOfFiles.size())+".bin";
        	SavePipeLine(NewPipeLine, FileName);
        	NamesOfFilesStructure.NamesOfFiles.push_back(FileName);
        	return NamesOfFilesStructure;
        } catch (const exception& e) {
		return NamesOfFilesStructure;
	}
    } else {
       DesiredNum_--;
    }
    CopiesOfClass[DesiredNum_].PrintData();
    cout << "[Update - 0, Delete - 1, Pass - 2, Exit - Ctrl+C]: ";
    int cmnd;
    int cmnd_;
    try {
    	 cmnd_ = DetectedInput<int>(cmnd, 2, 0);
    } catch (const exception& e) {
	     return NamesOfFilesStructure;
    }
    ObjectTemplate pipeline(parametr, metadata, DesiredType);
    string FileName = "Data"+prefix+to_string(DesiredNum_)+".bin";
    switch (cmnd_) {
        case 0:
            pipeline = CopiesOfClass[DesiredNum_];
            pipeline.update();
            CopiesOfClass[DesiredNum_] = pipeline;
	          SavePipeLine(pipeline, FileName);
	          pipeline.PrintData();
            break;
        case 1:
            if( remove( NamesOfFiles[DesiredNum_].c_str() ) != 0 ) {
                cout << "Uninstallation error, try restarting the program. If the problem persists, please contact technical support." << endl;
            } else {
                cout << "Successfully deleted." << endl;
                NamesOfFilesStructure.NamesOfFiles.erase(NamesOfFilesStructure.NamesOfFiles.begin() + DesiredNum_);
            }
            break;
        default:
            cout << "";
    }
    return NamesOfFilesStructure;
}



int main() {
	while (true) {
		cout << "[Pipelines - 0, Compressed station - 1, Exit - Ctrl+C]: " << endl;
		int StatusCode;
        string parametr[5];
        string metadata[5];
        int DesiredType[5];
        string parametr0[5] = {"Name: ", "Length: ", "Diameter: ", "Works normally: ", "Age: "};
        string metadata0[5] = {"", "", "", "(0 - false, 1 - true) ", ""};
        int DesiredType0[5] = {0, 1, 1, 1, 2};
        string parametr1[5] = {"Name: ", "Length: ", "Diameter: ", "Works normally: ", "Age: "};
        string metadata1[5] = {"", "", "", "(0 - false, 1 - true) ", ""};
        int DesiredType1[5] = {0, 1, 1, 1, 2};
		try {
      int StatusCode = DetectedInput<int>(StatusCode, 1, 0);
			string prefix;
			if (StatusCode == 0) {
				prefix = "Pipelines";
                for (int i = 0; i < 5; ++i) {
                    parametr[i] = parametr0[i];
                    metadata[i] = metadata0[i];
                    DesiredType[i] = DesiredType0[i];
                }
			} else if(StatusCode == 1) {
				prefix = "PipeCompressedStation";
                for (int i = 0; i < 5; ++i) {
                    parametr[i] = parametr1[i];
                    metadata[i] = metadata1[i];
                    DesiredType[i] = DesiredType1[i];
                }
			} else {
				cout << "input error. Try again." << endl;
				continue;
			}
			string FileName = "Data"+prefix+".bin";
			FilesData Data;
			{
        			std::ifstream is(FileName, std::ios::binary);
        			cereal::BinaryInputArchive input_archive(is);
        			input_archive(Data);
			}
			Data = MainMenu(Data, prefix, parametr, metadata, DesiredType);
			SavePipeLine(Data, FileName);
    		} catch (const exception& e) {
			cout << "input error. Try again." << endl;
    		}
	}
}
