//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/07/21
#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <memory>
#include <string>
#include <fstream>

namespace seneca {
    static const size_t MAX_ENTRIES = 20;

    enum class Err_Status {
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory,
    };

    template<typename T>
    class Database {
        static std::shared_ptr<Database<T>> instance;
        size_t entryCount;
        std::string keys[MAX_ENTRIES];
        T values[MAX_ENTRIES];
        std::string fileName;
        Database(const std::string& fileName);
        void encryptDecrypt(T& value);

    public:
        static std::shared_ptr<Database<T>> getInstance(const std::string& fileName);
        Err_Status GetValue(const std::string& key, T& value) const;
        Err_Status SetValue(const std::string& key, const T& value);
        ~Database();
    };

    template <>
    void Database<std::string>::encryptDecrypt(std::string& value);
    template <>
    void Database<long long>::encryptDecrypt(long long& value);

}

#endif 
