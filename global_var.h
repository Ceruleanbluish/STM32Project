/*
 * global_var.h
 *
 *  Created on: 11 11 2017
 *      Author: Ceruleanbluish
 */

#ifndef GLOBAL_VAR_H_
#define GLOBAL_VAR_H_

#include "stm32l4xx_hal.h"
#include "stm32l4xx.h"

#define NUM 2048
#define FS 2048
#define TIMES 20

extern float frequency;
extern float Freq_ADC_FFT;
extern float Freq_InputCapture[TIMES]; // TIM2 COMP IC

extern uint8_t LCD_Display[20];
extern char USART_Transmit[20];
extern float AD_Result[NUM * 2];
extern float out[NUM * 2];

extern float result[NUM];
//uint32_t AD_Conv;
extern uint32_t FFT_index; // for FFT
extern uint32_t COMP_index; // for COMP
extern char over;

#endif /* GLOBAL_VAR_H_ */
