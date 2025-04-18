/*
*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*gridSequence.h
*
*Description: The Grid class manages the robot's navigation through a grid-based intersection system. It determines whether 
*   the path is free or blocked using infrared sensors and a distance sensor, then updates the robot’s path accordingly.
*   The class handles different path states through a step-based state machine implemented in the executeGrid() method.
*State Machine : Can be found in read me file
*/


#ifndef Grid_H
#define Grid_H

constexpr uint8_t MOVE_SPEED = 60;
constexpr uint8_t WAIT_CHECK_DELAY = 200;
constexpr uint16_t RIGHT_CHOICE_DELAY = 600;
constexpr uint8_t CHECK_TURN_IMPLUSE = 90;
constexpr uint16_t BEFORE_CHECK_DELAY = 500;
constexpr uint8_t CHECK_DELAY = 100;
constexpr uint16_t HALF_SECOND_WAIT = 1500;
constexpr uint16_t MOVE_DELAY = 5000;
constexpr uint16_t WAIT_FREE = 750; 

enum Step { INIT, CENTER_FREE, CHECK_SCAN, RIGHT_FREE, LEFT_FREE, CHECK_SCAN_2, 
            CENTER_FREE_2, LEFT_FREE_2, RIGHT_FREE_2, END, TERM };

class Grid {
public:
    Grid();
    void executeGrid();
    Step state;
};

#endif