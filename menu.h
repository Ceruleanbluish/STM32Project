/*
 * menu.h
 *
 *  Created on: 11 11 2017
 *      Author: Ceruleanbluish
 */

#ifndef MENU_H_
#define MENU_H_

#include "stm32l4xx_hal.h"
#include "stm32l4xx.h"
#include "stm32l476g_discovery_glass_lcd.h"
#include "adc.h"
#include "comparator.h"
#include "led.h"
#include "global_var.h"
#include "arm_math.h"
#include "arm_const_structs.h"

extern TIM_HandleTypeDef Timer4Handle;
extern ADC_HandleTypeDef ADC1Handle;

extern COMP_HandleTypeDef COMP1Handle;
extern TIM_HandleTypeDef Timer2Handle;

struct MenuItem
{
    uint8_t MenuCount;
    char *DisplayString;
    void (*Subs)();
    struct MenuItem *Childrenms;
    struct MenuItem *Parentms;
};

void Nop(void);
//void FFT_Init(struct MenuItem *roam);
//void COMP_Init(struct MenuItem *roam);
void FFT_Processing(struct MenuItem *roam);
void COMP_Processing(struct MenuItem *roam);
void MeterPerSecond(struct MenuItem *roam);
void MilePerHour(struct MenuItem *roam);
void KilometerPerHour(struct MenuItem *roam);
void GameOver(void);
void Locate(struct MenuItem *roam);
void Run(struct MenuItem *roam);

struct MenuItem m0_main[2];

struct MenuItem m1_fft[1];
struct MenuItem m2_fft_unitconverter[3];

struct MenuItem m1_comp[1];
struct MenuItem m2_comp_unitconverter[3];

#endif /* MENU_H_ */
