//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/05/24
#include"ProteinDatabase.h"
#include <fstream>
#include <iostream>
using namespace seneca;
using namespace std;

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
        if (pdb.proteinSeq != nullptr){
                proteinSeq = new string[arraySize];
                for(size_t i = 0; i < arraySize; i++){
                    proteinSeq[i] = pdb.proteinSeq[i];
                }
            }
        }
    return *this;
}

ProteinDatabase::ProteinDatabase(ProteinDatabase &&pdb) noexcept{
    *this = std::move(pdb);
}

ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase &&pdb) noexcept {
    if (this != &pdb) {
        delete[] proteinSeq;
        proteinSeq = pdb.proteinSeq;
        pdb.proteinSeq = nullptr;
        arraySize = pdb.arraySize;
        pdb.arraySize = 0;
    }
    return *this;
}

ProteinDatabase::ProteinDatabase(const char* filename) {
      ifstream file(filename);
        string line,line2;
        size_t count = 0;
        if (file){
            file.ignore(1000, '\n');
            while (getline(file, line2, '>')){
                    arraySize++;
            }
            file.clear();
            file.seekg(0);
            proteinSeq = new string[arraySize];
            file.ignore(1000, '\n');
            while (getline(file, line)){
                if (line[0] != '>'){
                        proteinSeq[count] += line;
                } else {
                    if (count < arraySize){
                        count++;
                    }
                }
            }
        }

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
    