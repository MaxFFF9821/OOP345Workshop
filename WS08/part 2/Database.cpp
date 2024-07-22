//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/07/21
#include "Database.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm> 

namespace seneca {

    template<typename T>
    std::shared_ptr<Database<T>> Database<T>::instance{};

    template<typename T>
    Database<T>::Database(const std::string& fileName) : entryCount(0), fileName(fileName) {
        std::cout << "[" << this << "] Database(const std::string&)" << std::endl;

        std::ifstream file(fileName, std::ios::in);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line) && entryCount < MAX_ENTRIES) {
            std::istringstream iss(line);
            std::string key;
            T value;
            if (iss >> key >> value) {
                std::replace(key.begin(), key.end(), '_', ' ');
                encryptDecrypt(value);
                keys[entryCount] = key;
                values[entryCount] = value;
                ++entryCount;
            }
        }
        file.close();
    }

    template<typename T>
    void Database<T>::encryptDecrypt(T& value) {}

    template<>
    void Database<std::string>::encryptDecrypt(std::string& value) {
        const char secret[]{ "secret encryption key" };

        for (char& c : value) {
            for (const char& k : secret) {
                c ^= k;
            }
        }
    }

    template<>
    void Database<long long>::encryptDecrypt(long long& value) {
        const char secret[]{ "super secret encryption key" };

        char* byteValue = reinterpret_cast<char*>(&value);
        for (size_t i = 0; i < sizeof(value); ++i) {
            for (const char& k : secret) {
                byteValue[i] ^= k;
            }
        }
    }

    template<typename T>
    std::shared_ptr<Database<T>> Database<T>::getInstance(const std::string& fileName) {
        if (!instance) {
            instance = std::shared_ptr<Database>(new Database(fileName));
        }
        return instance;
    }

    template<typename T>
    Err_Status Database<T>::GetValue(const std::string& key, T& value) const {
        for (size_t i = 0; i < entryCount; ++i) {
            if (keys[i] == key) {
                value = values[i];
                return Err_Status::Err_Success;
            }
        }
        return Err_Status::Err_NotFound;
    }

    template<typename T>
    Err_Status Database<T>::SetValue(const std::string& key, const T& value) {
        if (entryCount < MAX_ENTRIES) {
            keys[entryCount] = key;
            values[entryCount] = value;
            ++entryCount;
            return Err_Status::Err_Success;
        }
        return Err_Status::Err_OutOfMemory;
    }

    template<typename T>
    Database<T>::~Database() {
        std::cout << "[" << instance << "] ~Database()" << std::endl;

        std::ofstream file(fileName + ".bkp.txt", std::ios::out | std::ios::trunc);
        for (size_t i = 0; i < entryCount; ++i) {
            file << std::left << std::setw(25) << keys[i];
            T encryptedValue = values[i];
            encryptDecrypt(encryptedValue);
            file << " -> " << encryptedValue << std::endl;
        }
        file.close();
    }

}

template class seneca::Database<std::string>;
template class seneca::Database<long long>;
