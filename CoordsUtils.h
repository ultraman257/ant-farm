//
// Created by matth on 17/06/2023.
//

#ifndef SIMULITE_COORDSUTILS_H
#define SIMULITE_COORDSUTILS_H


struct Coords {

    int locationX;
    int locationY;

    Coords(int x, int y) {
        locationX = x;
        locationY = y;
    };
    int getX() {
        return locationX;
    }
    int getY() {
        return locationY;
    }


};


class CoordsUtils {

};


#endif //SIMULITE_COORDSUTILS_H
