/*
 *  Stop Watch Main Function
 *
 *
 *  Created on: Mar 23, 2021
 *      Author: Arul Prakash Samathuvamani | Based on Driver in Unit 1 Examples
 */

#include "SevenSeg.h"
#include "HPS_Watchdog.h"
#include "PrivateTimer.h"
#include "HPS_IRQ.h"
#include "Initialisations.h"

// set private timer interrupt to private timer interrupt base address
volatile unsigned int *private_timer_interrupt_value = (unsigned int *) 0xFFFEC60C;

// set interrupt timer pointer to interrupt timer base address
volatile unsigned int *interrupt_timer_ptr           = (unsigned int *)0xFFC08000;



// Function used to count minutes i.e hour is zero | MM : SS : MS MS

void time_counter_no_hour () {


	// when timer interrupt is high,
	while( ( *private_timer_interrupt_value & 0x1 )  ) {

		reset_interrupt(); // reset the interrupt

		milli_seconds = milli_seconds + 1; // increment milliseconds

		if(milli_seconds < 100 ){

			sevenseg_double(0,milli_seconds); // display the updated milliseconds in display

		}else if(seconds < 59){ // when milliseconds reaches 100

			if( ((seconds == 60) || (seconds == 2) )&& (minutes > 0)){ // when minute is counted, blink twice
				display_blink(); // turn off the display for 1 second
				milli_seconds = 0; // reset milliseconds
				seconds = seconds + 1; // increment seconds
			}else{
				milli_seconds = 0; // reset milliseconds
				seconds = seconds + 1; // increment seconds
				sevenseg_double(2,seconds); // display the updated seconds
				sevenseg_double(4,minutes); // display the updated minutes
			}

		}else if(minutes < 59) { // when the counter is less than an hour, and minute is up


			display_blink(); // blink for one second
			seconds = 0; // reset seconds
			milli_seconds = 0; // reset milliseconds
			minutes = minutes + 1; // increment minute
			//sevenseg_double(4,minutes);

		}else{ // else if counter is running for more than an hour

			flag = 0; // set display to HH : MM : SS
			hour = hour + 1; // increment hour for first time
			minutes = 0; // reset minutes
			seconds = 0; // reset seconds
			milli_seconds = 0; // reset milli seconds
			display_blink(); // blink display for a second
			//sevenseg_double(4,hour);
			//sevenseg_double(2,minutes);
			intialise_timer ( 225000000 ); // reset time load value to count for one second

		}

	}

}

// function used to count hour | HH : MM : SS

void time_counter_hour() {

// run the loop when the A9 timer interrupt is high
while( ( *private_timer_interrupt_value & 0x1 )  ) {

						reset_interrupt(); // reset the interrupt

						if( seconds < 59){ // when counter is less than 59 seconds

							if( seconds ==2 || seconds == 60){
								display_blink(); // turn off the display for 1 second
								seconds = seconds + 1; // increment second
							}else{
								seconds = seconds + 1; // increment second
								sevenseg_double(0,seconds); // display updated second
								sevenseg_double(2,minutes); // display updated minutes
								sevenseg_double(4,hour); // display updated hour
							}


						}else if(minutes < 59) { // when the counter is less than 59 minutes

							display_blink(); // turn off the display for 1 second
							seconds = 0; // reset second
							minutes = minutes + 1; // increment minute
							//sevenseg_double(2,minutes);

						}else if (hour < 99 ){ // when hour is less than 99

							display_blink(); // turn off display for one minute
							minutes = 0; // reset minute
							seconds = 0; // reset seconds
							hour = hour + 1; // increment hour
							//sevenseg_double(4,hour);
							//sevenseg_double(2,minutes);

						}else if(hour > 99){ // if hour is more than 99, reset the timer

							minutes = 0; //reset minutes
							hour    = 0; // reset hour
							seconds = 0; //reset seconds
							milli_seconds = 0; // reset milliseconds
							flag = 1; // set the timer to MM : SS : MS MS mode
							intialise_timer ( 2250000 ); // load the timer to count 1 milli second

						}

					}

		HPS_ResetWatchdog(); // reset watchdog

}



unsigned int getPressedKeys () { // To find which key is pressed


    unsigned int key_current_state = *key_ptr; // find what key is pressed

    if( key_current_state != key_last_state){ // if the pressed key is different than previously pressed key

		key_last_state = key_current_state;
		key_pressed = key_current_state; // set the key_pressed to currently pressed key
	}else{
		key_pressed = 0; // if nothing is pressed, set the value to zero.
	}

    return key_pressed;

}

// Function to capture split timer when button 2 is pressed

void split_timer_capture (){

	SPLITS : if(splits < 20){ // if less than 20 splits is captured

		split_ms[splits] = milli_seconds; // capture milliseconds
		split_s[splits]  = seconds;  // capture seconds
		split_m[splits]  = minutes; //capture minutes
		split_hr[splits] = hour; //capture hour
		splits = splits + 1; // increment number of splits captured

	}else{

		splits = 0; // reset the splits index to zero to count in FIFO way
		goto SPLITS;
	}

}

// Function used to display the captured split times

void split_timer_display() {


	HPS_ResetWatchdog(); // Reset the watchdog

	if(flag){ // if in MM : SS : MS MS mode

		sevenseg_double( 0, split_ms[index]); // display the captured milliseconds
		sevenseg_double(2, split_s[index]); // display the captured seconds
		sevenseg_double(4,split_m[index]); // display the captured minute

	}else{ // if in HH : MM : SS mode

		sevenseg_double( 0, split_s[index]); // display captured second
		sevenseg_double(2, split_m[index]); // display captured minute
		sevenseg_double(4,split_hr[index]); // displayu the captured hour

	}

}

