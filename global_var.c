/*
 * global_var.c
 *
 *  Created on: 11 11 2017
 *      Author: Ceruleanbluish
 */

#include "global_var.h"

float frequency;
float Freq_ADC_FFT;
float Freq_InputCapture[TIMES]; // TIM2 COMP IC

uint8_t LCD_Display[20];
char USART_Transmit[20];
float AD_Result[NUM * 2];
float out[NUM * 2];

float result[NUM];
//uint32_t AD_Conv;
uint32_t FFT_index; // for FFT
uint32_t COMP_index; // for COMP
char over;
