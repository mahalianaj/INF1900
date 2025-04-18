#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>

#include "gridSelection.h"
#include "debug.h"
#include "robot.h"

extern Robot robot;

void centerGrid(){
    robot.pwm.stop();
    robot.l.center();
    robot.l.center();
    _delay_ms(CHECK_DELAY);
    robot.l.center();
    robot.l.center();
}

void checkGrid(Grid& grid){
    bool rightChoice = 0;
    while (!robot.l.d1())
        robot.pwm.newTurnRight(CHECK_TURN_IMPLUSE); 
    robot.pwm.stop();
    _delay_ms(BEFORE_CHECK_DELAY);

    while (!(robot.l.isCenterFull())){
        robot.pwm.newTurnRight(CHECK_TURN_IMPLUSE);
        _delay_ms(CHECK_DELAY);
        robot.pwm.stop();
        _delay_ms(CHECK_DELAY);
    
        if (robot.distanceSensor.isObstacle1()) {
            DEBUG_PRINT("obstacle ");
            robot.led.turnGreen();
            _delay_ms(HALF_SECOND_WAIT);
            rightChoice = false; 
            break;
        } else {
            robot.l.center();
            robot.l.center();
            rightChoice = true; 
        }
    }

    if (!rightChoice) {
        robot.l.turnLeftDelay();
        _delay_ms(RIGHT_CHOICE_DELAY);
        robot.pwm.newTurnLeft(60);
        _delay_ms(RIGHT_CHOICE_DELAY);
        robot.l.turnLeftDelay();

        robot.l.center();
        robot.l.center();
        grid.state = LEFT_FREE;
    } else {
        robot.l.center();
        robot.l.center();
        grid.state = RIGHT_FREE;
    }
}

void checkGrid2(Grid& grid){
    bool rightChoice = 0;
    while (!robot.l.d1())
        robot.pwm.newTurnRight(CHECK_TURN_IMPLUSE);
    // robot.pwm.newTurnRight(60);
    // _delay_ms(100);  
    robot.pwm.stop();
    _delay_ms(BEFORE_CHECK_DELAY);

    while (!(robot.l.isCenterFull())) {
        robot.pwm.newTurnRight(CHECK_TURN_IMPLUSE);
        _delay_ms(CHECK_DELAY);
        robot.pwm.stop();
        _delay_ms(CHECK_DELAY);
    

        if (robot.distanceSensor.isObstacle1()) {
            robot.led.turnGreen();
            _delay_ms(HALF_SECOND_WAIT);
            DEBUG_PRINT("obstacle! ");
            rightChoice = false; // state = LeftFree
            break;
        } else {
            robot.l.center();
            robot.l.center();
            rightChoice = true; // state = RightFree
        }
    }   

    if (!rightChoice) {
        robot.l.turnLeftDelay();
        _delay_ms(RIGHT_CHOICE_DELAY);
        robot.pwm.newTurnLeft(60);
        _delay_ms(RIGHT_CHOICE_DELAY);  
        robot.l.turnLeftDelay();

        robot.l.center();
        robot.l.center();
        grid.state = LEFT_FREE_2;
    } else {
        robot.l.center();
        robot.l.center();
        grid.state = RIGHT_FREE_2;
    }
}

void waitCheck() {
    robot.pwm.stop();
        _delay_ms(WAIT_CHECK_DELAY);
        _delay_ms(WAIT_CHECK_DELAY);
        robot.led.turnOff();
}

void centerFree() {
    DEBUG_PRINT("center free ");
    DEBUG_PRINT("1er black ");
    robot.pwm.stop();
    robot.led.blinkGreen4Hz();
    robot.l.moveForwardTo(Black);
    centerGrid();
    robot.l.moveForwardTo(Center);
    centerGrid();

    DEBUG_PRINT("2e black ");
    robot.l.moveForwardTo(Black);
    centerGrid();

    _delay_ms(100);
    robot.l.center();
    robot.l.center();
    robot.pwm.miniGo();
    centerGrid();

}

void rightFree(){
    DEBUG_PRINT("right free ");
    robot.pwm.stop();
    robot.led.blinkGreen4Hz();
    robot.l.moveForwardTo(White);
    DEBUG_PRINT("1e intersection ");
    robot.pwm.miniGo();
    centerGrid();
   
    robot.l.turnLeftDelay();
    centerGrid();
    
    _delay_ms(WAIT_FREE);
    do{robot.l.moveStart();} while (!robot.l.isLeftIntersection());

	robot.l.moveDelay(800);
	do{robot.l.moveStart();} while (!robot.l.isLeftIntersection());

    robot.pwm.miniGo();
    centerGrid();
   
    robot.l.turnLeftDelay();
    centerGrid();


    robot.l.moveForwardTo(Black);
    centerGrid();

    robot.pwm.miniGo();
    centerGrid();

    robot.l.turnRightDelay();
    centerGrid();


}

