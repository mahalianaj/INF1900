#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer.h"

Timer::Timer(){}

void Timer::startTimer ( uint16_t duration ) { //ms

    cli();
    TCNT1 = 0; //debut du minuteur
    OCR1A = ((F_CPU / PRESCALER_VALUE) / MS_TO_S) * duration;
    TCCR1A = 0; //CTC
    TCCR1B &= ~(1<<WGM13); //CTC
    TCCR1B |= (1<<WGM12 | 1<<CS12 | 1<<CS10); //CTC and prescaler == 1024
    TCCR1C = 0; //CTC
    TIMSK1 |= (1<<OCIE1A);
    sei();
}