// reset the captured split timer data
void flush_split_data(){

	index  = 0; // reset index
	splits = 0; // reset the number of captured splits

	for( loop_variable = 0 ; loop_variable < 20 ; loop_variable++){ // loop to set all the values to zero

		split_s[loop_variable]  = 0;
		split_ms[loop_variable] = 0;
		split_s[loop_variable]  = 0;
		split_hr[loop_variable] = 0;

	}


}

// Function to reset and set all the values to initial state values

void initialise(){


	seven_seg_initialise (); // set the display to display zero

	intialise_timer ( 2250000 ); // set the load value in A9 private timer to count in milliseconds

	key_pressed = 0; // set the pressed key state to zero

	milli_seconds = 0; // reset milli seconds to zero
	seconds       = 0; // reset the seconds to zero
	hour          = 0; // reset hour to zero
	minutes       = 0; // reset minutes to zero
	flush_split_data(); // call function to reset the split timer values


}

int main(void); // main function declaration


// interrupt function to set the system to sleep or wake up mode

void sleep_function (HPSIRQSource interruptID, bool isInit, void* initParams){

	if(!isInit){

		unsigned int press;

		press = key_ptr[3]; // read push button interrupt register
		key_ptr[3] = press; // set the value again to interrupt register to reset the register

		HPS_ResetWatchdog(); // reset watchdog

		if(mode){ // if interrupt occurs when the system is ON

			mode = 0; // turn off the system
			HPS_ResetWatchdog(); // reset watch dog

		}else{ // if interrupt occurs when system is OFF

			mode = 1; // turn on the system
			interrupt_timer_ptr[2] = 0;
		}
	}

}

// Function not working - Interrupt to put the system to sleep when IDLE for some time

void time_out_sleep(HPSIRQSource interruptID, bool isInit, void* initParams){

	if(!isInit){

		unsigned int timer_reset;

		timer_reset = interrupt_timer_ptr[3];

		mode = 1;
	}

	HPS_ResetWatchdog();
}


// Main function declaration

int main(void) {


	// Reset the system at the start
	initialise();

	// Initialise IRQs

	HPS_IRQ_initialise ( NULL );

	// Configure button 4 to call interrupt

	key_ptr[2] = 0x8;

	// configure timer interrupt - does not work

	interrupt_timer_ptr[2] = 0;
	interrupt_timer_ptr[0] = 100000000;
	interrupt_timer_ptr[2] = 0x03;

	// IRQ interrupt handler for timer
	HPS_IRQ_registerHandler( IRQ_TIMER_L4SP_0, time_out_sleep);

	// Reset watchdog
	HPS_ResetWatchdog();

	// IRQ interrupt handler for push button press
	HPS_IRQ_registerHandler( IRQ_LSC_KEYS, sleep_function);

	// Reset watchdog
	HPS_ResetWatchdog();


	while(1) { // Main Application loop

		interrupt_timer_ptr[2] = 0; // set IRQ timer to OFF

		INITIALISE: if(!mode){ // when the system is put to power down mode

			display_blink(); // turn off the display
			__asm("WFI"); // saving power by putting the processor to sleep

			HPS_ResetWatchdog(); // reset the watchdog

		}else{ // if the system is to be turned on,

			initialise(); // reset the system first
		}

		key_pressed = getPressedKeys (); // check which key is pressed

		HPS_ResetWatchdog(); // reset the watchdog


		if (key_pressed & 0x1){ // start the counter when button 1 is pressed

				while(1){

				key_pressed = getPressedKeys (); // check if other keys are pressed

				if( !(key_pressed & 0x2) && !(key_pressed & 0x4) ){ // if no other key is pressed, continue to count

					if(!mode){
						goto INITIALISE; // Used to turn off the system when Interrupt happens
					}

					if(flag == 1){ // when counter is running in MM : SS : MS MS mode

						time_counter_no_hour (); // goto function that counts M M : S S : MS MS
						HPS_ResetWatchdog(); // reset the watchdog

					}else{ // when the counter is running in HH : MM : SS mdoe

						time_counter_hour(); // goto function that counts HH : MM  : SS
						HPS_ResetWatchdog(); // reset the watchdog

					}
					HPS_ResetWatchdog(); // reset the watchdog



				} else if(key_pressed & 0x4){ // if button 3 is pressed then,

					split_timer_capture (); // goto function that captures the current time

				}else { // else if button 2 is pressed,

					while (1){

					HPS_ResetWatchdog(); // Reset the watchdog

					if(!mode){ // check if the system has been asked to turnoff

						goto INITIALISE; // turn off the system
					}
					key_pressed = getPressedKeys (); // check which key is pressed

					if( key_pressed & 0x1 ) { // if button 1 is pressed,

						break; // break from the loop and start to count again

					}else if(key_pressed & 0x2){ // if button 2 is pressed,

						initialise(); // Reset the system.
						HPS_ResetWatchdog(); // reset the watchdog

					}else if(key_pressed & 0x4){ // if button 3 is pressed, run in loop to display the captured splits

						DISPLAY : if(index < splits){ // check if split has been captured,
							split_timer_display(); // display the split time
							index++ ; // increase the display index by 1

						}else{ // if all the splits has been displayed, loop again to show the splits

							index = 0; // set the index to zero
							goto DISPLAY; // start displaying the splits agani

						}
							HPS_ResetWatchdog(); // reset the watch dog


					}

				}

				}
			}
		}

	}


}
