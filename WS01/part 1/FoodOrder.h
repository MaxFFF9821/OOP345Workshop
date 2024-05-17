#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

namespace seneca {
    class FoodOrder {
        char foodOrder[10];
        char foodDescription[25];
        double foodPrice;
        bool dailySpecial;
    public:
        FoodOrder();
        std::istream& read(std::istream& is);
        void display(std::ostream& os) const;

    };
    extern double g_taxrate;
    extern double g_dailydiscount;
}




#endif