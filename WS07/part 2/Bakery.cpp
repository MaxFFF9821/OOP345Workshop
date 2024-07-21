//I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my workshops and assignments. This submitted piece of work has not been shared with any other student or 3rd party content provider.
//Name: Max Feng
//Student ID:136141231
//Date:2024/07/13

#include "Bakery.h"
#include <fstream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <stdexcept> 

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

        do {
            std::string line;
            std::getline(file, line);

            if (file.good()) {
                BakedGood bakedItem;
                std::string typeStr = trim(line.substr(0, 8));

                if (typeStr == "Bread") {
                    bakedItem.type = BakedType::BREAD;
                } else if (typeStr == "Pastry") {
                    bakedItem.type = BakedType::PASTERY;
                } else {
                    throw std::runtime_error("Invalid BakedType in file");
                }

                bakedItem.description = trim(line.substr(8, 20));
                bakedItem.shelfLife = std::stoi(trim(line.substr(28, 14)));
                bakedItem.stock = std::stoi(trim(line.substr(42, 8)));
                bakedItem.price = std::stod(trim(line.substr(50, 6)));

                m_bakedGoods.push_back(bakedItem);
            }
        } while (file.good());
    }

    void Bakery::showGoods(std::ostream& os) const {
        size_t totalStock = std::accumulate(m_bakedGoods.begin(), m_bakedGoods.end(), 0,
            [](size_t sum, const BakedGood& bakedItem) {
                return sum + bakedItem.stock;
            }
        );

        double totalPrice = std::accumulate(m_bakedGoods.begin(), m_bakedGoods.end(), 0.0,
            [](double sum, const BakedGood& bakedItem) {
                return sum + bakedItem.price;
            }
        );

        std::for_each(m_bakedGoods.begin(), m_bakedGoods.end(),
            [&os](const BakedGood& bakedItem) {
                os << bakedItem << std::endl;
            }
        );

        os << "Total Stock: " << totalStock << std::endl;

        os << "Total Price: ";
        os.precision(2);
        os << std::fixed << totalPrice << std::endl;
    }

    void Bakery::sortBakery(const std::string& fieldName) {
        bool (*compare) (const BakedGood& item1, const BakedGood& item2) = nullptr;

        if (fieldName == "Description") {
            compare = [](const BakedGood& item1, const BakedGood& item2) {
                return item1.description < item2.description;
            };
        } else if (fieldName == "Shelf") {
            compare = [](const BakedGood& item1, const BakedGood& item2) {
                return item1.shelfLife < item2.shelfLife;
            };
        } else if (fieldName == "Stock") {
            compare = [](const BakedGood& item1, const BakedGood& item2) {
                return item1.stock < item2.stock;
            };
        } else if (fieldName == "Price") {
            compare = [](const BakedGood& item1, const BakedGood& item2) {
                return item1.price < item2.price;
            };
        }

        std::sort(m_bakedGoods.begin(), m_bakedGoods.end(), compare);
    }

    std::vector<BakedGood> Bakery::combine(Bakery& otherBakery) {
        std::vector<BakedGood> combinedBakedGoods{};

        sortBakery("Price");
        otherBakery.sortBakery("Price");

        std::merge(
            m_bakedGoods.begin(), m_bakedGoods.end(),
            otherBakery.m_bakedGoods.begin(), otherBakery.m_bakedGoods.end(),
            std::back_inserter(combinedBakedGoods),
            [](const BakedGood& item1, const BakedGood& item2) {
                return item1.price < item2.price;
            }
        );
        return combinedBakedGoods;
    }

    bool Bakery::inStock(const std::string description, const BakedType bakedType) const {
        return std::any_of(m_bakedGoods.begin(), m_bakedGoods.end(),
            [&description, &bakedType](const BakedGood& bakedItem) {
                return bakedItem.description == description && bakedItem.type == bakedType && bakedItem.stock > 0;
            }
        );
    }

    std::list<BakedGood> Bakery::outOfStock(const BakedType bakedType) const {
        std::list<BakedGood> outOfStockItems{};

        std::copy_if(m_bakedGoods.begin(), m_bakedGoods.end(), std::back_inserter(outOfStockItems),
            [&bakedType](const BakedGood& bakedItem) {
                return bakedItem.type == bakedType && bakedItem.stock == 0;
            }
        );
        return outOfStockItems;
    }

    std::ostream& operator<<(std::ostream& os, const BakedGood& bakedItem) {
        os << "* ";
        os << std::setw(10) << std::left << (bakedItem.type == BakedType::BREAD ? "Bread" : "Pastry") << " * ";
        os << std::setw(20) << std::left << bakedItem.description << " * ";
        os << std::setw(5) << std::left << bakedItem.shelfLife << " * ";
        os << std::setw(5) << std::left << bakedItem.stock << " * "; 
        os << std::setw(8) << std::right << std::fixed << std::setprecision(2) << bakedItem.price << " * ";
        return os;
    }
}