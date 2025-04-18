# 🤖 Projet Intégrateur 1 – INF1900 – Polytechnique Montréal
### Équipe 6275

## 👥 Team members

- Lysandra Kingne Welapenou
- Mahaliana Jeansoulé
- Sara Lynn Benkreira
- Farah Sherif 


## 📌 Project presentation
This project is the final project of the class INF1900 at Polytechnique Montréal.


## 🎯 Objective
The objective is to program a robot that has a **ATmega324PA** microcontroller to follow a circuit that contains multiple constraints : 

- Presence of obstacles
- Specific behaviors in certain parts of the circuit
- Sound emissions
- Reactions to presses of buttons
- Two different possible starting points
- Obligation to end the track where it started

This is what the circuit looks like :
![Circuit](./circuit.png) 

All the documents and explications on this project are available in the official website of the course **INF1900**.



## 🧠 Our approach

We split this project into **3 main parts** :
- `House`
- `BC`
- `Grid`

Each part was implemented in **their own class**, then was integrated into the `main` taking into account the two different possible starting points.

### 🔧 Debugging methods
- Use of `make debug` and `DEBUG_PRINT()`
- Tests separated in each module
- Verifications with LEDs in key sections of the code 
- Final assembly of all the parts once all the separate modules worked on their own 



## ⚙️ State Machines

## 🧠 State Machine – Grid section

| **Current State** | **Input / Condition**                | **Next State**   | **Output / Action**                                                            |
|-------------------|--------------------------------------|------------------|---------------------------------------------------------------------------------|
| INIT              | `!robot.distanceSensor.isObstacle1()` | CENTER_FREE      | -                                                                               |
| INIT              | otherwise (obstacle detected)         | CHECK_SCAN       | -                                                                               |
| CENTER_FREE       | -                                     | CHECK_SCAN_2     | `centerFree()`                                                                 |
| CHECK_SCAN        | `robot.distanceSensor.isObstacle1()`  | LEFT_FREE        | `checkGrid()` → obstacle detected                                              |
| CHECK_SCAN        | otherwise                             | RIGHT_FREE       | `checkGrid()` → no obstacle                                                    |
| RIGHT_FREE        | -                                     | CHECK_SCAN_2     | `rightFree()`                                                                  |
| LEFT_FREE         | -                                     | CHECK_SCAN_2     | `leftFree()` (specific navigation movement)                                    |
| CENTER_FREE_2     | `robot.distanceSensor.isObstacle1()`  | END              | `centerFree2()`                                                                |
| CHECK_SCAN_2      | `robot.distanceSensor.isObstacle1()`  | LEFT_FREE_2      | `checkGrid2()`                                                                 |
| CHECK_SCAN_2      | otherwise                             | RIGHT_FREE_2     | `checkGrid2()`                                                                 |
| LEFT_FREE_2       | -                                     | END              | `leftFree2()`                                                                  |
| RIGHT_FREE_2      | -                                     | END              | `rightFree2()`                                                                 |
| END               | -                                     | TERM             | Robot positions itself to either continue or finish its path                   |


## 📁 File and folder structure

This project is organised in different folders that join all the files necessary for its running.

### 📁 `projet/`
#### 📁 `app/`
- `app.cpp`
- `Makefile`

#### 📁 `lib_main/`
- `Makefile`
- `bc.h`
- `bc.cpp`
- `button.h`
- `button.cpp`
- `can.h`
- `can.cpp`
- `debug.h`
- `distanceSensor.h`
- `distanceSensor.cpp`
- `gridSelection.h`
- `gridSelection.cpp`
- `houseSequence.h`
- `houseSequence.cpp`
- `led.h`
- `led.cpp`
- `lineMaker.h`
- `lineMaker.cpp`
- `memory.h`
- `memory.cpp`
- `motor.h`
- `motor.cpp`
- `robot.h`
- `robot.cpp`
- `song.h`
- `song.cpp`
- `timer.h`
- `timer.cpp`
- `uart.h`
- `uart.cpp`



## 🔧 How to get the robot ready to roll 

1. **Supply the robot in electricity**  
   Insert :
   - 6 AA 1.5V batteries
   - 1 9V battery


2. **Compilation**  
   In the folder `lib_main` :
    make clean
    make

   Then in the folder `app` :
    make clean
    make install

3. **Disconnect the robot to start the course**


## 🔌 How to connect the components


| Components               | Connexions                                                                       |
|--------------------------|----------------------------------------------------------------------------------|
| **LED**                  | PA0 (positive), PA1 (negative)                                                   |
| **Line follower**        | VCC & GND on PORTD  <br> D1 → PA3, D2 → PA4, D3 → PA5, D4 → PA6, D5 → PA7        |
| **Button (breadboard)**  | VCC & GND on PORTA  <br> Input → PB0                                             |
| **Piézoélectric**        | PB2 and PB3                                                                      |
| **Right motor**          | Enable → PD7, Direction → PD5                                                    |
| **Left motor**           | Enable → PD6, Direction → PD4                                                    |


## 🖼️ Picture of the robot

Here is a picture of the robot **with connections** and **and without connections** next to each other :

![Robot branché](./robotImage.jpg) 