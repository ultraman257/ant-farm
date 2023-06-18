//
// Created by matth on 17/06/2023.
//

#ifndef SIMULITE_BUILDINGMANAGER_H
#define SIMULITE_BUILDINGMANAGER_H

#include <vector>
#include <iostream>
#include "Building.h"
#include "RequirementEnum.h"

struct buildingLocation {

    buildingLocation(int x,int y, Need buildingNeed, Building *buildingPointer) {
        locationX = x;
        locationY = y;
        state = buildingNeed;
        Building = buildingPointer;
    }

    int locationX;
    int locationY;
    Need state;
    Building *Building;
} ;


extern buildingLocation *locations[30];

class BuildingManager {


public:
    void addBuilding(Building *building, Need need) {

        for (auto & location : locations) {
            if(location == nullptr) {
                location = new buildingLocation(building->getLocation().getX(),building->getLocation().getY(), need, building);
                break;
            }
        }
    }

    // Check the location meets any needs
    Need checkLocation(Coords location) {
        for (auto & i : locations) {
            // Check if the array item is null, its small so far...
            if(i != nullptr) {
                if(i->locationX == location.getX() && i->locationY == location.getY()) {
                    std::cout << "Type: " << NeedToString(i->state) << std::endl;
                    return i->state;
                };
            } else {
                break;
            }
        }
        return NONE;

    }

    Building* getBuildings(Need need, Coords location) {

        std::vector<Building*> tempItems;

        for(auto & i : locations) {
            if(i != nullptr) {
                if(need == i->state) tempItems.push_back(i->Building);
            }
        }

        if(tempItems.empty()) return nullptr;

        Building* closestBuilding = tempItems.at(0);
        int closestDistance = 99999;

        for(auto & b : tempItems) {

            int distanceFrom = sqrt(abs(b->getLocation().getX() - location.getX()) + abs(b->getLocation().getY() - location.getY()) );

            std::cout << "Distance: " + std::to_string(distanceFrom) << std::endl;

            if(closestDistance >= distanceFrom) {
                closestBuilding = b;
                closestDistance = distanceFrom;
            }

        }

        return closestBuilding;

    }

    void printBuildings() {
        for (int i = 0; i < 30; ++i) {
            if(locations[i] != nullptr) {
                std::cout << NeedToString(locations[i]->state) << std::endl;
            }
        }
    }
};


#endif //SIMULITE_BUILDINGMANAGER_H
