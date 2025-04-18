/*
*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*song.h
*
*Description: Description: The Song class allows the piezo to operate. Initializing an object of this class
* initializes all the ports to which the piezo should be connected (PB2-PB3), as well as the timer 0
* of the ATmega324PA in CTC mode. There is a function which converts the respective note numbers into MIDI frequencies,
* and another function which allows a note to be played continuously.
*/

#ifndef H_SING
#define H_SING

#include <avr/io.h>

constexpr uint32_t FREQUENCY_CPU = 8000000;

class Song {
public:
    Song();
    void play(uint8_t note);
    double midiConvertion(uint8_t note);
    void stop();
    void happyBirtday();
    void playMarioTheme();
    void newsong();
};

#endif