/*
*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*button.h 
*
*Description: The button class manages a button connected to an Atmega324PA or a breadboard. 
* It initializes the registers to configure interrupts and detect button state changes.
* The user can select the port, the active mode (High or Low), and the trigger type
* (Any Edge, Rising Edge, Falling Edge). A method allows reading the button state
* (pressed or released). By default, the class configures the button on PORTD,
* pin PD2, in Any Edge mode and Active High.
*
*/

#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>
#include <avr/interrupt.h>

enum Mode{AE, RE, FE,};

class Button {
public:
    Button(volatile uint8_t* pinAdresse = &PIND, volatile uint8_t* ddrx = &DDRD, uint8_t pin = PD2 , uint8_t active = 1, Mode mode = AE);

    void initializeAE();
    void initializeRE();
    void initializeFE();

    bool readButton();

    constexpr static uint8_t DELAY_READ_BUTTON = 10;

private:
    volatile uint8_t* pinAdresse_;
    volatile uint8_t* DDR_;
    uint8_t pin_;
    uint8_t active_;

};

#endif