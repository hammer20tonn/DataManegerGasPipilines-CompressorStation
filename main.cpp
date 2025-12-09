#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <limits>
#include <array>

int Out_CinFuncs; // Переменная для вывода функций: CinFunc1, CinFunc
int Type; // 1 - PL, 2 - CS
int CommandCode;
int CinCode;
string buffer_;

struct PL {
    string Name;
    int Length; // Длина (км)
    int Diameters; // Диаметр (мм)
    bool State; // Признак "в ремонте" (true/false)
    void display_info() {
        cout << Name << endl;
        cout << Length << endl;
        cout << Diameters << endl;
        cout << State << endl;
    }
    void download() {
        string line;
        ifstream in("pipeline.txt");
        if (in.is_open()) {
            getline(in, line);
            Name = line;
            getline(in, line);
            Length = atoi(line.c_str());
            getline(in, line);
            Diameters =  atoi(line.c_str());
            getline(in, line);
            if (line == "true") {
                State = true;
            } else {
                State = false;
            }
        }
    }
    void save() {
        string outtxt;
        ofstream outFile("pipeline.txt");
        if (outFile.is_open()) {
            outtxt += Name+"\n";
            outtxt += to_string(Length)+"\n";
            outtxt += to_string(Diameters)+"\n";
            outtxt += State ? "true" : "false";
            outFile << outtxt;
            outFile.close();
        }
    }
};















struct CS {
    string Name;
    int Length; // Количество цехов
    int LengthOfWork; // Количество цехов в работе
    int ClassStation; // класс станции
    void display_info() {
        cout << Name << endl;
        cout << Length << endl;
        cout << LengthOfWork << endl;
        cout << ClassStation << endl;
    }
    void download() {
        string line;
        ifstream in("compressor_stations.txt");
        if (in.is_open()) {
            getline(in, line);
            Name = line;
            getline(in, line);
            Length = atoi(line.c_str());
            getline(in, line);
            LengthOfWork =  atoi(line.c_str());
            getline(in, line);
            ClassStation = atoi(line.c_str());
        }
    }
    void save() {
        string outtxt;
        ofstream outFile("compressor_stations.txt");
        if (outFile.is_open()) {
            outtxt += Name+"\n";
            outtxt += to_string(Length)+"\n";
            outtxt += to_string(LengthOfWork)+"\n";
            outtxt += to_string(ClassStation);
            outFile << outtxt;
            outFile.close();
        }
    }
};

int CinFunc1(const vector<string>& list) { // Функция проверки на валидность №2
    bool status = 1;
    for (size_t i = 0; i < list.size(); ++i) {
        if (buffer_ == list[i]) {
            status = 0;
        }
    }
    if (status == 1) {
        cerr << "Input error." << endl;
    }
    return status;
}

int CinFunc(int upfloor) {  // Функция проверки на валидность №1
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cerr << "Input error." << endl;
        return 1;
    }
    if (upfloor == CommandCode) {
        cout << "exit program" << endl;
        exit(0);
    }
    if (CommandCode < 0 | CommandCode > upfloor) {
        cerr << "Input error." << endl;
        return 1;
    }
    return 0;
}
bool status = false;
bool isIntegerStrict(const std::string& str) {
    try {
        if (str.empty()) return false;
        
        size_t pos = 0;
        stoi(str, &pos);
        return pos == str.length();
    } catch (const std::exception&) {
        return false;
    }
}

template<typename T> void ConditionPL(T& p) {
    vector<string> list = {"true", "false"};
    switch (CommandCode)
    {
        case 0:
            buffer_ = "";
            cout << "Enter new name: " << endl;
            getline(cin, buffer_);
            p.Name = buffer_;
            break;
        case 1:
            buffer_ = "";
            cout << "Enter new Length: " << endl;
            getline(cin, buffer_);


            // Проверка на валидность
            status = isIntegerStrict(buffer_.c_str());
            if(status) {
                CommandCode = atoi(buffer_.c_str());
                if (CommandCode == 0) {
                    cout << "Input error" << endl;
                    break;
                }
                Out_CinFuncs = CinFunc(1000);
                if (Out_CinFuncs == 1) {
                    break;
                }
                p.Length = CommandCode;
                break;
            } else {
                cout << "Input error" << endl;
                break;
            }


        case 2:
            buffer_ = "";
            cout << "Enter new Diameters: " << endl;
            getline(cin, buffer_);



            // Проверка на валидность
            status = isIntegerStrict(buffer_.c_str());
            if(status) {
                CommandCode = atoi(buffer_.c_str());
                if (CommandCode == 0) {
                    cout << "Input error" << endl;
                    break;
                }
                Out_CinFuncs = CinFunc(1000);
                if (Out_CinFuncs == 1) {
                    break;
                }
                p.Diameters = CommandCode;
                break;
            } else {
                cout << "Input error" << endl;
                break;
            }



        case 3:
            buffer_ = "";
            cout << "Enter new State: " << endl;
            getline(cin, buffer_);
            // Проверка на валидность
            Out_CinFuncs = CinFunc1(list);
            if (Out_CinFuncs == 1) {
                break;
            }
            // Перевод в другой тип данных
            if (buffer_ == "true") {
                p.State = true;
            } else if(buffer_ == "false") {
                p.State = false;
            }
            break;
        case 4:
            p.display_info();
            break;
        default:
            break;
    }
}

