/*
*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*motor.h
*
*Description: The PWM class controls the robot's motor via PWM on an Atmega324PA. It initializes pins 2 and timer 2 to generate a PWM signal. 
* The user can adjust the speed and direction of the motors. The method allows the motor to move forward, backward, rotate,
* or stop. The PWM signal intensity is modulated between 0 and 100% to control the speed.
*/

#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>

class PWM{
    public:
        PWM(volatile uint8_t* portx = &PORTD , volatile uint8_t* ddrx = &DDRD, uint8_t pinA = PD6, uint8_t pinB =  PD7, uint8_t pinDirectionA = PD4, uint8_t pinDirectionB = PD5);

        void initialize();
        void adjustment(uint8_t valueA, uint8_t valueB);
        void moveForward(uint8_t intensity);
        void moveBackward(uint8_t intensity);
        void turn(uint8_t valueA, uint8_t valueB);
        void turnLeft90();
        void turnRight90();
        void newTurnLeft(uint8_t intensity);
        void newTurnRight(uint8_t intensity);
        void stop();
        void boost();
        void boostLeft();
        void boostRight();
        void miniGo();
        constexpr static uint16_t AJUSTEMENT = 5;
        constexpr static uint16_t TURN_SPEED = 80;
        constexpr static uint16_t TURN_DELAY = 650;
        constexpr static uint16_t BOOST_TURN_DELAY = 10;
        constexpr static uint16_t MINI_GO_SPEED = 50;
        constexpr static uint16_t MINI_GO_DELAY = 1600;
        constexpr static uint16_t BOOST_SPEED = 100;
        constexpr static uint16_t BOOST_DELAY = 5;

    private:
        volatile uint8_t* port_;
        uint8_t pinA_;
        uint8_t pinB_;
        uint8_t pinDirectionA_;
        uint8_t pinDirectionB_;  
        volatile uint8_t* DDR_;

};

#endif