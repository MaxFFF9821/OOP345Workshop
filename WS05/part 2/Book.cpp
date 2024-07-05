//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/06/15
#include "Book.h"
#include <iomanip>

namespace seneca {

Book::Book(const std::string &strBook) {
    size_t start = 0;
    size_t end = strBook.find(',');

    m_author = trim(strBook.substr(start, end - start));

    start = end + 1;
    end = strBook.find(',', start);

    m_title = trim(strBook.substr(start, end - start));

    start = end + 1;
    end = strBook.find(',', start);

    m_country = trim(strBook.substr(start, end - start));

    start = end + 1;
    end = strBook.find(',', start);

    std::string priceStr = trim(strBook.substr(start, end - start));
    m_price = std::stod(priceStr);

    start = end + 1;
    end = strBook.find(',', start);

    std::string yearStr = trim(strBook.substr(start, end - start));
    m_year = std::stoul(yearStr);

    start = end + 1;
    m_desc = trim(strBook.substr(start));
}

const std::string &Book::title() const {
    return m_title;
}

const std::string &Book::country() const {
    return m_country;
}

const size_t& Book::year() const { 
    return m_year; 
    }

double &Book::price() {
    return m_price;
}

std::ostream &operator<<(std::ostream &os, const Book &book) {
    os << std::setw(20) << book.m_author << " | "
       << std::setw(22) << book.m_title << " | "
       << std::setw(5) << book.m_country << " | "
       << std::setw(4) << book.m_year << " | "
       << std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | "
       << book.m_desc << std::endl;
    return os;
}

} 