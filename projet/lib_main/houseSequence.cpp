#define F_CPU 8000000UL
#include <util/delay.h>
#include "robot.h"
#include "houseSequence.h"


extern Robot robot;

void HouseSequence::Start() {
	robot.pwm.miniGo();
	robot.l.turnRightDelay();
	_delay_ms(DELAY_TURN_RIGHT);
	robot.l.center();
	do{robot.l.moveStart();} while (!robot.l.isRightIntersection());

	robot.l.moveDelay(DELAY_TURN_RIGHT);
	do{robot.l.moveStart();} while (!robot.l.isRightIntersection());

	robot.pwm.miniGo();
	robot.l.center();
	robot.l.turnRightDelay(); 
	robot.l.center();
	do{robot.l.moveStart();} while (!robot.l.isRightIntersection());

	robot.pwm.newTurnLeft(MOVE_SPEED);
	_delay_ms(TURN_OR_MOVE_DELAY);
	robot.pwm.moveForward(MOVE_SPEED);
	_delay_ms(DELAY_AFTER_MOVE_FORWARD);
	robot.l.turnRightDelay();
	robot.pwm.stop();
    robot.l.center();
    _delay_ms(DELAY_100);
    robot.l.center();
	robot.pwm.stop();
	_delay_ms(DELAY_TURN_RIGHT);
	if (!robot.distanceSensor.isObstacle1()){HPathFree();}else {HPathObstacle();}
}

void HouseSequence::HPathFree() { 
	robot.led.blinkGreen4Hz();
	robot.pwm.stop();
	robot.l.moveForwardTo(White);
	robot.pwm.moveForward(MOVE_SPEED);
	_delay_ms(DELAY_TURN_RIGHT);
	robot.l.center();
	robot.l.turnRightDelay();
	robot.l.center();
	robot.l.center();
	do{robot.l.moveStart();} while (!robot.l.isWhite());
	// robot.l.turnRightDelay();
	// robot.l.center();
	// robot.l.center();
	// robot.l.moveForwardTo(White);
	Exit();
}

void HouseSequence::HPathObstacle(){
	robot.led.blinkRed4Hz();
	robot.pwm.stop();
	robot.l.turnRightDelay();
	robot.l.center();
	robot.l.center();
	robot.l.moveForwardTo(White);
	robot.pwm.stop();
	robot.pwm.moveForward(MOVE_SPEED);
	_delay_ms(DELAY_AFTER_MOVE_FORWARD);
	robot.l.center();
	robot.l.turnRightDelay();
	robot.l.center();
	robot.l.center(); 
	robot.l.moveForwardTo(White);
	Exit();
}

void HouseSequence::Exit(){
	robot.pwm.moveForward(MOVE_SPEED);
	_delay_ms(DELAY_IN_EXIT);
	robot.l.turnRightDelay();
	robot.l.center();
	robot.l.center();
	robot.l.moveForwardTo(White);
	robot.pwm.moveForward(MOVE_SPEED);
	_delay_ms(DELAY_IN_EXIT);
	robot.l.turnRightDelay();
	robot.l.center();
}