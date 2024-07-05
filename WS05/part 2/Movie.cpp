// I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
// Name: Max Feng
// Student ID:136141231
// Date:2024/06/15

#include "Movie.h"
#include "Book.h"
#include <iomanip>

namespace seneca {
    Movie::Movie(const std::string& strMovie) {
        size_t start = 0;
        size_t end = strMovie.find(',');

        m_title = trim(strMovie.substr(start, end - start));

        start = end + 1;
        end = strMovie.find(',', start);

        std::string yearStr = trim(strMovie.substr(start, end - start));
        m_year = std::stoul(yearStr);

        start = end + 1;
        m_description = trim(strMovie.substr(start));
    }

    const std::string& Movie::title() const {
        return m_title;
    }

    std::ostream& operator<<(std::ostream& os, const Movie& movie) {
        os << std::setw(40) << movie.m_title << " | "
           << std::setw(4) << movie.m_year << " | "
           << movie.m_description << std::endl;
        return os;
    }
}
