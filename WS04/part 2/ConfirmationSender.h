//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/06/08

#ifndef SENECA_CONFIRMATIONSENDER_H
#define SENECA_CONFIRMATIONSENDER_H

#include <iostream>
#include "Reservation.h"

namespace seneca {
    class ConfirmationSender {
        const Reservation** m_reservations;
        size_t m_count;

    public:
        ConfirmationSender();
        ConfirmationSender(const ConfirmationSender& other); // Copy constructor
        ConfirmationSender& operator=(const ConfirmationSender& other); // Copy assignment operator
        ConfirmationSender(ConfirmationSender&& other) noexcept; // Move constructor
        ConfirmationSender& operator=(ConfirmationSender&& other) noexcept; // Move assignment operator
        ~ConfirmationSender(); // Destructor

        ConfirmationSender& operator+=(const Reservation& res);
        ConfirmationSender& operator-=(const Reservation& res);

        friend std::ostream& operator<<(std::ostream& os, const ConfirmationSender& sender);
    };
}

#endif
