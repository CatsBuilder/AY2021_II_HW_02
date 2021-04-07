
#include "RGBLedDriver.h"
#include "Uart_Routine.h"
#include "UART.h"
#include "stdio.h"
#include "cytypes.h"
#include "Timeout_Timer.h"

extern uint8_t rgb[3]; //[red,green,blue]
extern uint8_t header,timer_compare,tail, timer_compare_temp,count,stop;
uint8_t i;
extern color color_led;
CY_ISR(Custom_UART_RX_ISR){ 
    tail=0;
    header=0;
    while(UART_ReadRxStatus() != UART_RX_STS_FIFO_NOTEMPTY) //attendere che il byte sia disponibile (ridondante)
        ; 
    header=UART_ReadRxData(); //assegna il valore del byte al header per capire cosa deve fare, imposta timer o seleziona colore
    UART_ClearRxBuffer(); //refresh sul buffer
    if (header==161){ 
        while(UART_ReadRxStatus() != UART_RX_STS_FIFO_NOTEMPTY);
        timer_compare_temp=UART_ReadRxData(); //mette il dato in una temporanea, se il tail è sbagliato, il tempo di compare non si aggiorna
        UART_ClearRxBuffer();
       
    } //quando arriva l'header 161, entra nella routine per cambiare il timer
    else if(header==160){ 
        count=0;    //ogni volta che finisco un giro di ricezione->assegnazione refresh sul counter per evitare lo stop
        Timeout_Timer_Start();
        for (i=0;i<3;i++){ //assegno alle locazioni del array, i colori trasmessi dal terminale
            count=0;
            while(UART_ReadRxStatus() != UART_RX_STS_FIFO_NOTEMPTY);
            if (stop){ //se il timer arriva al tempo di timeout, questa flag si alza e richiama USART_stop
                stop=0;
                UART_ClearRxBuffer();
                UART_Init();
                break; //esce dal for
            }
            rgb[i]=UART_ReadRxData();
            UART_ClearRxBuffer();
        }
    } //quando arriva l'header 160, entra nella routine per cambiare il colore
    while(UART_ReadRxStatus() != UART_RX_STS_FIFO_NOTEMPTY)
        ;
    tail=UART_ReadRxData();
    UART_ClearRxBuffer();
    if (tail==192 && header==161)
        timer_compare=timer_compare_temp; //rendo effettivo il cambio del tempo di timeout
    else if (tail==192 && header==160){
        color_led.red=rgb[0];
        color_led.green=rgb[1];
        color_led.blu=rgb[2];
    }   //cambio il colore
    else if (tail!=192) 
        ;
}

/* [] END OF FILE */
