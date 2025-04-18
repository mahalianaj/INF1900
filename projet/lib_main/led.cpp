#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include "led.h"


LED::LED(volatile uint8_t* portx, volatile uint8_t* ddrx, uint16_t positivePin, uint16_t negativePin) : portx_(portx), ddrx_(ddrx), positivePin_(positivePin), negativePin_(negativePin) {
    initializeLed();
}

void LED::initializeLed() {
    *ddrx_ |= (1 << positivePin_) | (1 << negativePin_);
}

void LED::turnRed() {
    *portx_ |= (1 << positivePin_);
    *portx_ &= ~(1 << negativePin_);
 }

void LED::turnGreen() {
    *portx_ |= (1 << negativePin_);
    *portx_ &= ~(1 << positivePin_);
 }

 void LED::turnAmber(uint16_t timeConditionMs) {
	
    while (timeConditionMs > 0 ) {
        turnRed();
        _delay_ms(DELAY_MS_RED);
        turnGreen();
        _delay_ms(DELAY_MS_GREEN);
        timeConditionMs -= TIME_CONDITON_MS;
    }
 }

void LED::turnOff() {
    *portx_ &= ~((1 << positivePin_)| (1 << negativePin_));
}


void LED::blinkGreen4Hz(){
    for (int i = 0; i < FOUR_HZ_REPETITON ; i++){
        turnGreen();
        _delay_ms(FOUR_HZ_DELAY);
        turnOff();
        _delay_ms(FOUR_HZ_DELAY);
    }
}

void LED::blinkRed4Hz(){
    for (int i = 0; i < FOUR_HZ_REPETITON; i++){
        turnRed();
        _delay_ms(FOUR_HZ_DELAY);
        turnOff();
        _delay_ms(FOUR_HZ_DELAY);
    }
}

void LED::blinkRedGreen2Hz(){
    while (true) {
        turnRed();
        _delay_ms(TWO_HZ_DELAY);
        turnGreen();
        _delay_ms(TWO_HZ_DELAY);
    }
}