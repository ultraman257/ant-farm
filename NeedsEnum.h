//
// Created by matth on 15/06/2023.
//

#ifndef SIMULITE_STATESENUM_H
#define SIMULITE_STATESENUM_H


#include <stdexcept>

enum Need {
    FOOD = 0,
    ENTERTAINMENT = 1,
    COMFORT = 2,
    MONEY = 3,
    MEDICAL = 4,
    NONE = 6,
    SHOP = 7
};

constexpr const char* NeedToString(Need n) throw() {
    switch (n) {
        case Need::FOOD: return "Food";
        case Need::ENTERTAINMENT: return "Entertainment";
        case Need::COMFORT: return "Comfort";
        case Need::MONEY: return "Money";
        case Need::MEDICAL: return "Medical";
        case Need::NONE: return "None";
        case Need::SHOP: return "Shop";
        default: throw std::invalid_argument("Unimplemented State");
    }
}

constexpr const int NeedToInt(Need n) throw() {
    switch (n) {
        case Need::FOOD: return 0;
        case Need::ENTERTAINMENT: return 1;
        case Need::COMFORT: return 2;
        case Need::MONEY: return 3;
        case Need::MEDICAL: return 4;
        case Need::NONE: return 6;
        case Need::SHOP: return 7;
        default: throw std::invalid_argument("Unimplemented State");
    }
}


#endif //SIMULITE_STATESENUM_H
