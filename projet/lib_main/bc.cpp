#define F_CPU 8000000UL
#include <util/delay.h>
#include "bc.h"
#include "robot.h"
#include "timer.h"

extern Robot robot;


void BC::determineMode() {
    uint8_t choice1 = 0; 
    uint8_t choice2 = 0;
    int countPress = 0;
    
    while (countPress < MAX_COUNT_PRESS) { 
        if (robot.buttonBb.readButton()) { 
            robot.led.turnRed(); 
            (countPress == BOOL_CHOICE_FALSE) ? choice1 = BOOL_CHOICE_TRUE : choice2 = BOOL_CHOICE_TRUE;
            while (robot.buttonBb.readButton()) {}
            robot.led.turnOff();
            ++countPress;
        } 
        else if (robot.buttonInt.readButton()) { 
            robot.led.turnGreen();
            (countPress == BOOL_CHOICE_FALSE) ? choice1 = BOOL_CHOICE_FALSE : choice2 = BOOL_CHOICE_FALSE;
            while (robot.buttonInt.readButton()) {}
            robot.led.turnOff();
            ++countPress;
        }
    }

    if (choice1 == BOOL_CHOICE_TRUE && choice2 == BOOL_CHOICE_TRUE) mode = Modes::LEFT_LEFT;
    else if (choice1 == BOOL_CHOICE_FALSE && choice2 == BOOL_CHOICE_FALSE) mode = Modes::RIGHT_RIGHT;
    else if (choice1 == BOOL_CHOICE_TRUE && choice2 == BOOL_CHOICE_FALSE) mode = Modes::LEFT_RIGHT;
    else mode = Modes::RIGHT_LEFT;
}


void BC::leftB() {
    robot.song.play(SONG_NOTE);
    _delay_ms(NOTE_DELAY);
    robot.song.stop();

    robot.pwm.moveForward(MOVE_FORWARD_SPEED);
    _delay_ms(MOVE_DELAY_1);
    robot.l.turnLeftDelay();
    robot.l.center();
    do{robot.l.moveStart();} while (!robot.l.isWhite());
    robot.pwm.stop();
}

void BC::leftC() {
    robot.song.play(SONG_NOTE);
    _delay_ms(NOTE_DELAY);
    robot.song.stop();

    robot.pwm.moveForward(MOVE_FORWARD_SPEED);
    _delay_ms(NOTE_DELAY);
    robot.l.turnLeftDelay();
    do{robot.l.moveStart();} while (!robot.l.isWhite());
    robot.pwm.miniGo();
    robot.l.turnRightDelay();
    robot.l.center();
    do{robot.l.moveStart();} while (!robot.l.isWhite());
    }

void BC::rightB() {
    robot.song.play(SONG_NOTE);
    _delay_ms(NOTE_DELAY);
    robot.song.stop();

    robot.pwm.moveForward(MOVE_FORWARD_SPEED);
    _delay_ms(MOVE_DELAY_1);
    robot.l.turnRightDelay();
    robot.l.center();
    do{robot.l.moveStart();} while (!robot.l.isWhite());
    robot.pwm.stop();
    
}

void BC::rightC() {
    robot.song.play(SONG_NOTE);
    _delay_ms(NOTE_DELAY);
    robot.song.stop();

    robot.pwm.moveForward(MOVE_FORWARD_SPEED);
    _delay_ms(NOTE_DELAY);
    robot.l.turnRightDelay();
    robot.l.center();
    do{robot.l.moveStart();} while (!robot.l.isWhite());
    robot.pwm.miniGo();
    robot.l.turnLeftDelay();
    robot.l.center();
    do{robot.l.moveStart();} while (!robot.l.isWhite());
}

void BC::modeLeftLeft() {
    leftB();
    leftC();
}

void BC::modeRightRight() {
    rightB();
    rightC();
}

void BC::modeLeftRight() {
    leftB();
    rightC();
}

void BC::modeRightLeft() {
    rightB();
    leftC();
}

void BC::executeMode() {
    switch (mode) {
        case Modes::LEFT_LEFT: modeLeftLeft(); break;
        case Modes::RIGHT_RIGHT: modeRightRight(); break;
        case Modes::LEFT_RIGHT: modeLeftRight(); break;
        case Modes::RIGHT_LEFT: modeRightLeft(); break;
    }
}