#include "Database.h"
#include <fstream>
#include <sstream>
#include <iomanip>

namespace seneca {

std::shared_ptr<Database> Database::instance = nullptr;

Database::Database(const std::string& filename) : num_entries(0), filename(filename) {
    std::cout << "[" << this << "] Database(const std::string&)" << std::endl;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line) && num_entries < MAX_ENTRIES) {
        std::istringstream iss(line);
        std::string key, value;
        if (iss >> key >> value) {
            for (char& c : key) {
                if (c == '_') {
                    c = ' ';
                }
            }
            keys[num_entries] = key;
            values[num_entries] = value;
            num_entries++;
        }
    }
    file.close();
}

Database::~Database() {
    std::cout << "[" << this << "] ~Database()" << std::endl;
    std::ofstream backup_file(filename + ".bkp.txt");
    for (int i = 0; i < num_entries; ++i) {
        backup_file << std::left << std::setw(25) << keys[i] << " -> " << values[i] << std::endl;
    }
    backup_file.close();
}

std::shared_ptr<Database> Database::getInstance(const std::string& filename) {
    if (instance == nullptr) {
        instance = std::shared_ptr<Database>(new Database(filename));
    }
    return instance;
}

Err_Status Database::GetValue(const std::string& key, std::string& value) const {
    for (int i = 0; i < num_entries; ++i) {
        if (keys[i] == key) {
            value = values[i];
            return Err_Status::Err_Success;
        }
    }
    return Err_Status::Err_NotFound;
}

Err_Status Database::SetValue(const std::string& key, const std::string& value) {
    if (num_entries < MAX_ENTRIES) {
        keys[num_entries] = key;
        values[num_entries] = value;
        num_entries++;
        return Err_Status::Err_Success;
    }
    return Err_Status::Err_OutOfMemory;
}

}
