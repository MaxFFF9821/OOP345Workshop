#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include <iostream>
#include <string>

inline std::string trim(const std::string &str) {
    size_t start = 0;
    while (start < str.size() && str[start] == ' ') {
        start++;
    }

    size_t end = str.size();
    while (end > start && str[end - 1] == ' ') {
        end--;
    }

    return str.substr(start, end - start);
}

namespace seneca {
    class Book{
        std::string m_author;
        std::string m_title;
        std::string m_country;
        std::string m_desc;
        double m_price;
        size_t m_year;
    public:
        Book() = default;
        Book(const std::string &strBook);
        const std::string &title() const;
        const std::string &country() const;
        const size_t& year() const;
        double &price();
        friend std::ostream &operator<<(std::ostream &os, const Book &book);
        
        template <typename T>
        void fixSpelling(T& spellChecker) {
            spellChecker(m_desc);
        }
    };
}

#endif