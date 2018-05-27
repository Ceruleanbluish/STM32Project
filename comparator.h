/*
 * comparator.h
 *
 *  Created on: 11 11 2017
 *      Author: Ceruleanbluish
 */

#ifndef COMPARATOR_H_
#define COMPARATOR_H_

#include "stm32l4xx_hal.h"
#include "stm32l4xx.h"
#include "led.h"

extern COMP_HandleTypeDef COMP1Handle;
extern TIM_HandleTypeDef Timer2Handle;

void COMP_Config(void);
void PB2_Init(void);
void TIM2_COMP_Init(void);

#endif /* COMPARATOR_H_ */
