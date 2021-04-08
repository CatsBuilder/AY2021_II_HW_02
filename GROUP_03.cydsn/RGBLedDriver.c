//*Programma di gestione del LED RGB*//

#include "project.h"
#include"RGBLedDriver.h"

static void RGBLed_WriteRed (uint8 red);

static void RGBLed_WriteGreen (uint8 green);

static void RGBLed_WriteBlu (uint8 blu);

void RGBLed_Start()
{
    PWM_BG_Start();
    PWM_R_Start();
}
void RGBLed_Stop()
{
    PWM_BG_Stop();
    PWM_R_Stop();
}
void RGBLed_WriteColor(color c)//Funzione per aggiornare il colore del LED
{
    RGBLed_WriteRed(c.red);
    RGBLed_WriteGreen(c.green);
    RGBLed_WriteBlu(c.blu);
}
static void RGBLed_WriteBlu(uint8 blu)
{
    PWM_BG_WriteCompare1(blu);
}
static void RGBLed_WriteGreen(uint8 green)
{
    PWM_BG_WriteCompare2(green);
}
static void RGBLed_WriteRed(uint8 red)
{
    PWM_R_WriteCompare(red);
}
/* [] END OF FILE */
