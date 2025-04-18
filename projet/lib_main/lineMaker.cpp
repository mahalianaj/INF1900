#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lineMaker.h"
#include "led.h"
#include "motor.h"
#include "robot.h"


extern Robot robot;
volatile uint8_t LineMaker::endTimer = 0;

ISR(TIMER1_COMPA_vect){
    LineMaker::endTimer = 1;
}

LineMaker::LineMaker(){ 
    DDRA &= ~((1<<PA3) |(1<<PA4) |(1<<PA5) |(1<<PA6) |(1<<PA7));
    PORTA |= (1<<PA3) | (1<<PA4) | (1<<PA5) | (1<<PA6) | (1<<PA7); 

}

bool LineMaker::d1(){
     return PINA & (1<<PA3);
}

bool LineMaker::d2(){
    return PINA & (1<<PA4);
}

bool LineMaker::d3(){
    return PINA & (1<<PA5);
}

bool LineMaker::d4(){
    return PINA & (1<<PA6);
}

bool LineMaker::d5(){
    return PINA & (1<<PA7);
}

bool LineMaker::isCenter(){
    return d3() && !d2() && !d4() && !d1() && !d5();   // D3 seul allumé
}

bool LineMaker::isCenterFull(){
    return (d3() && !d2() && !d4() && !d1() && !d5()) || 
           (d3() && d2() && !d4() && !d1() && !d5())  || 
           (d3() && !d2() && d4() && !d1() && !d5())  || 
           (d3() && d2() && d4() && !d1() && !d5());
}

bool LineMaker::isRight(){
    return d4() && !d1() && !d2();
}

bool LineMaker::isLeft(){
    return !d4() && !d5() && d2();
}

bool LineMaker::isMostRight(){
    return !d4() && d5() && !d1() && !d2() && !d3();
}

bool LineMaker::isMostLeft(){
    return !d4() && !d5() && d1() && !d2() && !d3();
}


bool LineMaker::isBlack(){
    return d1() && d2() && d3() && d4() && d5();          
}

bool LineMaker::isWhite(){
    return !d1() && !d2() && !d3() && !d4() && !d5();      
}

bool LineMaker::isRightIntersection(){
    return (d3() && d4() && d5() && !d1() && !d2()) ||
           (d2() && d3() && d4() && d5() && !d1());
}

bool LineMaker::isLeftIntersection(){
    return (d1() && d2() && d3() && d4() && !d5()) ||
           (d1() && d2() && d3() && !d4() && !d5());
}

void LineMaker::center(){
    Position position = getPosition();
        switch (position)
        {
        case Center:
            break;

        case MostRight :
            do {
                robot.pwm.newTurnRight(CENTER_TURN_PERCENTAGE);
                _delay_ms(CENTER_DELAY);
                robot.pwm.stop();
                _delay_ms(CENTER_DELAY);
            } while (!d4());
            break;

        case MostLeft:
            do {
                robot.pwm.newTurnLeft(CENTER_TURN_PERCENTAGE);
                _delay_ms(CENTER_DELAY);
                robot.pwm.stop();
                _delay_ms(CENTER_DELAY);
            } while (!d2());
            break;

        default:
            break;

        }

    robot.pwm.stop();
}


Position LineMaker::getPosition() {
    if (isCenter())             return Center;
    if (isBlack())              return Black;
    if (isWhite())              return White;
    if (isLeft())               return Left;
    if (isRight())              return Right;
    if (isMostRight())          return MostRight;
    if (isMostLeft())           return MostLeft;
    if (isRightIntersection())  return (RightCorner);
    if (isLeftIntersection())   return (LeftCorner);
    if (isCenterFull())         return FullCenter;
    return Unknown;
}


void LineMaker::move(){
    Position position = getPosition();
    robot.pwm.boost();

    switch (position)
    {
    case Center:
        robot.pwm.moveForward(MOVE_PERCENTAGE);
        break;

    case Right :
        robot.pwm.turn(SHORT_TURN_ADJUSTMENT,MID_TURN_ADJUSTMENT);
        break;

    case Left :
        robot.pwm.turn(MID_TURN_ADJUSTMENT,SHORT_TURN_ADJUSTMENT);
        break;

    case MostLeft :
        robot.pwm.turn(LONG_TURN_ADJUSTMENT,SHORT_TURN_ADJUSTMENT);
        break;

    case MostRight :
       robot.pwm.turn(SHORT_TURN_ADJUSTMENT,LONG_TURN_ADJUSTMENT); 
        break;

    case Black :
        robot.pwm.moveForward(MOVE_PERCENTAGE);
        break;

    default:
        break;
    }
    _delay_ms(DELAY_20);
}

void LineMaker::moveStart(){
    Position position = getPosition();

    switch (position)
    {
    case Center:
        robot.pwm.moveForward(MOVE_START_PERCENTAGE); 
        break;

    case Right :
        robot.pwm.turn(START_TURN_ADJUSTMENT_S,START_TURN_ADJUSTMENT_L); 
        break;

    case Left :
        robot.pwm.turn(START_TURN_ADJUSTMENT_L,START_TURN_ADJUSTMENT_S); 
        break;

    case MostLeft :
        robot.pwm.stop();
        robot.pwm.newTurnLeft(START_NEW_TURN_ADJUSTMENT); 
        _delay_ms(15);
        break;

    case MostRight :
        robot.pwm.stop();
        robot.pwm.newTurnRight(START_NEW_TURN_ADJUSTMENT); 
        _delay_ms(15);
        break;

    case Black :
        robot.pwm.moveForward(MOVE_START_PERCENTAGE);
        break;

    default:
        break;

    case Unknown:
        robot.led.turnRed();
        robot.led.turnOff();
        break;
    }
    _delay_ms(DELAY_20);
}

void LineMaker::moveForwardTo(Position targetPosition) {
        do { move();} while ( getPosition() != targetPosition);
}

void LineMaker::turnRightDelay(){
    while (!isWhite() )
    {
        robot.pwm.newTurnRight(FIRST_TURN_R);
    }
    robot.pwm.stop();
    _delay_ms(WHILE_DELAY);
    while(!(d2())){
        robot.pwm.newTurnRight(WHILE_TURN_DELAY_PERCENTAGE);
        _delay_ms(TURN_DELAY_DELAY);
        robot.pwm.stop();
        _delay_ms(TURN_DELAY_DELAY);
    }
    center();
} 

void LineMaker::turnLeftDelay(){
    while (!isWhite())
    {
        robot.pwm.newTurnLeft(FIRST_TURN_L);

    }

    robot.pwm.stop();
    _delay_ms(WHILE_DELAY);
    while(!(d2())){
        robot.pwm.newTurnLeft(WHILE_TURN_DELAY_PERCENTAGE);
        _delay_ms(TURN_DELAY_DELAY);
        robot.pwm.stop();
        _delay_ms(TURN_DELAY_DELAY);
    }
    center();
}

void LineMaker::moveDelay(uint16_t delay){
    endTimer = 0;

    robot.timer.startTimer(delay); 
    robot.pwm.boost();
    while(!endTimer){
        move();
    }

    robot.pwm.stop();
}

