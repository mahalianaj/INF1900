/*
*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*houseSequence.h
*
*Description: The houseSequence class defines the sequence of actions for the robot to take in order to navigate 
* the "house" section of the circuit. The various functions allow for the adaptable movement of the
* robot through detection of distance and lines, as well as making use of the appropriate movement
* speeds and delays. The Start() function is the only one the user needs to call to utilize this class,
* the rest being automatically triggered in according circumstances.
*/

#ifndef HOUSESEQUENCE_H
#define HOUSESEQUENCE_H
       


class HouseSequence {
    public:
    void Start();
    void HPathFree();
    void HPathObstacle();
    void Exit();
    constexpr static uint16_t DELAY_100 = 100;
    constexpr static uint16_t MOVE_SPEED = 60;
    constexpr static uint16_t DELAY_IN_EXIT = 750;
    constexpr static uint16_t DELAY_IN_H_PATH_FREE = 250;
    constexpr static uint16_t DELAY_TURN_RIGHT = 500;
    constexpr static uint16_t MOVE_DELAY_AFTER_CENTERED_1 = 7100;
    constexpr static uint16_t MOVE_DELAY_AFTER_CENTERED_2 = 1800;
    constexpr static uint16_t DELAY_AFTER_MOVE_FORWARD = 900;
    constexpr static uint16_t TURN_OR_MOVE_DELAY = 250;
};

#endif