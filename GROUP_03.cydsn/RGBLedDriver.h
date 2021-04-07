#ifndef __RGB_LED_DRIVER_H
    #define __RGB_LED_DRIVER_H
    
    #include "cytypes.h"
    
    
    typedef struct color {
        uint8 red;
        uint8 green;
        uint8 blu;
    }color;
    
    void RGBLed_Start();
    
    void RGBLed_Stop();
    
    void RGBLed_WriteColor(color c);
#endif

/* [] END OF FILE */
