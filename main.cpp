#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <limits>



struct Pipeline {
    string Name;
    int Length;
    int Diameters;
    string State;
    string titles[4];
    void display_info() {
        cout << titles[0] << Name << endl;
        cout << titles[1] << Length << endl;
        cout << titles[2] << Diameters << endl;
        cout << titles[3] << State << endl;
    }
};

struct CompressedStation {
    string Name;
    int LengthFactory;
    int TypeOfStation;
};

int CommandCode1;
int CommandCode2;
int CommandCode3; // Id
int CommandCode4;


vector<string> vec(4);
vector<Pipeline> PipeLines;
Pipeline Reader(int indx, string name, string title[4]) {
    PipeLines.clear();
    string text;
    string line;
    bool flag = false;
    string Name;
    int LengthOfFactory;
    int Diameters;
    string OffOn;
    ifstream in(name);
    
    int num = 0;
    int num1 = 0;

    
    if (in.is_open()) {
        while (getline(in, line)) {
            if (line == "-------") {
                if (flag == false) {
                    flag = true;
                    num = 0;
                } else if (flag == true) {
                    flag = false;
                    Pipeline PipeLine;
                    for(int i = 0; i < 4; i++) {
                        PipeLine.titles[i] = title[i];
                    }
                    //PipeLine.titles = title;
                    PipeLine.Name = vec.at(0);
                    try {
                        PipeLine.Length = stoi(vec.at(1));
                        PipeLine.Diameters = stoi(vec.at(2));
                    } catch (const exception& e) {
                        cerr << "Conversion error: " << e.what() << endl;
                        continue;
                    }
                    PipeLine.State = vec.at(3);
                    PipeLines.push_back(PipeLine);
                    line = to_string(num1) + ": " + vec.at(0) + "\n";
                    text = text + line;
                    num1++;
                }
            } else if (flag == true) {
                if (num < 4) {
                    vec[num] = line;
                    num++;
                }
            }
        }
    }
    in.close();
    cout << text;
    return PipeLines[indx];
}

void Reader_info(string name) {
    string text;
    string line;
    bool flag = false;
    string Name;
    int LengthOfFactory;
    int Diameters;
    string OffOn;
    ifstream in(name);
    
    vector<string> vec(4);
    int num = 0;
    int num1 = 0;
    
    if (in.is_open()) {
        while (getline(in, line)) {
            if (line == "-------") {
                if (flag == false) {
                    flag = true;
                    num = 0;
                } else if (flag == true) {
                    flag = false;
                    line = to_string(num1) + ": " + vec.at(0) + "\n";
                    text = text + line;
                    num1++;
                }
            } else if (flag == true) {
                if (num < 4) {
                    vec[num] = line;
                    num++;
                }
            }
        }
    }
    in.close();
    cout << text;
}







void write(string name) {
    string outtxt;
    for (Pipeline unit : PipeLines) {
        outtxt += "-------\n";
        outtxt += unit.Name+"\n";
        outtxt += to_string(unit.Length)+"\n";
        outtxt += to_string(unit.Diameters)+"\n";
        outtxt += unit.State+"\n";
        outtxt += "-------\n";
    }
    ofstream file(name);
    if (file.is_open()) {
        if (PipeLines.size() == 0) {
            outtxt += "-------\n";
            outtxt += "Zero project\n";
            outtxt += "0\n";
            outtxt += "0\n";
            outtxt += "off\n";
            outtxt += "-------\n";
        }
        file << outtxt;
        file.close();
    }
}






