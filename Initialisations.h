/*
 * Initialisations.h - Stop Watch
 *
 * This Programs declares all the variables and certain functions to be used in the Main Program
 *
 * This separate header is created to make understanding the need for declaration of variables more easier
 *
 *  Created on: Mar 26, 2021
 *      Author: Arul Prakash Samathuvamani | el20a2ps@leeds.ac.uk
 */

#ifndef INITIALISATIONS_H_
#define INITIALISATIONS_H_


// Declaration of Key_ptr pointer that points to key_press address. 4-bit address, changes accordingly to key press.

volatile unsigned int *key_ptr = (unsigned int *) 0xFF200050;

// Function variables used to indentify the pressed key.

unsigned int key_last_state = 0; // Last key press
unsigned int key_pressed; // denotes what is the currently pressed key


// Counter Function Variables

int milli_seconds = 0 ; // denotes milli_seconds
int seconds       = 0 ; // denotes seconds
int minutes       = 0 ; // denotes minutes
int hour 		  = 0 ; // denotes hour


int flag   = 1; // Used to denote if the system is counting in hours or minutes. If counting in minutes, the flag value is 1, if hour flag is 0

int splits = 0; // Variable used for split timer function. Used to count the number of times split timer button is pressed.

// Split timer variables. Used to store the time when split timer button is pressed. Can store only 20 split times.

int split_ms[20]; // to store milli-seconds
int split_s[20]; // to store seconds
int split_m[20]; // to store minutes
int split_hr[20]; // to store hour

// Variables used to print the split timer values

int index; // denotes current array index in split timer array
int loop_variable; // variable used inside for loop


int mode = 1; // Used for interrupts. When mode is 1, system is ON and functions. When mode is 0, then system is TURNED OFF.

void seven_seg_initialise (void); // function used to set all the values of 7-segment display to zero.

void display_blink (void); // function used to turn of the display, and blink when counter counts a minute. Turns of the 7-segment display.


#endif /* INITIALISATIONS_H_ */
