//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/05/17
#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H
#include <iostream>
namespace seneca {
    class FoodOrder {
        char* foodOrder;
        char* foodDescription;
        double foodPrice;
        bool dailySpecial;
    public:
        FoodOrder();
        ~FoodOrder();
        FoodOrder(const FoodOrder &src);
        FoodOrder& operator=(const FoodOrder &src);
        std::istream &read(std::istream &is);
        void display(std::ostream& os) const;
        void deallocate();

    };
    extern double g_taxrate;
    extern double g_dailydiscount;
}

#endif