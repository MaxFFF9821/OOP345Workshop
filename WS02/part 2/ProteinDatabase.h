//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/05/24
#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H
#include <iostream>
namespace seneca{
    class ProteinDatabase{
        std::string *proteinSeq{};
        size_t arraySize{};
        public:
        ProteinDatabase()=default;
        ProteinDatabase(const ProteinDatabase& pdb);
        ProteinDatabase(ProteinDatabase &&pdb) noexcept;
        ProteinDatabase& operator=( const ProteinDatabase& pdb);
        ProteinDatabase& operator=(ProteinDatabase &&pdb) noexcept;
        ProteinDatabase(const char* filename);
        ~ProteinDatabase();
        size_t size() const;
        std::string operator[](size_t index) const;
    };
}
#endif