int CoreFunc(string name, string title[]) {
    while (true) {
        cout << "[\n 0 - Edit,\n 1 - Create new,\n 2 - Delete,\n 3 - Check info,\n 4 - Main menu,\n 5 - Finished program\n]: ";
        cin >> CommandCode2;
        cout << endl;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cerr << "Input error." << endl;
            break;
        }
        if (CommandCode2 == 0) {
            Reader_info(name);
            cin >> CommandCode3;
            cout << endl;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cerr << "Input error." << endl;
                break;
            }
            Pipeline pipeline = Reader(CommandCode3, name, title);
            pipeline.display_info();

            if (CommandCode3 == 4) {
                break;
            } else if (CommandCode3 == 5) {
                exit(0);
            } else {
                int size_ = PipeLines.size();
                if (size_ < CommandCode3 || CommandCode3 < 0) {
                    cerr << "Input error." << endl;
                    break;
                }
            }
            cout << endl;
            cout << "[\n 0 - "+title[0]+",\n 1 - "+title[1]+", \n 2 - "+title[2]+",\n 3 - "+title[3]+",\n 4 - Main menu,\n 5 - Finished program\n]: ";
            cin >> CommandCode4;
            cout << endl;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cerr << "Input error." << endl;
                break;
            }
            if (CommandCode4 == 0) {
                string Name;
                cout << title[0] << endl;
                cin >> Name;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cerr << "Input error." << endl;
                    break;
                }
                cout << endl;
                pipeline.Name = Name;
            } else if (CommandCode4 == 1) {
                int Length;
                cout << title[1] << endl;
                cin >> Length;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cerr << "Input error." << endl;
                    break;
                }
                cout << endl;
                pipeline.Length = Length;
            } else if (CommandCode4 == 2) {
                int Diameter;
                cout << title[2] << endl;
                cin >> Diameter;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cerr << "Input error." << endl;
                    break;
                }
                cout << endl;
                pipeline.Diameters = Diameter;
            }  else if (CommandCode4 == 3) {
                string State;
                cout << title[3] << endl;
                cin >> State;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cerr << "Input error." << endl;
                    break;
                }
                cout << endl;
                pipeline.State = State;
            } else if (CommandCode4 == 4) {
                break;
            } else if (CommandCode4 == 5) {
                exit(0);
            } else {
                cerr << "Input error." << endl;
                break;
            }
            PipeLines[CommandCode3] = pipeline;
            write(name);
        } else if(CommandCode2 == 1) {
            Pipeline pipeline = Reader(0, name, title);
            string Name;
            cout << title[0] << endl;
            cin >> Name;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cerr << "Input error." << endl;
                break;
            }
            cout << endl;
            pipeline.Name = Name;
            int Length;
            cout << title[1] << endl;
            cin >> Length;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cerr << "Input error." << endl;
                break;
            }
            cout << endl;
            pipeline.Length = Length;
            int Diameter;
            cout << title[2] << endl;
            cin >> Diameter;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cerr << "Input error." << endl;
                break;
            }
            cout << endl;
            pipeline.Diameters = Diameter;
            string State;
            cout << title[3] << endl;
            cin >> State;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cerr << "Input error." << endl;
                break;
            }
            cout << endl;
            pipeline.State = State;
            PipeLines.push_back(pipeline);
            write(name);
        } else if(CommandCode2 == 2) {
            Reader_info(name);
            cin >> CommandCode3;
            cout << endl;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cerr << "Input error." << endl;
                break;
            }
            Pipeline pipeline = Reader(CommandCode3, name, title);
            PipeLines.erase(PipeLines.begin() + CommandCode3);
            write(name);
            Reader_info(name);
        } else if(CommandCode2 == 3) {
            Reader_info(name);
            cin >> CommandCode3;
            cout << endl;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cerr << "Input error." << endl;
                break;
            }
            Pipeline pipeline = Reader(CommandCode3, name, title);
            pipeline.display_info();
            break;
        } else if (CommandCode2 == 4) {
            break;
        } else if (CommandCode2 == 5) {
            exit(0);
        } else {
            cerr << "Input error." << endl;
            continue;
        }
    }
    return 0;
}








int main() {
    while (true) {
        cin.clear();
        cout << "[0 - Pipeline, 1 - Compressed station, 2 - Finished program]: ";
        cin >> CommandCode1;
        cout << endl;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cerr << "Input error." << endl;
            continue;
        }
        if (CommandCode1 == 0) {
            string arr[4] = {"Name: ", "Length: ", "Diameters: ", "State: "};
            CoreFunc("Pipelines.txt", arr);
        } else if(CommandCode1 == 1) {
            string arr[4] = {"Name: ", "Length: ", "Length of work: ", "Type: "};
            CoreFunc("CompressedStation.txt", arr);
        } else if(CommandCode1 == 2) {
            exit(0);
        } else {
            cerr << "Input error." << endl;
        }
    }
    return 0;
}