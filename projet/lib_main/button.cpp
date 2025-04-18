#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>

#include "button.h"


Button::Button(volatile uint8_t* pinAdresse, volatile uint8_t* ddrx, uint8_t pin, uint8_t active, Mode mode){
    DDR_ = ddrx;
    pin_ = pin;
    active_ = active;
    pinAdresse_ = pinAdresse;
    *DDR_ &= ~(1 << pin_); 
}


void Button::initializeAE() {
    cli(); 
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    EICRA &= ~(1 << ISC01);
    sei();
}

void Button::initializeRE() {
    cli(); 
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    EICRA |= (1 << ISC01);
    sei();
}

void Button::initializeFE() {
    cli(); 
    EIMSK |= (1 << INT0);
    EICRA &= ~(1 << ISC00);
    EICRA |= (1 << ISC01);
    sei();
}

bool Button::readButton() {    
    if (active_) {
       
        if (*pinAdresse_ & (1 << pin_)) {
            _delay_ms(Button::DELAY_READ_BUTTON); 

            return (*pinAdresse_ & (1 << pin_));  
        }
    } else {
        
        if (!(*pinAdresse_ & (1 << pin_))) {
            _delay_ms(Button::DELAY_READ_BUTTON); 

            return (!(*pinAdresse_ & (1 << pin_)));  
        }
    }
    return false;
}