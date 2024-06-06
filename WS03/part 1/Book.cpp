//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/05/31
#include "Book.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace seneca;
using namespace std;

Book::Book(){};

Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
{
    m_title = title;
    m_numChapters = nChapters;
    m_numPages = nPages;
}

bool Book::isValid() const
{
    return !m_title.empty() && m_numChapters > 0 && m_numPages > 0;
}

string Book::getTitle() const
{
    return m_title;
}

unsigned Book::getNumChapters() const
{
    return m_numChapters;
}

unsigned Book::getNumPages() const
{
    return m_numPages;
}

std::ostream& Book::print(std::ostream& os) const {
    if (isValid()) {
        string details = m_title + "," + to_string(m_numChapters) + "," + to_string(m_numPages);
        os << setw(56) << right << details << " | "
        << setw(15) << left << "(" + to_string(static_cast<double>(m_numPages) / m_numChapters) + ")";    
    } else {
        os << "| Invalid book data";
    }
    return os;
}

std::ostream& seneca::operator<<(std::ostream& os, const Book& bk)
{
    return bk.print(os);
}