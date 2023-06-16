//
// Created by matth on 15/06/2023.
//

#ifndef SIMULITE_STATESENUM_H
#define SIMULITE_STATESENUM_H


#include <stdexcept>

enum State {
    FOOD = 0,
    FEEDING = 1,
    POOR = 2,
    WORKING = 3,
    RELAXING = 4,
    BOREDOM = 5,
    AIMLESS = 6,
    SHOP = 7
};

constexpr const char* StateToString(State s) throw() {
    switch (s) {
        case State::FOOD: return "Food";
        case State::FEEDING: return "Eating";
        case State::POOR: return "Poor";
        case State::WORKING: return "Working";
        case State::RELAXING: return "Relaxing";
        case State::BOREDOM: return "Boredom";
        case State::SHOP: return "Shop";
        case State::AIMLESS: return "Aimless";
        default: throw std::invalid_argument("Unimplemented State");
    }
}


#endif //SIMULITE_STATESENUM_H
