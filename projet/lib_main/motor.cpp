#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "motor.h"
#include "robot.h"

extern Robot robot;

PWM::PWM(volatile uint8_t *portx, volatile uint8_t *ddrx, uint8_t pinA, uint8_t pinB, uint8_t pinDirectionA, uint8_t pinDirectionB)
{
    port_ = portx;
    DDR_ = ddrx;
    pinA_ = pinA;
    pinB_ = pinB;
    pinDirectionA_ = pinDirectionA;
    pinDirectionB_ = pinDirectionB;
    initialize();

};

void PWM::initialize()
{
    *DDR_ |= (1 << pinA_) | (1 << pinB_) | (1 << pinDirectionA_) | (1 << pinDirectionB_);

    TCCR2A |= (1 << WGM20);
    TCCR2A |= (1 << COM2B1);
    TCCR2A |= (1 << COM2A1);

    TCCR2B |= (1 << CS11);
  
}

void PWM:: adjustment(uint8_t valueA, uint8_t valueB){
    constexpr uint16_t MULTIPLIER = 255;
    constexpr uint16_t DIVIDER = 100;

    OCR2A = (valueA * MULTIPLIER) / DIVIDER;
    OCR2B = (valueB * MULTIPLIER) / DIVIDER; 
}

void PWM::moveForward(uint8_t intensity)
{
    *port_ &= ~(1 << pinDirectionA_);
    *port_ &= ~(1 << pinDirectionB_);

    initialize();

    adjustment(intensity, intensity);
}

void PWM::moveBackward(uint8_t intensity)
{
    *port_ |= (1 << pinDirectionA_);
    *port_ |= (1 << pinDirectionB_);

    initialize();

    adjustment(intensity, intensity);
}

void PWM::turn(uint8_t valueA, uint8_t valueB)
{
    *port_ &= ~(1 << pinDirectionA_);
    *port_ &= ~(1 << pinDirectionB_);

    initialize();

    adjustment(valueA, valueB);
}

void PWM::turnLeft90(){
    turn(TURN_SPEED, 0);
    _delay_ms(TURN_DELAY);
    stop();
}

void PWM::turnRight90(){
    turn(0, TURN_SPEED);
    _delay_ms(TURN_DELAY);
    stop();
}

void PWM::stop()
{
    initialize();

    adjustment(0, 0);
}

void PWM::boost() {
    moveForward(TURN_SPEED);
    _delay_ms(AJUSTEMENT);
}

void PWM::miniGo(){
    boost();
    moveForward(MINI_GO_SPEED);
    _delay_ms(MINI_GO_DELAY);
    robot.l.center();
    stop();
}

void PWM::boostLeft(){
    turn(TURN_SPEED,0);
    _delay_us(BOOST_TURN_DELAY);
}

void PWM::boostRight(){
    turn(0,TURN_SPEED);
    _delay_us(BOOST_TURN_DELAY);
}

void PWM::newTurnLeft(uint8_t intensity){
    *port_ |= (1 << pinDirectionA_);
    *port_ &= ~(1 << pinDirectionB_);

    adjustment(intensity, intensity );
}

void PWM::newTurnRight(uint8_t intensity){
    *port_ |= (1 << pinDirectionB_);
    *port_ &= ~(1 << pinDirectionA_);

    adjustment(intensity, intensity);
}