/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "timeout.h"
#include"GetKey.h"
#include"Int.h"
#include"RGBLedDriver.h"
#include"SelectColor.h"
#define START 160

uint8_t timer_compare=5;  //tempo di timeout (in secondi)
uint8_t stop_uart=0;    //flag di timeout per l'uart, dato che non so come si comporterebbe l'uart se diamo il comando di stop che trovi nella routine in "timeout.c", nel caso abbiamo questa flag da usare
uint8_t count=0;    //tempo di conteggio per timeout (in secondi)
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    Timeout_Interrupt_StartEx(CustomTimerISR);
     UART_Start();
    UART_Interrupt_StartEx(Custom_UART_RX_ISR);
    RGBLed_Start();
    
    //Timeout_Timer_Start() usa questa funzione all'interno della routine del uart per iniziare a contare con il timer
    //Timeout_Timer_Stop() per fermarlo quando deve smettere di contare, ricordati di mettere count di nuovo a zero per il conteggio successivo
    //quando arriva l'header che rappresenta "cambio tempo timeout basta che assegni il valore immesso a timer_compare,di default è 5

    for(;;)
    {
        if(Temp==START){ /*Set RGB Color when A0 recived*/
        SelectColor();
        }
    }
}

/* [] END OF FILE */
