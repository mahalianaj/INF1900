/*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*timer.h
*
*Description: This class allows the use of the ATmega324PA's 16-bit Timer 1
* in Clear Timer on Compare (CTC) mode with an ISR interrupt so that the timer
* has an effect on the code in which it is used. This class does not configure
* outputs OC1A and OC1B, so pins PD4 and PD5 remain available for other functions.
*/

#ifndef H_TIMER
#define H_TIMER

#include <avr/io.h>

//only timer 1 in mode ctc
constexpr uint16_t PRESCALER_VALUE = 1024;
constexpr uint16_t MS_TO_S = 1000;

class Timer {
    public:

    Timer();
    void startTimer(uint16_t duration);

};

#endif