template<typename T> void ConditionCS(T& p) {
    vector<string> list = {"1", "2", "3"};
    switch (CommandCode)
    {
        case 0:
            buffer_ = "";
            cout << "Enter new name: " << endl;
            getline(cin, buffer_);
            p.Name = buffer_;
            break;
        case 1:
            buffer_ = "";
            cout << "Enter new Length: " << endl;
            getline(cin, buffer_);
            // Проверка на валидность
            status = isIntegerStrict(buffer_.c_str());
            if(status) {
                CommandCode = atoi(buffer_.c_str());
                if (CommandCode == 0) {
                    cout << "Input error" << endl;
                    break;
                }
                Out_CinFuncs = CinFunc(1000);
                if (Out_CinFuncs == 1) {
                    break;
                }
                p.Length = CommandCode;
                break;
            } else {
                cout << "Input error" << endl;
                break;
            }
        case 2:
            buffer_ = "";
            cout << "Enter new LengthOfWork: " << endl;
            getline(cin, buffer_);
            // Проверка на валидность
            status = isIntegerStrict(buffer_.c_str());
            if(status) {
                CommandCode = atoi(buffer_.c_str());
                if (CommandCode == 0) {
                    cout << "Input error" << endl;
                    break;
                }
                Out_CinFuncs = CinFunc(1000);
                if (Out_CinFuncs == 1) {
                    break;
                }
                p.LengthOfWork = CommandCode;
                break;
            } else {
                cout << "Input error" << endl;
                break;
            }
        case 3:
            buffer_ = "";
            cout << "Enter new ClassStation: " << endl;
            getline(cin, buffer_);
            // Проверка на валидность
            Out_CinFuncs = CinFunc1(list);
            if (Out_CinFuncs == 1) {
                break;
            }
            p.ClassStation = atoi(buffer_.c_str());
            break;
        case 4:
            p.display_info();
            break;
        default:
            break;
    }
}

int main() {
    //bool status = false;
    while (true) {
        cout << "[0 - Pipeline, 1 - Compressed station, 2 - Finished program]: ";
        buffer_ = "";
        //cin >> CommandCode;
        getline(cin, buffer_);



        status = isIntegerStrict(buffer_.c_str());
        if(status) {    
            CommandCode = stoi(buffer_.c_str());
            //cout << CommandCode << endl;
            CinCode = CinFunc(2);
            if (CinCode == 1) {
                break;
            }
        } else {
            cout << "Input error" << endl;
            continue;
        }



        Type = CommandCode;
        if (CommandCode == 0) {
            buffer_ = "";
            PL p;
            p.download();
            cout << "[\n 0 - Name,\n 1 - Length,\n 2 - Diameters,\n 3 - State,\n 4 - print,\n 5 - passed,\n 6 - Finished program\n]: ";
            getline(cin, buffer_);
        status = isIntegerStrict(buffer_.c_str());
        if(status) {    
            CommandCode = stoi(buffer_.c_str());
            CinCode = CinFunc(6);
            if (CinCode == 1) {
                break;
            }
        } else {
            cout << "Input error" << endl;
            continue;
        }
            ConditionPL<PL>(p);
            p.save();
        } else if(CommandCode == 1) {
            buffer_ = "";
            CS p;
            p.download();
            cout << "[\n0 - Name,\n 1 - Length,\n 2 - Length of work,\n 3 - Class of station,\n 4 - print,\n 5 - passed,\n 6 - Finished program\n]: ";
            getline(cin, buffer_);
        status = isIntegerStrict(buffer_.c_str());
        if(status) {    
            CommandCode = stoi(buffer_.c_str());
            CinCode = CinFunc(6);
            if (CinCode == 1) {
                break;
            }
        } else {
            cout << "Input error" << endl;
            continue;
        }
            ConditionCS<CS>(p);
            p.save();
        } else {
            return 0;
        }
    }
}