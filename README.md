
# ELEC5620M Written Assignment Repository - Stopwatch 

This repository contains code for Digital Stopwatch. This was designed to fulfil the requirements for Assignment 2.

<h3> Digital Stopwatch using ARM A9 Private Timer and 7-Segment Display. </h3>

Files inside the repository

| File | Purpose |
| ---  | --- |
| 'main.c'                  | Main Program Function , Performs the functionality of stopwatch.|
| 'Initialisations.c'           | Function used to set all the values of 7-segment display to zero.|
| 'SevenSeg.c'                   | Driver Function for Seven Segment Display. |
| 'PrivateTimer.c'               | Driver Function for ARM A9 Private Timer.|
| 'HPS_IRQ.c'                    | Driver function to handle IRQ Interrupts. |

Functionality:

The objective of this assignment is to design a digital stopwatch using ARM A9 private timer and 7-segment displays and debug the same using DE1-SoC board. DE1-SoC is hardware design platform with Cyclone V SoC with ARM A9 dual core processor.

The stopwatch has the following specifications.

1.	The stopwatch can be started using Button 1 on the DE1-SoC board.
2.	The stopwatch can be stopped using Button 2 on the DE1-SoC board. When the stopwatch is stopped and the button is pressed again, the stopwatch resets itself.
3.	The stopwatch displays time in MM : SS : FF format where MM denotes minutes, SS denotes seconds and FF denotes hundredths of seconds. When the stopwatch has been running for more than an hour, the stopwatch displays time in HH : MM : SS format where HH denotes hour, MM denotes minutes and SS denotes seconds.
4.	The stopwatch has split timer functionality. When Button 3 on the DE1-SoC board is pressed, the time during the button press is recorded but the stopwatch continues to run. When the stopwatch is stopped, the recorded time can be viewed by pressing Button 3 on the board. The split timer gets reset when the stopwatch is reset.
5.	Button 4 turns on/off the stopwatch.
6.	Display animations on the stopwatch when the stopwatch has counted a minute.

