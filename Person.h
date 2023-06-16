//
// Created by matth on 14/06/2023.
//

#ifndef SIMULITE_PERSON_H
#define SIMULITE_PERSON_H


#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include "StatesEnum.h"

class Person {

    int id;

    State current = AIMLESS;

    bool showDebug;

    // Basic stats
    int food;
    int hunger;
    int wealth;
    int comfort;
    int entertainment;

    int maxEnergy;
    int energy;

    bool refill = false;

    int locX = 495;
    int locY = 495;

    int pathfinding[2];

    int homeLocation[2];

    Fl_Button *currentItem;

    Fl_Double_Window* window;

    Fl_Box *foodDebug;
    Fl_Box *hungerDebug;
    Fl_Box *wealthDebug;
    Fl_Box *comfortDebug;
    Fl_Box *entertainmentDebug;
    Fl_Box *maxEnergyDebug;
    Fl_Box *energyDebug;
    Fl_Box *stateDebug;

    std::string foodLabel;
    std::string hungerLabel;
    std::string wealthLabel;
    std::string comfortLabel;
    std::string entertainmentLabel;
    std::string energyLabel;


public:
    Person() {

        food = rand()%(1000-25 + 1) + 25;
        hunger = rand()%(1000-25 + 1) + 25;
        wealth = rand()%(1000-25 + 1) + 25;
        comfort = rand()%(1000-25 + 1) + 25;
        entertainment = 50;

        showDebug = false;

        maxEnergy = rand()%(100-25 + 1) + 25;
        energy = maxEnergy;

    }
    Person* setId(int i) {
        id = i;
        return this;
    }

    static void showWindowStatic(Fl_Widget* button, void* data) {
        Person* p = (Person*) data;
        p->showWindow();
    }

    void showWindow() {
        if(showDebug) {
            window->hide();
            showDebug = false;
        } else {

            // We crete a new window, we'll use it for the GUI.
            std::string idName = "PDebug" + std::to_string(id);
            window = new Fl_Double_Window(500,200, idName.c_str());


            stateDebug = new Fl_Box(20, 20, 480, 50, StateToString(current));

            foodLabel = "Food: " + std::to_string(food);
            foodDebug = new Fl_Box(20, 50, 480, 50, foodLabel.c_str());

            hungerLabel= "Hunger: " + std::to_string(hunger);
            hungerDebug = new Fl_Box(20, 70, 480, 50, hungerLabel.c_str());

            wealthLabel= "Wealth: " + std::to_string(wealth);
            wealthDebug = new Fl_Box(20, 90, 480, 50, wealthLabel.c_str());

            comfortLabel = "Comfort: " + std::to_string(comfort);
            comfortDebug = new Fl_Box(20, 110, 480, 50, comfortLabel.c_str());

            entertainmentLabel = "Boredom: " + std::to_string(entertainment);
            entertainmentDebug = new Fl_Box(20, 130, 480, 50, entertainmentLabel.c_str());

            energyLabel = "Energy: " + std::to_string(energy) + "/" + std::to_string(maxEnergy);
            energyDebug = new Fl_Box(20, 150, 480, 50, energyLabel.c_str());

            window->show();

            showDebug = true;

        }
    }

    void refreshDisplay() {
        if(showDebug) {

            stateDebug->label(StateToString(current));

            if(food < 0) food = 0;
            foodLabel = "Food: " + std::to_string(food);
            foodDebug->label(foodLabel.c_str());

            if(hunger < 0) hunger = 0;
            hungerLabel = "Hunger: " + std::to_string(hunger);
            hungerDebug->label(hungerLabel.c_str());

            if(wealth < 0) wealth = 0;
            wealthLabel = "Wealth: " + std::to_string(wealth);
            wealthDebug->label(wealthLabel.c_str());

            comfortLabel = "Comfort: " + std::to_string(comfort);
            comfortDebug->label(comfortLabel.c_str());

            if(entertainment < 0) entertainment = 0;
            entertainmentLabel = "Boredom: " + std::to_string(entertainment);
            entertainmentDebug->label(entertainmentLabel.c_str());

            energyLabel = "Energy: " + std::to_string(energy) + "/" + std::to_string(maxEnergy);
            energyDebug->label(energyLabel.c_str());

            window->redraw();

        }
    }

    State calculateTopNeed(State currentState) {

        refreshDisplay();

        if(food < 100 && hunger < 100) return SHOP;
        if(food > 0 && hunger < 100) return FOOD;

//        if(food > 50) return FOOD;
//
//
        if(currentState == FOOD && hunger < 1500 && food > 0) return FOOD;
        if(currentState == RELAXING && comfort < 1500) return RELAXING;
        if(wealth <= 50) return POOR;
        if((currentState == WORKING || currentState == POOR) && wealth < 2000) return WORKING;
        if((currentState == WORKING || currentState == POOR) && wealth > 1500) return AIMLESS;

        if(currentState == RELAXING && comfort > 5000) return AIMLESS;

        if(comfort < 200) return RELAXING;

        if(entertainment < 50) return BOREDOM;

        return AIMLESS;

    }

