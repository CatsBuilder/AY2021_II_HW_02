/**
*================================================
*       \RGBLedDriver.h
*
*       Header file to initialize the RGB led and implement all the functions needed to control the RGB LED
*
*       \Authors: Michele Civitavecchia, Oswaldo Parra
*       \Date : 06/0472021
*================================================
*/
#ifndef __RGB_LED_DRIVER_H
    #define __RGB_LED_DRIVER_H
    
    #include "cytypes.h"
    
    
    typedef struct color { //new structure for color information storage
        uint8 red;
        uint8 green;
        uint8 blu;
    }color;
    
    void RGBLed_Start();
    
    void RGBLed_Stop();
    
    void RGBLed_WriteColor(color c);
#endif

/* [] END OF FILE */
