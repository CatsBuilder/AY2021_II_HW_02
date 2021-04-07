#include "GetKey.h"
#include "RGBLedDriver.h"
#include "Int.h"
#include "UART.h"
#include "stdio.h"
#include "cytypes.h"


CY_ISR(Custom_UART_RX_ISR)
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        t=GetKey(UART_ReadRxData());
        UART_ClearRxBuffer();
    }
}

/* [] END OF FILE */
