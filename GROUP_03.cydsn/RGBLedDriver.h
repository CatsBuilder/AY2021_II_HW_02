#ifndef __RGB_LED_DRIVER_H
    #define __RGB_LED_DRIVER_H
    
    #include "cytypes.h"
    
    
    typedef struct Color {
        uint8 red;
        uint8 green;
        uint8 blu;
    }Color;
    
    void RGBLed_Start();
    
    void RGBLed_Stop();
    
    void RGBLed_WriteColor(Color c);
#endif

/* [] END OF FILE */
