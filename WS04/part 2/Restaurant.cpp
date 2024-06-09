//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/06/08

#include "Restaurant.h"

namespace seneca {
    Restaurant::Restaurant(const Reservation* reservations[], size_t cnt) : m_reservations(nullptr), m_count(cnt) {
        if (cnt > 0) {
            m_reservations = new Reservation*[m_count];
            for (size_t i = 0; i < m_count; i++) {
                m_reservations[i] = new Reservation(*reservations[i]);
            }
        }
    }

    // Copy constructor
    Restaurant::Restaurant(const Restaurant& other) : m_reservations(nullptr), m_count(0) {
        *this = other;
    }

    // Copy assignment operator
    Restaurant& Restaurant::operator=(const Restaurant& other) {
        if (this != &other) {
            for (size_t i = 0; i < m_count; i++) {
                delete m_reservations[i];
            }
            delete[] m_reservations;

            m_count = other.m_count;
            if (m_count > 0) {
                m_reservations = new Reservation*[m_count];
                for (size_t i = 0; i < m_count; i++) {
                    m_reservations[i] = new Reservation(*other.m_reservations[i]);
                }
            } else {
                m_reservations = nullptr;
            }
        }
        return *this;
    }

    // Move constructor
    Restaurant::Restaurant(Restaurant&& other) noexcept : m_reservations(other.m_reservations), m_count(other.m_count) {
        other.m_reservations = nullptr;
        other.m_count = 0;
    }

    // Move assignment operator
    Restaurant& Restaurant::operator=(Restaurant&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < m_count; i++) {
                delete m_reservations[i];
            }
            delete[] m_reservations;

            m_reservations = other.m_reservations;
            m_count = other.m_count;
            other.m_reservations = nullptr;
            other.m_count = 0;
        }
        return *this;
    }

    // Destructor
    Restaurant::~Restaurant() {
        for (size_t i = 0; i < m_count; i++) {
            delete m_reservations[i];
        }
        delete[] m_reservations;
    }

    size_t Restaurant::size() const {
        return m_count;
    }

    std::ostream& operator<<(std::ostream& os, const Restaurant& res) {
        static int call_count = 0;
        call_count++;

        os << "--------------------------" << std::endl;
        os << "Fancy Restaurant (" << call_count << ")" << std::endl;
        os << "--------------------------" << std::endl;

        if (res.m_count == 0) {
            os << "This restaurant is empty!" << std::endl;
        } else {
            for (size_t i = 0; i < res.m_count; i++) {
                os << *res.m_reservations[i];
            }
        }
        
        os << "--------------------------" << std::endl;

        return os;
    }
}
