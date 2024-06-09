//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/06/08

#include "ConfirmationSender.h"

namespace seneca {
    ConfirmationSender::ConfirmationSender() : m_reservations(nullptr), m_count(0) {}

    // Copy constructor
    ConfirmationSender::ConfirmationSender(const ConfirmationSender& other) : m_reservations(nullptr), m_count(0) {
        *this = other;
    }

    // Copy assignment operator
    ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& other) {
        if (this != &other) {
            delete[] m_reservations;

            m_count = other.m_count;
            if (m_count > 0) {
                m_reservations = new const Reservation*[m_count];
                for (size_t i = 0; i < m_count; i++) {
                    m_reservations[i] = other.m_reservations[i];
                }
            } else {
                m_reservations = nullptr;
            }
        }
        return *this;
    }

    // Move constructor
    ConfirmationSender::ConfirmationSender(ConfirmationSender&& other) noexcept : m_reservations(other.m_reservations), m_count(other.m_count) {
        other.m_reservations = nullptr;
        other.m_count = 0;
    }

    // Move assignment operator
    ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& other) noexcept {
        if (this != &other) {
            delete[] m_reservations;

            m_reservations = other.m_reservations;
            m_count = other.m_count;

            other.m_reservations = nullptr;
            other.m_count = 0;
        }
        return *this;
    }

    // Destructor
    ConfirmationSender::~ConfirmationSender() {
        delete[] m_reservations;
    }

    ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res) {
        bool alreadyInArray = false;
        for (size_t i = 0; i < m_count; i++) {
            if (m_reservations[i] == &res) {
                alreadyInArray = true;
                break;
            }
        }

        if (!alreadyInArray) {
            const Reservation** temp = new const Reservation*[m_count + 1];
            for (size_t i = 0; i < m_count; i++) {
                temp[i] = m_reservations[i];
            }
            temp[m_count] = &res;

            delete[] m_reservations;
            m_reservations = temp;
            ++m_count;
        }

        return *this;
    }

    ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res) {
        bool found = false;
        for (size_t i = 0; i < m_count; i++) {
            if (m_reservations[i] == &res) {
                m_reservations[i] = nullptr;
                found = true;
                break;
            }
        }

        if (found) {
            size_t newSize = 0;
            for (size_t i = 0; i < m_count; i++) {
                if (m_reservations[i] != nullptr) {
                    ++newSize;
                }
            }

            const Reservation** temp = new const Reservation*[newSize];
            size_t index = 0;
            for (size_t i = 0; i < m_count; i++) {
                if (m_reservations[i] != nullptr) {
                    temp[index++] = m_reservations[i];
                }
            }

            delete[] m_reservations;
            m_reservations = temp;
            m_count = newSize;
        }

        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const ConfirmationSender& sender) {
        os << "--------------------------" << std::endl;
        os << "Confirmations to Send" << std::endl;
        os << "--------------------------" << std::endl;
        if (sender.m_count == 0) {
            os << "There are no confirmations to send!" << std::endl;
        } else {
            for (size_t i = 0; i < sender.m_count; i++) {
                os << *sender.m_reservations[i];
            }
        }
        os << "--------------------------" << std::endl;
        return os;
    }
}