    int goHome(int x, int y) {
        homeLocation[0] = x;
        homeLocation[1] = y;

        locX = x;
        locY = y;
    }
    int setPathFind(int x, int y) {
        pathfinding[0] = x;
        pathfinding[1] = y;
    }
    int setPathFindX(int x) {
        pathfinding[0] = x;
    }
    int setPathFindY(int y) {
        pathfinding[1] = y;
    }
    int getY() {
        return locY;
    }

    int getX() {
        return locX;
    }

    void setBox(Fl_Button *item) {
        currentItem = item;
        currentItem->callback(showWindowStatic, this);
    };
    Fl_Button * getBox() {
        return currentItem;
    }

    int moveTo() {

        current = calculateTopNeed(current);

        if(current == POOR) gotoWork();
        if(current == SHOP) gotoShop();
        if(current == FOOD) gotoHome();
        if(current == BOREDOM) gotoGallery();
        if(current == RELAXING) gotoHome();


        if(current == AIMLESS) {
            // Create some randomness for choosing who gets a new endpoint.
            std::random_device rd;
            std::mt19937 gen(rd());
            // THis is random number for which person is selected.
            std::uniform_int_distribution<int> upGen(0, 100);
            // This generates the random position.
            std::uniform_int_distribution<int> posGen(0, 990);

            if(upGen(rd) % 10 == 0) {

            setPathFind(posGen(rd), posGen(rd));
            }
        }

        // Work
        if(locX == 850 && locY == 150) {
            current = WORKING;
            wealth = wealth + rand()%(20-5 + 1) + 5;
        }

        // Food
        if(locX == 950 && locY == 950) {
            current = FEEDING;
            food = rand()%(5000-1000 + 1) + 1000;
        }

        // Home
        if(locX == homeLocation[0] && locY == homeLocation[1]) {
            if(food >= 0) {
                hunger = hunger + rand()%(5-1 + 1) + 1;
                food = food - rand()%(5-1 + 1) + 1;
            }
            comfort = comfort + rand()%(50-1 + 1) + 1;
        }

        if(locX == 890 && locY == 250) {
            entertainment = entertainment + rand() % (500 - 1 + 1) + 1;
        }

        hunger = hunger - rand()%(5-1 + 1) + 1;
        wealth = wealth - rand()%(5-1 + 1) + 1;
        comfort = comfort - rand()%(5-1 + 1) + 1;
        entertainment = entertainment - rand() % (5 - 1 + 1) + 1;

        if(hunger < 0) hunger = 0;
        if(wealth < 0) wealth = 0;
        if(comfort < 0) comfort = 0;
        if(entertainment < 0) entertainment= 0;
        if(food < 0) food = 0;

        if(refill) {

            energy = energy + 10;

            if(energy >= maxEnergy) {
                refill = false;
            }

            return 0;

        }

        if(energy < 0) {
            energy = 0;
            refill = true;
            return 0;
        }

        energy = energy - rand()%(5-1 + 1) + 1;

        float slope;

        int newX = locX;
        int newY = locY;

        // Handle any X movement
        if(locX != pathfinding[0]) {

            // Check the direction
            // We need to move right
            if(locX < pathfinding[0]) {
                newX = locX + 1;
            } else if(locX > pathfinding[0]) {
                newX = locX - 1;
            }

        }

        // Handle any Y movement
        if(locY != pathfinding[1]) {

            // Check the direction
            // We need to move right
            if(locY < pathfinding[1]) {
                newY = locY + 1;
            } else if(locX > pathfinding[1]) {
                newY = locY - 1;
            }

        }

        // Check so we can't go out of bounds
        if(!(newX > 10 && newX < 990 )) {
            newX = locX;
        }
        // Check so we can't go out of bounds
        if(!(newY > 10 && newY < 990 )) {
            newY = locY;
        }

        locX = newX;
        locY = newY;

       if(showDebug) {
           currentItem->color(FL_DARK_GREEN);
       } else {
           currentItem->color(FL_RED);
       }
       // Update the dots position and re-add the
        currentItem->position(locX, locY);
        currentItem->callback(showWindowStatic, this);
        currentItem->redraw();

        return 0;
    }

    // Nagivation Functions
    void gotoGallery() {
        setPathFindX(890);
        setPathFindY(250);
    }

    void gotoShop() {
        setPathFind(950, 950);
    }

    void gotoWork() {
        setPathFind(850, 150);
    }

    void gotoHome() {
        setPathFind(homeLocation[0], homeLocation[1]);
    }
};


#endif //SIMULITE_PERSON_H
