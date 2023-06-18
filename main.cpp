#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <thread>
#include <iostream>
#include <random>
#include "Person.h"
#include "Building.h"
#include "BuildingManager.h"
#include "RequirementEnum.h"

const int pCount = 1;

buildingLocation *locations[30];

Person *p[pCount];
Fl_Button *pBox[pCount];

std::vector<std::vector<int>> houseArray;

Fl_Double_Window *window;

BuildingManager *bm;

// This is the function the animates the points and runs what happens each frame.
void animateThread(void *data) {

    // For every person run the update function, telling them to move towards their waypoint.
    for (auto & i : p) {

        // Check if the current location meets any requirments.
        i->checkLocation();
        // Supplying 0,0 as the function used to accept a location to move to.
        i->moveTo();
    }

    // Redraw the window after all the points have moved.
    window->redraw();
    // Repeat this function
    Fl::repeat_timeout(0.05, animateThread, data);

}

// The ain application thread
int main(int argc, char **argv) {



    bm = new BuildingManager();

    // Populate the P[] array with people objects.
    for (int i = 0; i < pCount; ++i) {
        p[i] = new Person(bm);
        p[i]->setId(i);
    }

    // We crete a new window, we'll use it for the GUI.
    window = new Fl_Double_Window(1040,1040, "Simulation");

    // Create an outer bound.
    Fl_Box *boundingBox = new Fl_Box(20,20,1000,1000,"");
    boundingBox->box(FL_BORDER_BOX);

    // Make an building object, we do this so we can later use if for collisions etc hopefully.
    Building* storeBuilding = Building(740, 900, 250, 100, "Shop", FL_CYAN).getSelf();
    Building* storeExtraBuilding = Building(500, 60, 250, 100, "Shop", FL_CYAN).getSelf();
    Building* officeBuilding = Building(850,100,100,100,"Office", FL_RED).getSelf();
    Building* galleryBuilding = Building(870,220,80,140,"Gallery", FL_DARK_BLUE).getSelf();
    Building* office2Building = Building(200,400,80,140,"Office", FL_DARK_GREEN).getSelf();
    Building* theareBuilding = Building(870,560,80,140,"Theatre", FL_DARK_YELLOW).getSelf();

    bm->addBuilding(storeBuilding, SUPPLIES);
    bm->addBuilding(storeExtraBuilding, SUPPLIES);
    bm->addBuilding(officeBuilding, MONEY);
//    bm->addBuilding(office2Building, MONEY);
    bm->addBuilding(galleryBuilding, ENTERTAINMENT);
//    bm->addBuilding(theareBuilding, ENTERTAINMENT);

    bm->printBuildings();



    // Let's make a few buildings.
    Fl_Box *storeBox = storeBuilding->getBuilding();
    Fl_Box *officeBox = officeBuilding->getBuilding();
    Fl_Box *galleryBox = galleryBuilding->getBuilding();

    // Create a 3D array for houses.
    Fl_Box *house[10][20];

    // A row of 10 x 10 for houses
    for(int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Make a new variable called t, we use it for ignoring certain rows.
            int t = j;
            // Check J is not even, if it is add 5 onto our new variable changing it's offset.
            if(j % 2) {
                t = j + 5;
            }
            // Make x and y
            int x = ((t*30) + 30);
            int y = ((i * 32) + 30);
            // Add this house to the possible houses.
            houseArray.push_back({x, y});
            // Create a new box for the house at the x and y co-ords, with a width of 30
            // and a height of 30.
            house[i][j] = new Fl_Box(x, y, 30, 30, "House");
            // Add a border to the house so we can see it
            house[i][j]->box(FL_BORDER_BOX);
        }
    }

    // The same as before
    for(int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {

            int t = j;

            if(j % 2) {
                t = j + 5;
            }

            int x = ((t*30) + 30);
            int y = ((i * 32) + 650);

            houseArray.push_back({x, y});

            house[i][j] = new Fl_Box(x, y, 30, 30, "House");
            house[i][j]->box(FL_BORDER_BOX);
        }
    }


    // More randomness
    std::random_device rd;
    std::mt19937 gen(rd());
    // Random number gen for selecting their new waypoint.
    std::uniform_int_distribution<int> dis(10, 990);

    std::uniform_int_distribution<int> rndHouse(0, houseArray.size() - 1);

    for (int i = 0; i < pCount; ++i) {

        pBox[i] = new Fl_Button(p[i]->getX(), p[i]->getY(), 15, 15, "");

        pBox[i]->box(FL_CIRCLE_BOX);
        pBox[i]->color(FL_RED);

        int homeNum = rndHouse(rd);

        p[i]->goHome(houseArray[homeNum][0], houseArray[homeNum][1]);
        p[i]->setBox(pBox[i]);

        p[i]->setPathFind(dis(gen), dis(gen));

        p[i]->getBox()->position(40, 80);
    }

    window->end();
    window->show(argc, argv);

    Fl::add_timeout(0.01, animateThread, window);

    Fl::visual(FL_DOUBLE|FL_INDEX);

    return Fl::run();
}

