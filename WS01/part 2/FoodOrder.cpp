//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/05/17
#include "FoodOrder.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;
using namespace seneca;

double seneca::g_taxrate = 0.0;
double seneca::g_dailydiscount= 0.0;

FoodOrder::FoodOrder(): foodOrder(nullptr), foodDescription(nullptr), foodPrice(0.0), dailySpecial(false){}

FoodOrder::FoodOrder(const FoodOrder &src){
    foodOrder = new char[strlen(src.foodOrder) + 1];
    foodDescription = new char[strlen(src.foodDescription) + 1];
    strcpy(foodOrder, src.foodOrder);
    strcpy(foodDescription, src.foodDescription);
    foodPrice = src.foodPrice;
    dailySpecial = src.dailySpecial;

}

FoodOrder& FoodOrder::operator=(const FoodOrder &src) {
    if (this != &src)
    {
        deallocate();
        foodOrder = new char[strlen(src.foodOrder) + 1];
        foodDescription = new char[strlen(src.foodDescription) + 1];
        strcpy(foodOrder, src.foodOrder);
        strcpy(foodDescription, src.foodDescription);
        foodPrice = src.foodPrice;
        dailySpecial = src.dailySpecial;
    }
    return *this;
}

void FoodOrder::deallocate(){
    delete[] foodOrder;
    delete[] foodDescription;
    foodOrder = nullptr;
    foodDescription = nullptr;
}

FoodOrder::~FoodOrder() {
    deallocate();
}

istream& FoodOrder::read(istream& is) {
    if (is.good()) {
        std::string tempfoodOrder;
        std::string tempfoodDescription;
        getline(is, tempfoodOrder, ',');
        getline(is, tempfoodDescription, ',');
        is >> foodPrice;
        is.ignore(1, ',');
        char specialStatus;
        is >> specialStatus;
        dailySpecial = (specialStatus == 'Y');
        is.ignore(1000, '\n');
        deallocate();
        foodOrder = new char[tempfoodOrder.length() + 1];
        strcpy(foodOrder, tempfoodOrder.c_str());
        foodDescription = new char[tempfoodDescription.length() + 1];
        strcpy(foodDescription, tempfoodDescription.c_str());
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

