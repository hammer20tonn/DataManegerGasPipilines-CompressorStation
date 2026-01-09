#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Pipe {
    string name;
    double length;
    int diametr;
    bool state; // 1 - работает, 0 - не работает
};

struct CompressorStation {
    string name;
    int numberWorkshop; // Количество цехов
    int workingWorkshop; // Работающие цеха
    int classWorkshop;
};

void addPipe(Pipe& pipe) {
    cout << "Name: ";
    getline(cin >> ws, pipe.name);
    while (pipe.name.empty()) {
        cout << "Input error. Please, try again.\n";
        cout << "Name: ";
        getline(cin, pipe.name);
    }

    cout << "Length: ";
    while (!(cin >> pipe.length) || (pipe.length < 0) || (cin.peek() != '\n')) {
        cout << "Input error. Please, try again.";
        cout << "Length: ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "Diameter: ";
    while (!(cin >> pipe.diametr) || (pipe.diametr < 0) || (cin.peek() != '\n')) {
        cout << "Input error. Please, try again.";
        cout << "Diameter: ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "status(1 - work, 0 - not work): ";
    while (!(cin >> pipe.state) || (cin.peek() != '\n')) {
        cout << "Input error. Please, try again.";
        cout << "status(1 - work, 0 - not work): ";
        cin.clear();
        cin.ignore(100, '\n');
    }
}



void addCs(CompressorStation& cs) {
    cout << "Name: ";
    getline(cin >> ws, cs.name);
    while (cs.name.empty()) {
        cout << "Input error. Please, try again.\n";
        cout << "Name: ";
        getline(cin, cs.name);
    }

    cout << "Length of workshops: ";
    while (!(cin >> cs.numberWorkshop) || (cs.numberWorkshop < 0) || (cin.peek() != '\n')) {
        cout << "Input error. Please, try again.";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "Number of workshops: ";
    while (!(cin >> cs.workingWorkshop) || (cs.workingWorkshop < 0) || (cin.peek() != '\n') || (cs.workingWorkshop > cs.numberWorkshop)) {
        cout << "Input error. Please, try again.";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "Class(1-4): ";
    while (!(cin >> cs.classWorkshop) || (cs.classWorkshop < 0) || (cin.peek() != '\n')) {
        cout << "Input error. Please, try again.";
        cin.clear();
        cin.ignore(100, '\n');
    }
}

void viewPipe(Pipe& pipe) {
    if (!pipe.name.empty()) {
        cout << "\nPipe\n";
        cout << "_______\n";
        cout << pipe.name << endl;
        cout << pipe.length << endl;
        cout << pipe.diametr << endl;
        cout << pipe.state << endl;
    }
    else {
        cout << "Empty" << endl;
    }
}

void viewCs(CompressorStation& cs) {
    if (!cs.name.empty()) {
        cout << "\Compressor station\n";
        cout << "_______\n";
        cout << cs.name << endl;
        cout << cs.numberWorkshop << endl;
        cout << cs.workingWorkshop << endl;
        cout << cs.classWorkshop << endl;
    }
    else {
        cout << "Empty" << endl;
    }
}

void editPipeState(Pipe& pipe) {
    if (pipe.name.empty()) {
        cout << "Pipeline not found." << endl;
        return;
    }
    cout << "status(1 - work, 0 - not work): ";
    while (!(cin >> pipe.state) || (cin.peek() != '\n')) {
        cout << "Input error. Please, try again.";
        cout << "status(1 - work, 0 - not work): ";
        cin.clear();
        cin.ignore(100, '\n');
    }
}

void editCsWorkshop(CompressorStation& cs) { // workingWorkshop++
    if (cs.name.empty()) {
        cout << "Compressor station not found." << endl;
        return;
    }
    int NumChoice;
    cout << "Edit working workshop(1 - increase, 0 - deincrease): ";
    while (!(cin >> NumChoice) || (cin.peek() != '\n')) {
        cout << "Input error. Please, try again.";
        cout << "Edit working workshop(1 - increase, 0 - deincrease): ";
        cin.clear();
        cin.ignore(100, '\n');
    }
    switch (NumChoice) {
    case 1:
        if ((cs.workingWorkshop + 1) > cs.numberWorkshop) {
            cout << "The permissible limit has been exceeded." << endl;
            break;
        }
        cs.workingWorkshop++;
        break;
    case 0:
        if ((cs.workingWorkshop - 1) < 0) {
            cout << "The permissible limit has been exceeded." << endl;
            break;
        }
        cs.workingWorkshop--;
        break;
    default:
        break;
    }
}



void savePipeCs(const Pipe& pipe, const CompressorStation& cs, string name) {
    ofstream file(name);
    if (file.is_open()) {
        file << "==========" << "\n";
        if (!pipe.name.empty() || pipe.length > 0 || pipe.diametr > 0) {
            file << pipe.name << "\n";
            file << pipe.length << "\n";
            file << pipe.diametr << "\n";
            file << pipe.state << "\n";
        }

        file << "----------" << "\n";
        if (!cs.name.empty() || cs.numberWorkshop > 0 || cs.classWorkshop > 0) {
            file << cs.name << "\n";
            file << cs.numberWorkshop << "\n";
            file << cs.workingWorkshop << "\n";
            file << cs.classWorkshop << "\n";
        }

        file.close();
        cout << "Data saved successfully to " << name << endl;
    }
    else {
        cout << "Error: Could not open file for writing!" << endl;
    }
}






void savePipe(ofstream& file, const Pipe& pipe) {
    //ofstream file(name);
    if (file.is_open()) {
        file << "==========" << "\n";
        if (pipe.length > 0 || pipe.diametr > 0) {
            file << pipe.name << "\n";
            file << pipe.length << "\n";
            file << pipe.diametr << "\n";
            file << pipe.state << "\n";
        }
        cout << "Data saved successfully" << endl;
    }
    else {
        cout << "Error: Could not open file for writing!" << endl;
    }
}




void saveCs(ofstream& file, const CompressorStation& cs) {
    //ofstream file(name);
    if (file.is_open()) {
        file << "----------" << "\n";
        if (cs.numberWorkshop > 0 || cs.classWorkshop > 0) {
            file << cs.name << "\n";
            file << cs.numberWorkshop << "\n";
            file << cs.workingWorkshop << "\n";
            file << cs.classWorkshop << "\n";
        }

        cout << "Data saved successfully" << endl;
    }
    else {
        cout << "Error: Could not open file for writing!" << endl;
    }
}









void loadPipe(Pipe& pipe, ifstream& file) {
    string line;
    if (file.is_open()) {
        file >> pipe.name;
        file >> pipe.length;
        file >> pipe.diametr;
        file >> pipe.state;
    }
}

void loadCs(CompressorStation& cs, ifstream& file) {
    if (file.is_open()) {
        file >> cs.name;
        file >> cs.numberWorkshop;
        file >> cs.workingWorkshop;
        file >> cs.classWorkshop;
    }
}
int main() {
    Pipe pipe;
    CompressorStation cs;
    int NumChoice;

    // Главный цикл программы
    do {
        cout << "\nMenu\n";
        cout << "1. Add a pipe\n";
        cout << "2. Add a compressor station\n";
        cout << "3. View pipe\n";
        cout << "4. View compressor station\n";
        cout << "5. Edit a pipe\n";
        cout << "6. Edit a compressor station\n";
        cout << "7. Save data\n";
        cout << "8. Load data\n";
        cout << "0. Exit\n";
        cout << "> ";
        if (!(cin >> NumChoice)) {
            NumChoice = 999;
            cout << "Input error. Please enter a number." << endl;
            cin.clear(); // Сбрасываем флаг ошибки
            cin.ignore(10000, '\n'); // Очищаем буфер ввода
            continue;
        }
        cin.ignore(10000, '\n');
        switch (NumChoice) {
        case 1:
            addPipe(pipe);
            break;
        case 2:
            addCs(cs);
            break;
        case 3:
            viewPipe(pipe);
            break;
        case 4:
            viewCs(cs);
            break;
        case 5:
            editPipeState(pipe);
            break;
        case 6:
            editCsWorkshop(cs);
            break;
        case 7: {
            ofstream file("PipelineComporessorstation.txt");
            savePipe(file, pipe);
            saveCs(file, cs);
            //savePipeCs(pipe, cs, "PipelineComporessorstation.txt");
            cout << "Data saved successfully!\n";
            file.close();
            break;
        }
        case 8:
        {
            ifstream file("PipelineComporessorstation.txt");
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    if (line == "==========") {
                        loadPipe(pipe, file);
                    }
                    else if (line == "----------") {
                        loadCs(cs, file);
                    }
                }
                file.close();
                cout << "Data loaded successfully!\n";
            }
            else {
                cout << "Error: Could not open file for reading.\n";
            }
        }
        break;
        case 0:
            cout << "Exiting.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (NumChoice != 0);

    return 0;
}