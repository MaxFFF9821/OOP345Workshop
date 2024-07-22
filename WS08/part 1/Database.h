#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <iostream>
#include <memory>
#include <string>

namespace seneca {

enum class Err_Status {
    Err_Success,
    Err_NotFound,
    Err_OutOfMemory,
};


class Database {
private:
    static std::shared_ptr<Database> instance;
    static const int MAX_ENTRIES = 20;
    int num_entries;
    std::string keys[MAX_ENTRIES];
    std::string values[MAX_ENTRIES];
    std::string filename;
    Database(const std::string& filename);

public:
    ~Database();
    static std::shared_ptr<Database> getInstance(const std::string& filename);
    Err_Status GetValue(const std::string& key, std::string& value) const;
    Err_Status SetValue(const std::string& key, const std::string& value);
};

}

#endif
