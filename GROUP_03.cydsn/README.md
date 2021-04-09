09/apr/2021
	Second Assignment
	the project implements 3 headers:
		RGBLedDriver.h
		timeout.h	
		Uart_Routine.h
	and 4 executables:
		main.c 
		RGBLedDriver.c
		timeout.c
		Uart_Routine.c
The execution of the program is the expected one and no primary bug have been found on the code.
Whent the micro starts the led is black, if the right header is transmitted from a terminal, a routine is triggered and a timeout is set (default 5s, settable by the header 161).
If the header received is 160, the color selection routine is triggered and the protocol waits up to <timeout value> for each color in the right sequence (red->green->blu), it then waits again <timeout value> for the tail that has to be 192 other wise an error is triggered and the system is taken back to the initial waiting phase until a new expected header is received.
Any header different from 160 and 161 will result in an error. 
For detailed information about the code and its execution please refer to the code comments and, in particular, to the graph in Uart_Routine.c which explains the logic behind the transmission.
for further informations write to oswaldo.parra@mail.polimi.it or michele.civitavecchia@mail.polimi.it