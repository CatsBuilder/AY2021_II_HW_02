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
#define ERRORE 6
extern uint8_t count;
extern uint8_t timer_compare;
extern uint8_t info;
uint8_t flag=0;
CY_ISR(CustomTimerISR){
    
    count++;
    Timeout_Timer_ReadStatusRegister();
    if (count>=timer_compare){
        info=ERRORE;
        
    }
    else 
        ;
    
}

/* [] END OF FILE */
