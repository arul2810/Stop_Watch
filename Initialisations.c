/*
 * Initialisations.c - Stop Watch
 *
 * This Programs declares all the variables and certain functions to be used in the Main Program
 *
 * This separate header is created to make understanding the need for declaration of variables more easier
 *
 *  Created on: Mar 26, 2021
 *      Author: Arul Prakash Samathuvamani | el20a2ps@leeds.ac.uk
 */


// function used to set all the values of 7-segment display to zero.

#include "SevenSeg.h"

void seven_seg_initialise () {

	// sets all the values in seven segment display to 1

	sevenseg_single(0,0);
	sevenseg_single(1,0);
	sevenseg_single(2,0);
	sevenseg_single(3,0);
	sevenseg_single(4,0);
	sevenseg_single(5,0);

}

// function used to turn of the display, and blink when counter counts a minute. Turns of the 7-segment display.

void display_blink () {

	// turns off the seven segment display.

	sevenseg_single(0,10);
	sevenseg_single(1,10);
	sevenseg_single(2,10);
	sevenseg_single(3,10);
	sevenseg_single(4,10);
	sevenseg_single(5,10);


}
