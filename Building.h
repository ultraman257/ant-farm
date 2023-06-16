//
// Created by matth on 15/06/2023.
//

#ifndef SIMULITE_BUILDING_H
#define SIMULITE_BUILDING_H

#include <FL/Fl_Box.H>

class Building {

    Fl_Box* buildingBox;


public:
    Building(int x, int y, int w, int h, const char *name, const Fl_Color colour) {

        buildingBox = new Fl_Box(x, y, w, h, name);

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
};


#endif //SIMULITE_BUILDING_H
