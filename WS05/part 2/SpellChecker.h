#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <iostream>
#include <string>

namespace seneca {
    const size_t WORD_LIST_SIZE = 6;

    class SpellChecker {
        std::string m_badWords[WORD_LIST_SIZE];
        std::string m_goodWords[WORD_LIST_SIZE];
        size_t m_replaceCounts[WORD_LIST_SIZE] = {0}; 


    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };
}

#endif
