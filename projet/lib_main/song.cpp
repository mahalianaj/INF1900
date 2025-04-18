#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h> 
#include "song.h"

Song::Song(){

    TCCR0A &=~(1 << WGM00); //mode ctc
    TCCR0A |= (1 << WGM01);
    TCCR0B &= ~(1 << WGM02);

    DDRB |= (1 << PB3)| (1 << PB2); 
    PORTB |= (1 << PB3);
    PORTB &= ~(1 << PB2);

    TCCR0B |= (1 << CS02); //prescaler 256
}

double Song::midiConvertion(uint8_t note){
    return 440.0 * pow(2.0, (note - 69) / 12.0);
}

void Song::play(uint8_t note) {
    double frequency = midiConvertion(note); 

    TCCR0A |= (1<< COM0A0);            
    TCCR0A &= ~(1<< COM0A1);
    OCR0A = ((FREQUENCY_CPU) / (2 * 256 * frequency)) - 1;  
}


void Song::stop(){
   TCCR0A &= ~(1<<COM0A0); 
   TCCR0A &= ~(1<<COM0A1);
}

void Song::happyBirtday(){

    // Première phrase: "Joyeux anniversaire"
    play(60);  // C4
    _delay_ms(400); // 400 ms

    play(60);  // C4
    _delay_ms(400); // 400 ms

    play(62);  // D4
    _delay_ms(800); // 800 ms

    play(60);  // C4
    _delay_ms(800); // 800 ms

    play(65);  // F4
    _delay_ms(800); // 800 ms

    play(64);  // E4
    _delay_ms(1600); // 1600 ms (longue pause)

    stop();
    _delay_ms(600);

    // Deuxième phrase: "Joyeux anniversaire"
    play(60);  // C4
    _delay_ms(400); // 400 ms

    play(60);  // C4
    _delay_ms(400); // 400 ms

    play(62);  // D4
    _delay_ms(800); // 800 ms

    play(60);  // C4
    _delay_ms(800); // 800 ms

    play(67);  // G4
    _delay_ms(800); // 800 ms

    play(65);  // F4
    _delay_ms(1600); // 1600 ms (longue pause)

    stop();
    _delay_ms(600);

    // Troisième phrase: "Joyeux anniversaire"
    play(60);  // C4
    _delay_ms(400); // 400 ms

    play(60);  // C4
    _delay_ms(400); // 400 ms

    play(60);  // C4
    _delay_ms(800); // 800 ms

    play(71);  // B4
    _delay_ms(800); // 800 ms

    play(69);  // A4
    _delay_ms(800); // 800 ms

    play(65);  // F4
    _delay_ms(1600); // 1600 ms

    stop();
    _delay_ms(600);

    // Quatrième phrase: "Joyeux anniversaire"
    play(72);  // C5
    _delay_ms(400); // 400 ms

    play(72);  // C5
    _delay_ms(400); // 400 ms

    play(71);  // B4
    _delay_ms(800); // 800 ms

    play(67);  // G4
    _delay_ms(800); // 800 ms

    play(69);  // A4
    _delay_ms(1600); // 1600 ms (longue pause)

    stop();
    _delay_ms(600);

    // Fin de la musique

}

void Song::playMarioTheme(){
    // Première phrase: "C E G"
    play(60);  // C2 (C)
    _delay_ms(120); // 0.12s

    play(64);  // E2 (E)
    _delay_ms(120); // 0.12s

    play(67);  // G2 (G)
    _delay_ms(120); // 0.12s

    // Deuxième phrase: "C E"
    play(60);  // C3 (C)
    _delay_ms(120); // 0.12s

    play(64);  // E3 (E)
    _delay_ms(120); // 0.12s

    // Troisième phrase: "G E"
    play(67);  // G3 (G)
    _delay_ms(360); // 0.36s

    play(64);  // E3 (E)
    _delay_ms(240); // 0.24s

    // Quatrième phrase: "C DE GA"
    play(60);  // C2 (C)
    _delay_ms(120); // 0.12s

    play(62);  // D2 (DE)
    _delay_ms(120); // 0.12s

    play(68);  // A2 (GA)
    _delay_ms(120); // 0.12s

    // Cinquième phrase: "C DE"
    play(60);  // C3 (C)
    _delay_ms(120); // 0.12s

    play(62);  // D3 (DE)
    _delay_ms(120); // 0.12s

    // Sixième phrase: "GA DE"
    play(68);  // A3 (GA)
    _delay_ms(360); // 0.36s

    play(62);  // D3 (DE)
    _delay_ms(240); // 0.24s

    // Septième phrase: "D F AB"
    play(62);  // D2 (D)
    _delay_ms(120); // 0.12s

    play(65);  // F2 (F)
    _delay_ms(120); // 0.12s

    play(73);  // AB3 (AB)
    _delay_ms(120); // 0.12s

    // Huitième phrase: "D F"
    play(62);  // D3 (D)
    _delay_ms(120); // 0.12s

    play(65);  // F3 (F)
    _delay_ms(120); // 0.12s

    // Neuvième phrase: "AB"
    play(73);  // AB4 (AB)
    _delay_ms(360); // 0.36s

    // Dixième phrase: "AB AB AB"
    play(73);  // AB4 (AB)
    _delay_ms(120); // 0.12s

    play(73);  // AB4 (AB)
    _delay_ms(120); // 0.12s

    play(73);  // AB4 (AB)
    _delay_ms(120); // 0.12s

    // Dernière phrase: "C"
    play(60);  // C5 (C)
    _delay_ms(1440); // 1.44s

    stop();

}

void Song::newsong(){
// Do – Do – Do – Ré – Mi – Ré – Do – Mi – Ré – Ré – Do – Do – Do – Do – Ré – Mi – Ré – Do – Mi – Ré – Ré – Do – Ré – Ré – Ré – Ré – La – La – Ré – Do – Si – La – Sol – Do – Do – Do – Ré – Mi – Ré – Do – Mi – Ré – Ré – Do.

play(60);  // Do
_delay_ms(400); // 0.4s

play(60);  // Do
_delay_ms(400); // 0.4s

play(60);  // Do
_delay_ms(400); // 0.4s

play(62);  // Ré
_delay_ms(400); // 0.4s

play(64);  // Mi
_delay_ms(800); // 0.4s

play(62);  // Ré
_delay_ms(800); // 0.4s

play(60);  // Do
_delay_ms(400); // 0.4s

play(64);  // Mi
_delay_ms(400); // 0.4s

play(62);  // Ré
_delay_ms(400); // 0.4s

play(62);  // Ré
_delay_ms(400); // 0.4s

play(60);  // Do
_delay_ms(800); // 0.4s


play(60);  // Do
_delay_ms(400); // 0.4s

play(60);  // Do
_delay_ms(400); // 0.4s

play(60);  // Do
_delay_ms(400); // 0.4s

play(62);  // Ré
_delay_ms(400); // 0.4s

play(64);  // Mi
_delay_ms(800); // 0.4s

play(62);  // Ré
_delay_ms(800); // 0.4s

play(60);  // Do
_delay_ms(400); // 0.4s

play(64);  // Mi
_delay_ms(400); // 0.4s

play(62);  // Ré
_delay_ms(400); // 0.4s

play(62);  // Ré
_delay_ms(400); // 0.4s

play(60);  // Do
_delay_ms(800); // 0.4s

}