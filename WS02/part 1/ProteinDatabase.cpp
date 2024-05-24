//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/05/24
#include"ProteinDatabase.h"
#include <fstream>
#include <iostream>
using namespace seneca;
using namespace std;

ProteinDatabase::ProteinDatabase(){};

ProteinDatabase::ProteinDatabase(const ProteinDatabase& pdb){
    *this = pdb;
}

ProteinDatabase::~ProteinDatabase(){
    delete[] proteinSeq;
}

ProteinDatabase& ProteinDatabase::operator=( const ProteinDatabase& pdb){
    if(this != &pdb){
        delete[] proteinSeq;
        proteinSeq = nullptr;
        arraySize = pdb.arraySize;
        proteinSeq = new string[arraySize];
        for(size_t i = 0; i < arraySize; i++){
            proteinSeq[i] = pdb.proteinSeq[i];
        }
    }
    return *this;
}

ProteinDatabase::ProteinDatabase(const std::string &filename){
    ifstream file(filename);
    string line;
    size_t count = 0;
    while (getline(file, line)) {
        if (line[0] == '>') {
            count++;
        }
    }
    proteinSeq = new string[count];
    arraySize = count;
    file.clear();
    file.seekg(0);
    count = 0;
    string seq;
    while (std::getline(file, line)) {
        if (line[0] == '>') {
            if (!seq.empty()) {
                proteinSeq[count++] = seq;
                seq.clear();
            }
        } else {
            seq += line;
        }
    }
    if (!seq.empty()) {
        proteinSeq[count] = seq;
    }

        file.close();
    ;
}

size_t ProteinDatabase::size() const{
    return arraySize;
}

std::string ProteinDatabase::operator[](size_t index) const{
    if (index > arraySize - 1 || arraySize == 0){
        return "";
    }
    return proteinSeq[index];
}
    