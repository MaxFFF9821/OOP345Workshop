//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/05/31
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <iostream>
#include "Book.h"
namespace seneca {
    template <typename T, size_t C>
    class Collection {
        T m_items[C];
        size_t m_size{0};
        static T m_smallestItem;
        static T m_largestItem;
    protected:
        void setSmallestItem(const T& item){
            if (m_size == 0 || item < m_smallestItem) {
                m_smallestItem = item;
            }
        }
        
        void setLargestItem(const T& item){
            if (m_size == 0 || item > m_largestItem) {
                m_largestItem = item;
            }
        }
    public:
        Collection() = default;
        static T getSmallestItem() { return m_smallestItem; }
        static T getLargestItem() { return m_largestItem; }
        size_t size() const { return m_size; }
        size_t capacity() const { return C; }
        bool operator+=(const T& item) {
            if (m_size < C) {
                setSmallestItem(item);
                setLargestItem(item);
                m_items[m_size++] = item;
                return true;
            }
            return false;
        }

        void print(std::ostream& os) const {
            os << "[";
            for (size_t i = 0; i < m_size; i++) {
                if (i < m_size - 1) {
                    os << m_items[i] << ",";
                } else {
                    os << m_items[i] << "]";
                }
            }
            os << std::endl;
        }
    };
    template <typename T, size_t C>
    T Collection<T, C>::m_smallestItem = static_cast<T>(9999);

    template <typename T, size_t C>
    T Collection<T, C>::m_largestItem = static_cast<T>(-9999);

    template <>
    Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);

    template <>
    Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);

}
#endif