#ifndef PUMP_H
#define PUMP_H

#include "../utils/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

enum DRINK_RECIPES { NONE, DRINK1, DRINK2, DRINK3, DRINK4 };

void pump_init(void);
void pump_cleanup(void);
void setupGPIO();   ////exports all pins, set all pins to out, set all pins to low
void* pumpThread(void* arg);

//pump turns on for state == true, pump turns off for state == false
void Primary_Pump(int state);
void Pump1(int state);
void Pump2(int state);
void Pump3(int state);
void Pump4(int state);

//The solenoids are electronic flow valves.
//the primary pump is hooked up to 2 different reservoirs, which reservoir is pumped from can be selected by opening/closing solenoid valves.
//state==true, valve is open. Else valve is closed.
void Solenoid1(int state);
void Solenoid2(int state);
void writeToFile(char* file, char* value);

static void activate(int gpio);
static void deactivate(int gpio);

// Getter and setters for the "currentDrink" state
int pump_getDrink();
void pump_setDrink(int newDrink);

void make_drink(void);

#endif
