/*
*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*lineMaker.h
*
*Description:  The LineMaker class enables the robot to follow black lines on the ground using the infrared sensor on the robot.
* The class includes functions to read individual sensor values and determine the robot’s current alignment relative
* to the line through logical methods such as isCenter(), isLeft(), isRight(), and others. It uses the Position enumeration
* to represent various line detection states like Center, MostLeft, RightCorner, and White. In addition to line detection,
* the class provides movement and adjustment methods, including move(), moveForwardTo(Position), moveDelay(), center(),
* turnLeftDelay(), and turnRightDelay(), allowing the robot to adapt its motion based on sensor input. Timing and delay
* behaviors are controlled through predefined constants and a static variable endTimer, which can be used to synchronize
* movements with timers.
* State Machines : Can be found in read me file.
*/

#ifndef LINEMAKER_H
#define LINEMAKER_H

#include <avr/io.h> 

constexpr uint8_t MOVE_START_PERCENTAGE = 50;
constexpr uint8_t START_TURN_ADJUSTMENT_S = 40;
constexpr uint8_t START_TURN_ADJUSTMENT_L = 50;
constexpr uint8_t START_NEW_TURN_ADJUSTMENT = 70;

constexpr uint8_t CENTER_TURN_PERCENTAGE = 70;
constexpr uint8_t CENTER_DELAY = 75;
constexpr uint8_t MOVE_PERCENTAGE = 50;
constexpr uint8_t SHORT_TURN_ADJUSTMENT = 40;
constexpr uint8_t LONG_TURN_ADJUSTMENT = 50;
constexpr uint8_t MID_TURN_ADJUSTMENT = 50;

constexpr uint8_t FIRST_TURN_L = 55;
constexpr uint8_t FIRST_TURN_R = 55;

constexpr uint8_t WHILE_TURN_DELAY_PERCENTAGE = 80;
constexpr uint8_t TURN_DELAY_DELAY = 60;
constexpr uint16_t WHILE_DELAY = 300;

constexpr uint8_t DELAY_20 = 20;



enum Position {Center, FullCenter, Right, Left, MostRight, MostLeft, Black, White, RightCorner, LeftCorner, Unknown};

class LineMaker{

    public:
        LineMaker(); 
        bool d1();
        bool d2();
        bool d3();
        bool d4();
        bool d5();
        bool isCenter();
        bool isCenterFull();
        bool isRight();
        bool isLeft();
        bool isBlack();
        bool isWhite();
        bool isMostRight();
        bool isMostLeft();
        bool isRightIntersection();
        bool isLeftIntersection();
        Position getPosition();
        void move();
        void moveStart();
        void moveForwardTo(Position targetPosition);
        void moveDelay(uint16_t delay);
        static volatile uint8_t endTimer;
        void center();
        void turnRightDelay();
        void turnLeftDelay();
};

#endif