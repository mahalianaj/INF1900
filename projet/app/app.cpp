/*
*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*app.cpp
*
*Description: This program compiles the navigation of the path the robot must follow. The robot must record a button selection
* corresponding to a LED, and we ensure that the robot advances after a two-second delay until it detects either
* white, in which case it will begin the path knowing that it started from point A, or black, in which case it will
* begin the path knowing that it started from point J. The robot stops when it returns to its starting point.
*/
#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include "robot.h"

extern Robot robot;
constexpr uint16_t MOVE_DELAY_BEFORE_HOUSE = 3500;
constexpr uint16_t MOVE_DELAY_BEFORE_BC = 4800;
constexpr uint16_t DELAY_MS_BEFORE_ROBOT_START = 2000;


void robotStartedFromA(){
    robot.pwm.stop();
    robot.bc.executeMode();
    robot.pwm.boost();
    robot.houseSequence.Start();
    robot.pwm.boost();
    robot.pwm.boost();
    do{robot.l.moveStart();} while (!robot.l.isBlack());
    robot.gridSelection.executeGrid();
    robot.led.blinkRedGreen2Hz();
}

void robotStartedFromJ(){
    robot.gridSelection.executeGrid();
    robot.pwm.boost();
    do{robot.l.moveStart();} while (!robot.l.isWhite());
    robot.pwm.stop();
    robot.bc.executeMode();
    robot.pwm.boost();
    robot.pwm.boost();
    robot.houseSequence.Start();
    robot.pwm.stop();
    robot.led.blinkRedGreen2Hz();
}

void sequenceBeforeStartingCourse(){
    robot.bc.determineMode();
    _delay_ms(DELAY_MS_BEFORE_ROBOT_START);
}

int main(){ 
    sequenceBeforeStartingCourse();
    robot.pwm.boost();
    robot.pwm.boost();
    do{robot.l.moveStart();} while (!robot.l.isWhite() && !robot.l.isBlack());
    if (robot.l.isWhite()){robotStartedFromA();} else {robotStartedFromJ(); }
}