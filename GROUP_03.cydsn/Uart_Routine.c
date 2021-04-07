
#include "RGBLedDriver.h"
#include "Uart_Routine.h"
#include "UART.h"
#include "stdio.h"
#include "cytypes.h"

extern uint8_t header,red,green,blue;
extern uint8_t timer_compare,tail, timer_compare_temp;
CY_ISR(Custom_UART_RX_ISR){
    while(UART_ReadRxStatus() != UART_RX_STS_FIFO_NOTEMPTY); //attendere che il byte sia disponibile (ridondante)
    header=UART_ReadRxData(); //assegna il valore del byte al header per capire cosa deve fare, imposta timer o seleziona colore
    UART_ClearRxBuffer();
    if (header==161){
        while(UART_ReadRxStatus() != UART_RX_STS_FIFO_NOTEMPTY);
        timer_compare_temp=UART_ReadRxData();
        UART_ClearRxBuffer();
        while(UART_ReadRxStatus() != UART_RX_STS_FIFO_NOTEMPTY);
        tail=UART_ReadRxData();
        UART_ClearRxBuffer();
        if (tail==192)
            timer_compare=timer_compare_temp;
        else
            ;   
    } //quando arriva l'header 161, entra nella routine per cambiare il timer
    else if(header==160){
        
        while(UART_ReadRxStatus() != UART_RX_STS_FIFO_NOTEMPTY);
        red=UART_ReadRxData();
        UART_ClearRxBuffer();
        while(UART_ReadRxStatus() != UART_RX_STS_FIFO_NOTEMPTY);
        green=UART_ReadRxData();
        UART_ClearRxBuffer();
        while(UART_ReadRxStatus() != UART_RX_STS_FIFO_NOTEMPTY);
        blue=UART_ReadRxData();
        UART_ClearRxBuffer();
        
    } //quando arriva l'header 160, entra nella routine per cambiare il colore
}

/* [] END OF FILE */
