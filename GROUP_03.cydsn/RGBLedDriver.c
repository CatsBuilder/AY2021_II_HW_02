/**
*================================================
*       \RGBLedDriver.c
*
*       Source file to initialize the RGB led and implement all the functions needed to control the RGB LED
*
*       \Authors: Michele Civitavecchia, Oswaldo Parra
*       \Date : 06/0472021
*================================================
*/

#include "project.h"
#include"RGBLedDriver.h"

static void RGBLed_WriteRed (uint8 red);

static void RGBLed_WriteGreen (uint8 green);

static void RGBLed_WriteBlu (uint8 blu);

extern color black;

void RGBLed_Start()                             //PWMs initialization
{
    PWM_BG_Start();
    PWM_R_Start();
    RGBLed_WriteColor(black);                   //at the beginning the led has to be black
    
}

void RGBLed_Stop()                              //PWMs arrest
{
    PWM_BG_Stop();
    PWM_R_Stop();
}

void RGBLed_WriteColor(color c)                 //function to drive the PWMs and create a combination of RGB colors that creates a composite color
{
    RGBLed_WriteRed(c.red);
    RGBLed_WriteGreen(c.green);
    RGBLed_WriteBlu(c.blu);
}

static void RGBLed_WriteBlu(uint8 blu)          //function to drive the blu dose in the combination
{
    PWM_BG_WriteCompare1(blu);
}

static void RGBLed_WriteGreen(uint8 green)      //function to drive the green dose in the combination
{
    PWM_BG_WriteCompare2(green);
}

static void RGBLed_WriteRed(uint8 red)          //function to drive the red dose in the combination
{
    PWM_R_WriteCompare(red);
}
/* [] END OF FILE */