void leftFree(){
    DEBUG_PRINT("left free ");
    robot.pwm.stop();
    robot.led.blinkGreen4Hz();
    robot.l.moveForwardTo(White);
    DEBUG_PRINT("1e intersection ");

    robot.pwm.miniGo();
    centerGrid();

    robot.l.turnRightDelay();
    centerGrid();
    
    _delay_ms(WAIT_FREE);

    DEBUG_PRINT("2e intersection ");
     do{robot.l.moveStart();} while (!robot.l.isRightIntersection());

	robot.l.moveDelay(800);
	do{robot.l.moveStart();} while (!robot.l.isRightIntersection());

    robot.pwm.miniGo();
    centerGrid();

    robot.l.turnRightDelay();
    centerGrid();

    robot.l.moveForwardTo(Black);
    DEBUG_PRINT("millieu ");
    centerGrid();

    robot.pwm.miniGo();
    centerGrid();
    
    robot.l.turnLeftDelay();
    centerGrid();
    robot.l.center();
    robot.l.center();

}

void rightFree2(){
    DEBUG_PRINT("right free ");
    robot.pwm.stop();
    robot.led.blinkGreen4Hz();
    robot.l.moveForwardTo(White);
    DEBUG_PRINT("1e intersection ");

    robot.pwm.miniGo();
    robot.l.turnLeftDelay();
    centerGrid();
    robot.l.moveForwardTo(White);
    DEBUG_PRINT("2e intersection ");

    robot.pwm.miniGo();
    centerGrid();
    robot.l.turnRightDelay();
    centerGrid();
}

void leftFree2(){
    DEBUG_PRINT("left free ");
    robot.pwm.stop();
    robot.led.blinkGreen4Hz();
    robot.l.moveForwardTo(White);
    DEBUG_PRINT("1e intersection ");

    robot.pwm.miniGo();
    robot.l.turnRightDelay();
    centerGrid();
    robot.l.moveForwardTo(White);
    DEBUG_PRINT("3e intersection ");

    robot.pwm.miniGo();
    centerGrid();

    robot.l.turnRightDelay();
    centerGrid();

}

Grid::Grid() : state(INIT) {}

void Grid::executeGrid(){
    while (state != TERM) {
        switch (state){
            case INIT:
                DEBUG_PRINT("INIT ");

                do { robot.l.move();} while ( robot.l.isBlack());

                robot.l.moveDelay(1500);
                robot.pwm.stop();
                waitCheck();
                if (!robot.distanceSensor.isObstacle1()) {
                    state = CENTER_FREE;
                } else {
                    state = CHECK_SCAN;
                }
                break;

            case CENTER_FREE :
                DEBUG_PRINT("CENTER_FREE ");
                centerFree();
                state = CHECK_SCAN_2;
                break;

            case CHECK_SCAN:
                DEBUG_PRINT("CHECK_SCAN ");
                checkGrid(*this);
                break;
            
            case RIGHT_FREE:
                DEBUG_PRINT("RIGHT_FREE "); 
                rightFree();
                state = CHECK_SCAN_2;
                break;
            
            case LEFT_FREE:
            DEBUG_PRINT("LEFT_FREE ");
                leftFree();
                state = CHECK_SCAN_2;
                break;

            case CHECK_SCAN_2:
            DEBUG_PRINT("CHECK_SCAN_2 ");
                waitCheck();
                if (!robot.distanceSensor.isObstacle1()) {
                    state = CENTER_FREE_2;
                } else {
                    checkGrid2(*this);
                }
                break;

            case CENTER_FREE_2:
            DEBUG_PRINT("CENTER_FREE_2 ");
                robot.pwm.stop();
                robot.led.blinkGreen4Hz();
                robot.l.moveForwardTo(White);

                robot.pwm.miniGo();
                robot.l.turnRightDelay();
                centerGrid();
                state = END;
                break;


            case LEFT_FREE_2:
            DEBUG_PRINT("LEFT_FREE_2 ");

                leftFree2();
                state = END;
                break;

            case RIGHT_FREE_2:
                DEBUG_PRINT("RIGHT_FREE_2 ");
                rightFree2();
                state = END;
                break;

            case END:
            DEBUG_PRINT("END ");
                centerGrid();
                robot.pwm.boost();
                robot.pwm.boost();
                centerGrid();
                do{robot.l.moveStart();} while (!robot.l.isWhite());
                robot.pwm.moveForward(MOVE_SPEED);
	            _delay_ms(WAIT_FREE);
                robot.l.turnRightDelay();
                robot.pwm.stop();
                state = TERM;
                break;
            default :
                break;
        }
    }
}