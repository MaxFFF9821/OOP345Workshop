//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/05/17
#include "FoodOrder.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace seneca;

double seneca::g_taxrate = 0.0;
double seneca::g_dailydiscount= 0.0;

FoodOrder::FoodOrder(){};

istream& FoodOrder::read(istream& is) {
    if (is.good()) {
        is.getline(foodOrder, 10, ',');
        is.getline(foodDescription, 25, ',');
        is >> foodPrice;
        is.ignore(1, ',');
        char specialStatus;
        is >> specialStatus;
        dailySpecial = (specialStatus == 'Y');
        is.ignore(1000, '\n');
    }
    return is;
}

void FoodOrder::display(ostream& os) const {
    static int counter = 1;
    double taxedPrice = foodPrice * (1 + g_taxrate);
    os.setf(ios::left);
    os.precision(2);
    os.width(2);
    os << counter++ << ". ";
    if (foodOrder[0] == '\0') {
        os << "No Order" << endl;
        return;
    }
    os.width(10);
    os << foodOrder << "|";
    os.width(25);
    os << foodDescription << "|";
    os.width(12);
    os << fixed << setprecision(2) << taxedPrice << "|";
    os.width(13);
    os.unsetf(ios::left);
    if (dailySpecial){
        double specialPrice = taxedPrice - g_dailydiscount;
        os.setf(ios::right);
        os << setw(13) << fixed << setprecision(2) << specialPrice << endl;
        os.unsetf(ios::right);
    }else {
        os << endl;
    }
}

