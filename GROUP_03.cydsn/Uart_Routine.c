/**
*================================================
*   \Uart_Routine.c
*
*   Source for the UART management, it implements the interrupt routine for transmission and an error routine that resets the transmission
*
*   \Author: Oswaldo Parra, Michele Civitavecchia
*   \Date: 08/06/2021
*================================================
*/

#include "RGBLedDriver.h"
#include "Uart_Routine.h"
#include "UART.h"
#include "stdio.h"
#include "cytypes.h"
#include "Timeout_Timer.h"
#include "project.h"

#define HEAD 0
#define RED 1
#define GREEN 2
#define BLU 3
#define TAIL 4
#define TIMEOUTSELECTION 5
#define ERROR 6

extern uint8_t header,timer_compare,tail, timer_compare_temp,count, status;
extern color color_led, white ,black, red, green, blu;
uint8_t i;

/*=====================================================

        Brief graph of logic UART path in Custom_UART_RX_ISR function.
                        Start      
    ---------->  Waiting(main.c loop)<---------------
    ^                    |                          ^
    |                    |                          |
    |                    V                          |
    |       A new header has been received          |
    |       |            |              |           |
    |       V            V              V     ErrorManagement
    |  |<-- a0           a1 --->|      else         |
    |  |    |            |      |       |           |
    |  |    V            V      |       |           |
                        new     V       V           |
    |  |<-- red       timeout ------> ERROR-------->|
    |  |    |          value            ^
    |  |    V           |               |
    |  |<-- green       |               |
    |  |    |           |               |   
    |  |    V           V               |
    |  |<-- blu------->tail             |
    |  V                 |              |
    |  -------------------------------> |
    |                    |
    |                    V
    |<--------------------

    In 4 cases an error could be triggered:
                                    1.if the header received is not associated to an operation
                                    2. if a timeout occurs
                                    3.if the tail does not match the one expected
                                    4. the new timeout value is not valid (<1 || >20)
========================================================*/


CY_ISR(Custom_UART_RX_ISR){
    switch (status) {                                           // the routine is a finite state machine where evrey case in the switch is a state
        case HEAD:                                              //the first step is to receive a header, this header contains the information about what it has to be done, 3 branches are created
            header=UART_ReadRxData();                           //read the byte arrived from the terminal and put it in the header variable
            Timeout_Timer_Start();                              //start the timer to keep the time flow under control and give a timeout error if needed
            if(header==0xa1)                                    //an "a1" header will trigger the routine for the timeout time setting 
                status=TIMEOUTSELECTION;
            else if (header==0xa0)                              //an "a0" header will trigger the routine for the color setting, the first primary color to be setted is the red one
                status=RED;
            else if(header==0x76|| header==0x56){               //when we receive the character v, the micro will respond with the line "RGB LED Program $$$"
                UART_PutString("RGB LED Program $$$");
                UART_ClearRxBuffer();                           //buffer refresh 
                Timeout_Timer_Stop();                           //stop the timer, not necessary ti trigger an error, just go back to header waiting
                status=HEAD;
            }
            else                                                //case of error N°1
                status=ERROR; 
            UART_ClearRxBuffer();
            break;
        case TIMEOUTSELECTION:                                  // if the timeout setting has been triggered, go to that state
            count=0;                                            // reset the time passed since the last effective operation
            timer_compare_temp=UART_ReadRxData();               // we put the new time in a temporary variable since the tail could be wrong or the number received could be >20 o <1
            if(timer_compare_temp>=21 || timer_compare_temp<=0) // case of error N°4
                status=ERROR;
            else
                status=TAIL;                                    // go to tail state
            UART_ClearRxBuffer();
            break;
        case RED:                                               //red dose selection
            count=0;
            color_led.red=UART_ReadRxData();                    //assign the first color to the red part in the color struct
            UART_ClearRxBuffer();
            status=GREEN;                                       //go to the next state, green
            break;
        case GREEN:                                             // green dose selection
            count=0;
            color_led.green=UART_ReadRxData();                  //assign the second color to the green part in the color struct
            UART_ClearRxBuffer();
            status=BLU;                                         //go to the next state, blu
            break;
        case BLU:                                               //blu dose selection
            count=0;            
            color_led.blu=UART_ReadRxData();                    //assign the third color to the blu part in the color struct
            UART_ClearRxBuffer();
            status=TAIL;                                        //go to the tail state
            break;
        case TAIL:
            count=0;
            Timeout_Timer_Stop();                               //both routines finish here so the timer is no more necessary
            tail=UART_ReadRxData();                             //assign the tail to its variable
            if (tail==0xc0 && header==0xa1){                    //if both the tail and the header are correct and the header matches the TIMEOUT setting routine
                timer_compare=timer_compare_temp;               //update the effective timeout value 
                status=HEAD;                                    //go back to the first state and wait for the next header byte
            }
            else if (tail==0xc0 && header==0xa0){               //if both the tail and the header are correct and the header matches the COLOR setting routine
                RGBLed_WriteColor(color_led);                   //change the color
                status=HEAD;                                    //go back to the first state and wait for the next header byte
                
            }
            else                                                //if the tail is wrong, trigger an error routine 
                status=ERROR;                                   //case of N°3 error
            UART_ClearRxBuffer();
            break;
            
    }
}


void UART_ErrorManagement(void){
    Timeout_Timer_Stop();                                       //when an error occurs we stop the timer
    count=0;                                                    //Time Reset
                                                                /*          This part is used in debug phase, to see if the error is well processed
                                                                RGBLed_WriteColor(black);   
                                                                for (i=0; i<2; i++){
                                                                    RGBLed_WriteColor(red);
                                                                    CyDelay(200);
                                                                    RGBLed_WriteColor(black);
                                                                    CyDelay(200);
                                                                }
                                                                RGBLed_WriteColor(green);
                                                                CyDelay(500);
                                                                RGBLed_WriteColor(color_led);
                                                                */
    header=0;                                                   //reset the variable head and tail, otherwise it could cause a bug when the tail or head are checked
    tail=0;
    status=HEAD;                                                //go back to head status 
}


/* [] END OF FILE */
