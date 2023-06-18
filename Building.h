//
// Created by matth on 15/06/2023.
//

#ifndef SIMULITE_BUILDING_H
#define SIMULITE_BUILDING_H

#include <FL/Fl_Box.H>
#include "CoordsUtils.h"

class Building {

    Fl_Box* buildingBox;

    int locationX;
    int locationY;


public:
    Building(int x, int y, int w, int h, const char *name, const Fl_Color colour) {

        buildingBox = new Fl_Box(x, y, w, h, name);

        locationX = x + (w/2);
        locationY = y + (h/2);

        buildingBox->box(FL_BORDER_BOX);
        buildingBox->labelcolor(colour);
        buildingBox->labelsize(36);

    }

    Fl_Box* getBuilding() {
        return buildingBox;
    }
    Building* getSelf() {
        return this;
    }
    Coords getLocation() {
        return Coords(locationX, locationY);
    }
};


#endif //SIMULITE_BUILDING_H
