/*
*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*robot.h
*
*Description: The Robot class groups all the necessary modules for the robot's various functions into one
* centralized class. The goal of this class is to simplify the programming of the robot by encapsulating
* all the required hardware and software components (motors, sensors, buttons, memory, etc.)
* in a single object. This way, only one Robot object needs to be instantiated in order to easily access
* all the available features without having to manage each module individually.
*
*Material Identification : 
*   LED : positive pin on PA0, negative on PA1
*   Distance sensor : PA2 and VCC/GDN on PORTC
*   Line follower : d1 on PA3, d2 on PA4, d3 on PA5, d4 on PA6, D5 on PA7, VCC/GND on PORTD
*   Breadboard button : input on PB0, VCC/GND on PORTA
*   Interrupt button : input on PD2
*   Piezo : positive pin on PB2, negative on PB3
*   Motors : PD4 on direction left, PD5 on direction right, PD6 on enable left, PD7 on enable right
*/

#ifndef ROBOT_H
#define ROBOT_H

#include <avr/io.h>
#include "button.h"
#include "led.h"
#include "motor.h"
#include "timer.h"
#include "song.h"
#include "can.h"
#include "uart.h"
#include "debug.h"
#include "memory.h"
#include "lineMaker.h"
#include "distanceSensor.h"
#include "bc.h"
#include "gridSelection.h"
#include "houseSequence.h"


class Robot{
public:
    Robot() : led(), buttonInt(), buttonBb(&PINB, &DDRB, PB0 , 0, AE), pwm(), timer(), song(), canObj(), 
              uart(), memory(), l(), distanceSensor(), houseSequence(), gridSelection(), bc() {} 
      

    LED led;
    Button buttonInt;
    Button buttonBb;
    PWM pwm;
    Timer timer;
    Song song;
    can canObj;
    Uart uart;
    Memoire24CXXX memory;
    LineMaker l;
    DistanceSensor distanceSensor;
    HouseSequence houseSequence;
    Grid gridSelection;
    BC bc;
};

#endif