/*
 * adc.h
 *
 *  Created on: 11 11 2017
 *      Author: Ceruleanbluish
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32l4xx_hal.h"
#include "stm32l4xx.h"
#include"led.h"

extern ADC_HandleTypeDef ADC1Handle;
extern TIM_HandleTypeDef Timer4Handle;

/* Exported functions --------------------------------------------------------*/
void ADC_Config(void);
void PA0_GPIO_Init(void); // PA0--adc1_channel_5 as input pin
uint32_t ADC_Converter(ADC_HandleTypeDef* hadc, uint32_t Timeout);
void TIM4_ADC_init(void);


#endif /* ADC_H_ */
