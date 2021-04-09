/**
*================================================
*   \timeout.h
*
*   Source file for CustomTimerISR: deals with time flow and sets the state in UART transmission to "ERROR" in case of timeout
*
*   \Authors: Oswaldo Parra, Michele Civitavecchia
*   \Date: 06/04/2021
*================================================
*/
#ifndef __TIMEOUT_H__
    #define __TIMEOUT_H__
    
    #include "cytypes.h"
    #include "project.h"
    
    CY_ISR_PROTO(CustomTimerISR);
    
    
#endif
/* [] END OF FILE */
