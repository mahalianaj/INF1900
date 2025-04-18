/*
*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*distanceSensor.h
*
*Description: The DistanceSensor class uses an analog infrared sensor to detect obstacles in front of the robot. 
* The class provides methods to determine whether an obstacle is present (isObstacle1) and to read
* and transmit sensor values via UART for debugging (readValue).
*/

#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include <avr/io.h>

constexpr uint8_t MAX = 45;
constexpr uint8_t TWO_BITSHIFT = 2;
constexpr uint8_t TEN = 10;
constexpr uint8_t OBSTACLE_DELAY = 20;


class DistanceSensor
{
public:
    bool isObstacle1();
    void readValue();
};

#endif