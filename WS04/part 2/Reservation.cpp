//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/06/08
#include "Reservation.h"
#include <iomanip>
#include <string>

namespace seneca {

    Reservation::Reservation(const std::string& res) {
        size_t start = 0;
        size_t end = res.find(':');
        m_ResID = res.substr(start, end - start);
        m_ResID.erase(0, m_ResID.find_first_not_of(' '));
        m_ResID.erase(m_ResID.find_last_not_of(' ') + 1);

        start = end + 1;
        end = res.find(',', start);
        m_ResName = res.substr(start, end - start);
        m_ResName.erase(0, m_ResName.find_first_not_of(' '));
        m_ResName.erase(m_ResName.find_last_not_of(' ') + 1);

        start = end + 1;
        end = res.find(',', start);
        m_ResEmail = res.substr(start, end - start);

        m_ResEmail.erase(0, m_ResEmail.find_first_not_of(' '));
        m_ResEmail.erase(m_ResEmail.find_last_not_of(' ') + 1);

        start = end + 1;
        end = res.find(',', start);
        std::string peopleStr = res.substr(start, end - start);
        m_ResPeople = std::stoi(peopleStr);

        start = end + 1;
        end = res.find(',', start);
        std::string dayStr = res.substr(start, end - start);
        m_ResDay = std::stoi(dayStr);

        start = end + 1;
        std::string hourStr = res.substr(start);
        m_ResHour = std::stoi(hourStr);
    }

    void Reservation::update(int day, int hour) {
        m_ResDay = day;
        m_ResHour = hour;
    }

    std::ostream& operator<<(std::ostream& os, const Reservation& res) {
        std::string meal = "Drinks";

        if (res.m_ResHour >= 6 && res.m_ResHour <= 9) {
            meal = "Breakfast";
        } else if (res.m_ResHour >= 11 && res.m_ResHour <= 15) {
            meal = "Lunch";
        } else if (res.m_ResHour >= 17 && res.m_ResHour <= 21) {
            meal = "Dinner";
        }

        os << "Reservation ";
        os << std::setw(10) << std::right << res.m_ResID << ": ";
        os << std::setw(20) << std::right << res.m_ResName << "  ";
        os << std::setw(20) << std::left << ("<" + res.m_ResEmail + ">") << "    ";
        os << meal << " on day " << res.m_ResDay << " @ " << res.m_ResHour << ":00 for ";
        os << res.m_ResPeople << (res.m_ResPeople == 1 ? " person." : " people.") << std::endl;

        return os;
    }
}
