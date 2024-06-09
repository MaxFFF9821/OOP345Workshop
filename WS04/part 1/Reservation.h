//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/06/08
#ifndef SENECA_RESERVATION_H
#define SENECA_RESERVATION_H
#include <iostream>
#include <string>

namespace seneca {
    class Reservation {
        std::string m_ResID;
        std::string m_ResName;
        std::string m_ResEmail;
        int m_ResPeople;
        int m_ResDay;
        int m_ResHour;
    public:
        Reservation() = default;
        Reservation(const std::string& res);
        void update(int day, int hour);
        friend std::ostream& operator<<(std::ostream& os, const Reservation& res);
    };
}
#endif