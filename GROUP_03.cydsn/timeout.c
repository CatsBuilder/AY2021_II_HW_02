/* ========================================
Routine dell'interrupt del timer
se il conteggio del timer supera 
il valore impostato viene aggiornata 
la variabile di stato 'info'
 * ========================================
*/
#include "timeout.h"
#include "project.h"
#define ERRORE 6
extern uint8_t count;//Variabile che tiene conto dei secondi passati dall'avvio del timer
extern uint8_t timer_compare;
extern uint8_t info;
CY_ISR(CustomTimerISR){
    count++;
    Timeout_Timer_ReadStatusRegister();
    if (count>=timer_compare){
        info=ERRORE;
    }
    else ;
}
/* [] END OF FILE */
