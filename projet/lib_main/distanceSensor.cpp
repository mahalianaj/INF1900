#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "distanceSensor.h"
#include "can.h"
#include "uart.h"
#include <stdio.h>
using namespace std;

bool DistanceSensor::isObstacle1()
{
    _delay_ms(OBSTACLE_DELAY);
    can sensor;
    uint16_t sum = 0;
    for (uint8_t i = 0; i < TEN; i++){
        sum += sensor.lecture(PA2) >> TWO_BITSHIFT;
    }
    sum /= TEN;
    return (sum >= MAX ); 
}


void DistanceSensor::readValue(){
    Uart uart;
    can can;
    DDRA &= ~(1 << PA2);
    char stringData[6];
    while (true)
    {
        _delay_ms(OBSTACLE_DELAY);
        uint16_t analogValue = can.lecture(PA2) >> TWO_BITSHIFT;

        snprintf(stringData, 6, "%u", analogValue);
        uart.transmitString("valeur : ");
        uart.transmitString(stringData);
           
        uart.transmitString(" \n ");
    }
}
   