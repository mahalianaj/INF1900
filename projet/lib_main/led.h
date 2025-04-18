/*
*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*Led.h
*
*Description:  This class allows the management of the ATmega324PA's free LED,
* such as its color (red, amber, green) and state (on or off).
* The class ensures that an LED object can be instantiated and used
* on the defined ports (B0, B1).
*/

#ifndef H_LED
#define H_LED
#include <avr/io.h>

constexpr uint8_t DELAY_MS_RED = 1;
constexpr uint8_t DELAY_MS_GREEN = 1;
constexpr uint8_t TIME_CONDITON_MS = 2;
constexpr uint8_t FOUR_HZ_DELAY = 125;
constexpr uint8_t FOUR_HZ_REPETITON = 8;
constexpr uint8_t TWO_HZ_DELAY = 250;


class LED {
    public:

        LED(volatile uint8_t* portx = &PORTA, volatile uint8_t* ddrx = &DDRA, uint16_t positivePin = PA0, uint16_t negativePin = PA1);

        void initializeLed();
        void turnRed(); 
        void turnGreen();
        void turnAmber(uint16_t timeConditionMs);
        void turnOff();
        void blinkRed4Hz();
        void blinkGreen4Hz();
        void blinkRedGreen2Hz();

    
    private :

        volatile uint8_t* portx_;
        volatile uint8_t* ddrx_;
        uint16_t positivePin_;
        uint16_t negativePin_;

};

#endif




