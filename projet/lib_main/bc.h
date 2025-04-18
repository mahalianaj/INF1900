/*
*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*bc.h
*
*Description: The BC class handles user input at points B and C using two buttons. It determines the chosen path 
* based on the sequence of buttons pressed and executes the corresponding navigation sequence.
* The selected mode is stored using an enum (Modes) and executed via the executeMode() method.
*/


#ifndef BC_H
#define BC_H

enum class Modes {
    LEFT_LEFT,
    RIGHT_RIGHT,
    LEFT_RIGHT,
    RIGHT_LEFT
};

class BC {
public:
    void determineMode();
    void executeMode();
    constexpr static uint8_t BOOL_CHOICE_TRUE = 1;
    constexpr static uint8_t BOOL_CHOICE_FALSE = 0;
    constexpr static uint8_t MAX_COUNT_PRESS = 2;
    

private:
    Modes mode;
    void leftB();
    void leftC();
    void rightB();
    void rightC();
    void modeLeftLeft();
    void modeRightRight();
    void modeLeftRight();
    void modeRightLeft();
    constexpr static uint8_t SONG_NOTE = 45;
    constexpr static uint8_t MOVE_FORWARD_SPEED = 60;
    constexpr static uint16_t NOTE_DELAY = 1000;
    constexpr static uint16_t MOVE_DELAY_1= 1200;
    constexpr static uint16_t MOVE_DELAY_2 = 2000;
    constexpr static uint16_t MOVE_DELAY_3 = 2500;
    constexpr static uint16_t MOVE_DELAY_4= 1700;
    constexpr static uint16_t MOVE_DELAY_5= 1500;
    constexpr static uint16_t MOVE_DELAY_6= 1750;
    constexpr static uint16_t MOVE_DELAY_7= 2600;
    constexpr static uint16_t MOVE_DELAY_8= 1800;
};

#endif
