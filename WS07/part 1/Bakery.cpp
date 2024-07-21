//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/07/13

#include "Bakery.h"
#include <fstream>
#include <algorithm>
#include <iomanip>

namespace seneca {
    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \r\n\t");
        size_t last = str.find_last_not_of(" \r\n\t");

        if (start == std::string::npos) start = 0;
        if (last == std::string::npos) last = str.length() - 1;

        return str.substr(start, last - start + 1);
    }

    Bakery::Bakery(const std::string& fileName) {
        std::ifstream file(fileName);

        if (!file) {
            throw std::runtime_error("File " + fileName + " not found!");
        }

        while (file) {
            std::string line;
            std::getline(file, line);

            if (file) {
                BakedGood item;
                item.type = line[0] == 'B' ? BakedType::BREAD : BakedType::PASTERY;

                item.description = trim(line.substr(8, 20));
                item.shelfLife = std::stoi(trim(line.substr(28, 14)));
                item.stock = std::stoi(trim(line.substr(42, 8)));
                item.price = std::stod(trim(line.substr(50, 6)));

                bakedGoods.push_back(item);
            }
        }
    }

    void Bakery::showGoods(std::ostream& os) const {
        std::for_each(bakedGoods.begin(), bakedGoods.end(), [&os](const BakedGood& item) {
            os << item;
        });
    }

    std::ostream& operator<<(std::ostream& os, const BakedGood& b) {
        os << "* ";

        os << std::setw(10) << std::left << (b.type == BakedType::BREAD ? "Bread" : "Pastry") << " * "
           << std::setw(20) << std::left << b.description << " * "
           << std::setw(5) << std::left << b.shelfLife << " * "
           << std::setw(5) << std::left << b.stock << " * "
           << std::setw(8) << std::right << std::fixed << std::setprecision(2) << b.price << " * " << std::endl;

        return os;
    }
}
