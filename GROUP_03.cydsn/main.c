/** 
*========================================
*      \main.c
* 
*      Main source for the project, it declares variables, initializes the peripherals and calls the error routine if necessary.
* 
*      \Authors: Oswaldo Parra, Michele Civitavecchia
*      \Date: 09/04/2021
* ========================================
*/
#include "project.h"
#include "timeout.h"
#include"Uart_Routine.h"
#include"RGBLedDriver.h"
#define START 160
#define HEAD 0
#define RED 1
#define GREEN 2
#define BLU 3
#define TAIL 4
#define TIMEOUTSELECTION 5
#define ERROR 6
uint8_t timer_compare=5;                                //timeout time for abort transmission (in seconds)
uint8_t count=0;                                        //variable that keeps track of time(in seconds)
uint8_t header,tail, timer_compare_temp;                //we assign to header and tail their byte received from the terminal, timer_compare_temp is used to not change the real variable used for timeout until we check the tail is correct
color color_led;                                        //color to be created with RGB led, struct defined in RGBLedDriver.h
uint8_t status;                                         // flag used to deal with states in the uart transmission protocols
const color white={255,255,255};                        //some colors to be used --Start
const color black={0,0,0};
const color red={255,0,0};
const color green={0,255,0};
const color blu={0,0,255};                              //some colors to be used --End

int main(void){
    CyGlobalIntEnable;                                  //Enable global interrupts.
    Timeout_Interrupt_StartEx(CustomTimerISR);          // enable the interrupt for the timer
    UART_Start();                                       // initialize the UART preripheral
    UART_Interrupt_StartEx(Custom_UART_RX_ISR);         // enable the interrupt for the UART
    RGBLed_Start();                                     // we enable the PWMs for the color creation
    for(;;){
        if (status==ERROR){                             //if an error occurs, we use the errore routine implemented in Uart_Routine.c
            UART_ErrorManagement();
        }
    else                                                //if everything works as expected, the main does nothing but initialize the peripherals and call the error management
        ;
    }
}


/* [] END OF FILE */
