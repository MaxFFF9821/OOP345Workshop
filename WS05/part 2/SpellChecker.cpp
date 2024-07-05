#include "SpellChecker.h"
#include <fstream>

namespace seneca {
    SpellChecker::SpellChecker(const char* filename) {
        std::ifstream file(filename);

        if (!file) {
            throw "Bad file name!";
        }

        size_t i = 0;
        std::string line;
        while (std::getline(file, line) && i < WORD_LIST_SIZE) {
            size_t firstSpace = line.find(' ');
            m_badWords[i] = line.substr(0, firstSpace);
            m_badWords[i].erase(0, m_badWords[i].find_first_not_of(' '));
            m_badWords[i].erase(m_badWords[i].find_last_not_of(' ') + 1);

            m_goodWords[i] = line.substr(firstSpace + 1);
            m_goodWords[i].erase(0, m_goodWords[i].find_first_not_of(' '));
            m_goodWords[i].erase(m_goodWords[i].find_last_not_of(' ') + 1);

            ++i;
        }
    }

    void SpellChecker::operator()(std::string& text) {
        for (size_t i = 0; i < WORD_LIST_SIZE; ++i) {
            size_t pos = 0;
            while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                m_replaceCounts[i]++;
                pos += m_goodWords[i].length();
            }
        }
    }


    void SpellChecker::showStatistics(std::ostream& out) const {
        out << "Spellchecker Statistics\n";
        for (size_t i = 0; i < WORD_LIST_SIZE; i++) {
            out.width(15);
            out << std::right << m_badWords[i] << ": " << m_replaceCounts[i] << " replacements\n";
        }
    }
}
