/**
*================================================
*   \Uart_Routine.h
*
*   Header for the UART management, it implements the interrupt routine for transmission and an error routine that resets the transmission
*
*   \Author: Oswaldo Parra, Michele Civitavecchia
*   \Date: 08/06/2021
*================================================
*/
#ifndef __INT_H
    #define __INT_H
    #include "cytypes.h"
    
    
    CY_ISR_PROTO(Custom_UART_RX_ISR);
    
    void UART_ErrorManagement(void);
#endif

/* [] END OF FILE */
