#include "SelectColor.h"

void SelectColor(){
    UART_PutString("Insert_red\r\n");
    CyDelay(5000);
    Data.red=Temp;
    Temp=0;
    UART_PutString("Insert_green\r\n");
    CyDelay(5000);
    Data.green=Temp;
    Temp=0;
    UART_PutString("Insert_blue\r\n");
    CyDelay(5000);
    Data.blu=Temp;
    RGBLed_WriteColor(Data);
    Temp=0;
}


/* [] END OF FILE */
