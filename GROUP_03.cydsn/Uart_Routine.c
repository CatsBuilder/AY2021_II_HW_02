//*Routine Interrupt UART*//

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
#define ERRORE 6
extern uint8_t rgb[3]; //array in cui vengono salvati temporaneamente i valori da inserire nel LED [red,green,blue]
extern uint8_t header,timer_compare,tail, timer_compare_temp,count,stop, info;
uint8_t i;
extern color color_led;

CY_ISR(Custom_UART_RX_ISR){
    switch (info) { //gli switch si riferiscono agli stati della macchina a stati finiti, ogni case è un passo
        case HEAD: //inizialmente ci si aspetta di avere l'header iniziale
            header=UART_ReadRxData();
            Timeout_Timer_Start();
            if(header==0xa1){ //a seconda di qual è l'header, decidiamo se fare selezione timeout o selezione colore
                info=TIMEOUTSELECTION;
            }
            else if (header==0xa0){ //in caso di header 160 "entriamo nel loop" che ci porta a cambiare il colore
                //il primo passo è il rosso
                //settiamo il counter a zero per partire a contare
                //Timeout_Timer_Init(); /*partiamo con il conteggio che nel caso portasse il valore di count oltre il 
                //timeout time, ci porterà allo stato di errore dove viene reinizializzato tutto e si riparte da head*/
                info=RED;
                
            }
            else if(header==0x76|| header==0x56){// in caso di header 'v' oppure 'V'
                UART_PutString("RGB LED Program $$$");//Per Test GUI
                UART_ClearRxBuffer();//refresh sul buffer
                Timeout_Timer_Stop();
                info=HEAD;
            }
            else 
                info=ERRORE; //se arriva un header che non è associato a nessuna routine, finiamo diretti in case ERRORE
            UART_ClearRxBuffer();
            break;
        case TIMEOUTSELECTION: // routine per cambiare il tempo di timeout
            count=0;
            timer_compare_temp=UART_ReadRxData(); /*mettiamo il tempo immesso in una variabile temporanea, in caso il 
            tail non sia corretto, la variabile vera verrà cambiata solo in caso il tail sia corretto*/
            info=TAIL; //andiamo ad aspettare il prossimo byte che sarà di tail
            UART_ClearRxBuffer();
            break;
        case RED:
            color_led.red=UART_ReadRxData(); //in caso di 160 finiamo nella routine del colore, il primo è il rosso
            count=0; //se arriviamo qui senza errori azzeriamo il timer
            UART_ClearRxBuffer();
            info=GREEN;
            break;
        case GREEN:
            color_led.green=UART_ReadRxData();
            count=0;
            UART_ClearRxBuffer();
            info=BLU;
            break;
        case BLU:
            color_led.blu=UART_ReadRxData();
            UART_ClearRxBuffer();
            info=TAIL;
            count=0;
            break;
        case TAIL:
            tail=UART_ReadRxData();
            if (tail==0xc0 && header==0xa1){
                timer_compare=timer_compare_temp;
                info=HEAD;
            }
            else if (tail==0xc0 && header==0xa0){
                RGBLed_WriteColor(color_led);
                info=HEAD;
                
            }
            else
                info=ERRORE;
            UART_ClearRxBuffer();
            count=0;
            Timeout_Timer_Stop();
            break;
            
    }
    
}
/*=======================================================
\ Questa routine va bene per fare tutti in un solo interrupt, meglio fare un interrupt ogni byte arrivato 
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
=========================================================
*/

/* [] END OF FILE */
