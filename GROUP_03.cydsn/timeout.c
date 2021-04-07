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
#include "timeout.h"
#include "project.h"

extern uint8_t count;
extern uint8_t timer_compare;
extern uint8_t stop_uart;
void CustomTimerISR(void){
    count++; // il timer va in overflow ogni secondo, count sono i sewcondi trascorsi da quando il timer è stato inizializzato
    if (count>=timer_compare){
        //stop_uart=1;            //  quando raggiunge il numero di secondi immessi per il timeout, alza una flag che l'uart deve usare per reinizializzarsi
        UART_Stop();
        //metodo alternativo è usare una porta per forzare il reset sulla uart, in questa routine abilitamo una porta e la accendiamo, nel top design colleghiamo quella porta al reset pin 
        count=0;
    }
    else 
        ;
    
}

/* [] END OF FILE */
