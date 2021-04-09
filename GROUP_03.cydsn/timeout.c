/**
*================================================
*   \timeout.c
*
*   Source file for CustomTimerISR: deals with time flow and sets the state in UART transmission to "ERROR" in case of timeout
*
*   \Authors: Oswaldo Parra, Michele Civitavecchia
*   \Date: 06/04/2021
*================================================
*/

                   
#include "timeout.h"
#include "project.h"

#define HEAD 0
#define ERROR 6

extern uint8_t count;                   //Interrupt given by the timer happens once a second, this variable keeps track of time in seconds
extern uint8_t timer_compare;           //this value is the one set as threshold value for the ERROR stauts, when this threshold is overcome, the transmission is aborted and the system goes back to the "wait" status
extern uint8_t status;                  // flag used to deal with the states of the finite state machine
extern uint8_t header;
extern uint8_t tail;
CY_ISR(CustomTimerISR){
    count++;                           //every second we add 1 to this variable
    Timeout_Timer_ReadStatusRegister();//we clear the register, otherwise the system will be locked a loop of timer interrupts
    if (count>=timer_compare)          //if the timeout threshold is overcome, the system is taken into error state
        status=ERROR;                  //case of error N°2, for error list please refer to the instructions in UART_Routine.c
    else                               //if nothing happens, the interrupt ends without instruction
        ;

}
/* [] END OF FILE */
