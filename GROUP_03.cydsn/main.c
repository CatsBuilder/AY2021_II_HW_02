/* ========================================
 *
 * 
 * 
 * 
 *
 * 
 * 
 *
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
#define ERRORE 6
uint8_t timer_compare=5;  //tempo di timeout (in secondi)
uint8_t stop_uart=0;    //flag di timeout per l'uart, dato che non so come si comporterebbe l'uart se diamo il comando di stop che trovi nella routine in "timeout.c", nel caso abbiamo questa flag da usare
uint8_t count=0;    //tempo di conteggio per timeout (in secondi)
uint8_t header,tail, timer_compare_temp,stop, info;
uint8_t rgb[3]={0};
color color_led;
int main(void){
    CyGlobalIntEnable; /* Enable global interrupts. */
    //Timeout_Interrupt_Enable();
    Timeout_Interrupt_StartEx(CustomTimerISR);
    UART_Start();
    UART_Interrupt_StartEx(Custom_UART_RX_ISR);
    RGBLed_Start();
    //Timeout_Timer_Init();
    //Timeout_Timer_Enable();
    //Timeout_Timer_Start() usa questa funzione all'interno della routine del uart per iniziare a contare con il timer
    //Timeout_Timer_Stop() per fermarlo quando deve smettere di contare, ricordati di mettere count di nuovo a zero per il conteggio successivo
    //quando arriva l'header che rappresenta "cambio tempo timeout basta che assegni il valore immesso a timer_compare,di default è 5

    for(;;){
        if (info==ERRORE){
            Timeout_Timer_Stop();
            count=0;//Timer Reset
            //UART_Start();
            PWM_R_WriteCompare(255);//In caso di errore viene il led diventa rosso utilizzato per debugging
            PWM_BG_WriteCompare1(0);
            PWM_BG_WriteCompare2(0);
            header=0;
            tail=0;
            info=HEAD;
        }
    else 
        ;
    }
}


/* [] END OF FILE */
