#include "ObjectTemplate.h"



#include "cereal/archives/binary.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/variant.hpp"



#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include <stdexcept>






ObjectTemplate::ObjectTemplate() {}
ObjectTemplate::ObjectTemplate(string parametr_[5], string metadata_[5], int DesiredType_[5]) {
    for (int i = 0; i < 5; ++i) {
        parametr[i] = parametr_[i];
        metadata[i] = metadata_[i];
        DesiredType[i] = DesiredType_[i];
    }

}
ObjectTemplate::~ObjectTemplate() {}






void ObjectTemplate::TechFunc1(int i) {
    //int DesiredType[5] = {0, 1, 1, 1, 2};
    auto TypeDesireedTypeOut = MainData[i];
    cout << DesiredType[i] << endl;
    if (DesiredType[i] == 1) {
        TypeDesireedTypeOut = 0;
        InputPos<int>(parametr[i], get<int>(TypeDesireedTypeOut), i);
    } else if(DesiredType[i] == 0) {
        TypeDesireedTypeOut = "";
        InputPos<string>(parametr[i], get<string>(TypeDesireedTypeOut), i);
    } else if(DesiredType[i] == 2) {
        unsigned par = 0;
        TypeDesireedTypeOut = par;
        InputPos<unsigned>(parametr[i], get<unsigned>(TypeDesireedTypeOut), i);
    }
}


template <typename T>
T ObjectTemplate::InputPos(string NameOfInput, T DesireedTypeIn, int id) {
    cout << NameOfInput << metadata[id];
    cin >> DesireedTypeIn;
    if (cin.fail()) {
        cin.clear();
        cout << "input error. Try again." << endl;
        throw invalid_argument("Invalid argument. Try again.");
    }
    variant<int, unsigned, string> DesireedTypeInVariant = DesireedTypeIn;
    MainData[id] = DesireedTypeInVariant;
    return DesireedTypeIn;
}

template int ObjectTemplate::InputPos<int>(string, int, int);
template unsigned ObjectTemplate::InputPos<unsigned>(string, unsigned, int);
template string ObjectTemplate::InputPos<string>(string, string, int);


void ObjectTemplate::update() {
    cout << "-----------------" << endl;
    cout << "Enetr this number for change parametr." << endl;
    for (int i = 0; i < size(parametr); i++) {
        cout << parametr[i] << i << endl;
    }

    int NumOfPar;
    cout << "Input number of parametr: ";
    cin >> NumOfPar;

    TechFunc1(NumOfPar);
    cout << "-----------------" << endl;
}

void ObjectTemplate::create() {
    cout << "-----------------" << endl;
    cout << "Create a new pipeline." << endl;
    for(size_t i = 0; i < 5; i++) {
        TechFunc1(i);
    }
    cout << "-----------------" << endl;
}

void ObjectTemplate::PrintData() {
    cout << "-----------------" << endl;
    for (int i = 0; i < size(MainData); i++) {
        cout << parametr[i] << metadata[i];
        visit([](const auto& value) {
            cout << value;
        }, MainData[i]);
        cout << endl;
    }
    cout << "-----------------" << endl;
}




template<class Archive>
void ObjectTemplate::serialize(Archive& archive) {
    archive(
        MainData,    // сериализуем основные данные
        parametr,    // сериализуем параметры
        metadata     // сериализуем метаданные
    );
    // Примечание: временные массивы вроде DesiredType не сериализуем
}

template void ObjectTemplate::serialize<cereal::BinaryOutputArchive>(cereal::BinaryOutputArchive&);
template void ObjectTemplate::serialize<cereal::BinaryInputArchive>(cereal::BinaryInputArchive&);
