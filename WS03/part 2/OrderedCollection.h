//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/05/31
#ifndef SENECA_ORDEREDCOLLECTION_H
#define SENECA_ORDEREDCOLLECTION_H

#include "Collection.h"

namespace seneca {

template <typename T>
class OrderedCollection : public Collection<T, 72> {
public:
    bool operator+=(const T& item) {
        if (this->size() < this->capacity()) {
            size_t i = this->size();
            while (i > 0 && item < (*this)[i - 1]) {
                (*this)[i] = (*this)[i - 1];
                i--;
            }
            (*this)[i] = item;
            this->incrSize();
            this->setSmallestItem(item);
            this->setLargestItem(item);
            return true;
        }
        return false;
    }
};

} // namespace seneca

#endif
