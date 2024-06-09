//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/06/08

#ifndef SENECA_RESTAURANT_H
#define SENECA_RESTAURANT_H

#include <iostream>
#include "Reservation.h"

namespace seneca {
    class Restaurant {
        Reservation** m_reservations;
        size_t m_count;

    public:
        Restaurant(const Reservation* reservations[], size_t cnt);
        Restaurant(const Restaurant& other); // Copy constructor
        Restaurant& operator=(const Restaurant& other); // Copy assignment operator
        Restaurant(Restaurant&& other) noexcept; // Move constructor
        Restaurant& operator=(Restaurant&& other) noexcept; // Move assignment operator
        ~Restaurant(); // Destructor

        size_t size() const;

        friend std::ostream& operator<<(std::ostream& os, const Restaurant& res);
    };
}

#endif
